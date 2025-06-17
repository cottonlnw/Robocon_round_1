from control import Movement_control
from joystick import Ps5reader
from gui import gui_control
from gyro import UARTReceiver

import tkinter as tk
import serial
import time

# ==== Loop หลักของโปรแกรม ====
def main():
    try:
        control.get_joy()
        # print("Axes:", control.axes)
        # print("Buttons:", control.buttons)

        if not control.axes or not control.buttons:
            print("No controller detected")
        else:
            # ดึงค่าไปใช้ได้เลย #
            g = uart.receive()
            result_drive = control.drive_train()
            result_rack = control.rack_train()

            Send_Data = result_drive + result_rack
            message = ' '.join(map(str, Send_Data)) + '\n'
            # print(Send_Data)
            # print("📥 GIGA data:", g)  # g จะเป็นข้อความใน <...> เช่น "10,200,35"
            ser.write(message.encode())
            ser.flush()

        root.after(20, main)
    except Exception as e:
        print(f"ERROR in main(): {e}")

# ==== เริ่มโปรแกรม ====
if __name__ == "__main__": 
    joy = Ps5reader()
    uart = UARTReceiver("/dev/ttyAMA3", 115200, timeout=0.01)

    for _ in range(20):
        joy.checkconnect()
        if joy.controller:
            break
        print("รอการเชื่อมต่อจอย...")
        time.sleep(2)

    if not joy.controller:
        print("ไม่พบจอยหลังจากพยายามหลายครั้ง")
    else:
        print("เชื่อมต่อจอยสำเร็จ")
        
    control = Movement_control(0, joy)
    ser = serial.Serial("/dev/ttyAMA0", 115200)
    ser_reset = serial.Serial('/dev/ttyAMA3', 115200)
    time.sleep(0.02)

    # เริ่ม GUI
    root = tk.Tk()
    app = gui_control(root, ser_reset)
    main()
    root.mainloop()