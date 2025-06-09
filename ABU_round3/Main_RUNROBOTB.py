from control import Movement_control
from joystick import Ps5reader
import serial
import time

def main():
    result_joy = joy.read_ps5()
    if result_joy is None:
        print("No controller detected")
        return
    result_drive = control.drive_train()
    result_rack = control.rack_train()
    control.get_joy() 
    control.drive_train()
    
    Send_Data = result_drive + result_rack
    message = ' '.join(map(str, Send_Data)) + '\n'
    ser.write(message.encode())
    ser.flush() 
    time.sleep(0.03)
    print("Sent to Mega:", message)
    
    

if __name__ == "__main__": 
    joy = Ps5reader()
    joy.checkconnect() 
    control = Movement_control(0, joy)  # ส่ง joy ไปให้ control
    ser = serial.Serial("/dev/serial0", 115200)
    time.sleep(0.02)

    while True:
        main()
