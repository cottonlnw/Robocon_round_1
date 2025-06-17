import tkinter as tk
from tkinter import messagebox
import sys
import os
import time
from joystick import Ps5reader

class ConsoleRedirect:
    def __init__(self, text_widget):
        self.text_widget = text_widget

    def write(self, message):
        self.text_widget.insert(tk.END, message)
        self.text_widget.see(tk.END)

    def flush(self):
        pass

class gui_control:
    def __init__(self, root, ser_reset):
        self.ser_reset = ser_reset
        self.root = root
        self.root.title("Rc modracle Control Panel")
        self.root.geometry("1024x600")
        self.root.configure(bg="black")
        self.root.attributes('-fullscreen', True)
        self.root.bind_all("<Escape>", lambda e: self.root.attributes('-fullscreen', False))
        self.root.bind_all("<F12>", lambda e: self.root.attributes('-fullscreen', True))
        self.root.focus_set()

        self.joy = Ps5reader()
        self.joy.checkconnect()

        self.reset_broad_button = tk.Button(root, text="Reset Broad", font=("Courier", 12), fg="#000000", bg="#ffe933",
                                            command=self.reset_broad, width=45, height=15)
        self.reset_broad_button.place(x=0, y=0)

        self.reset_sensor_button = tk.Button(root, text="Reset Sensor", font=("Courier", 12),
                                             command=self.reset_sensor, width=45, height=15)
        self.reset_sensor_button.place(x=0, y=300)

        self.text_output = tk.Text(root, height=73, width=530, bg="black", fg="lime", font=("Courier", 10))
        self.text_output.place(x=470, y=0)

        sys.stdout = ConsoleRedirect(self.text_output)
        print("Start system...")
        print("ConnectJoyalrealy")
        print("SendDatatobroad...")

    def reset_broad(self):
        try:
            print("Reset Borad")
            python = sys.executable
            os.execl(python, python, *sys.argv)
        except Exception as e:
            messagebox.showerror("Error", f"Failed to reset broad: {e}")

    def reset_sensor(self):
        print("Reset Sensor")
        try:
            self.ser_reset.reset_input_buffer()
            time.sleep(0.3)
            cmd = "<r>".encode("utf-8")
            print(f"📤 ส่ง {cmd} ไปที่ Mega")
            self.ser_reset.write(cmd)
            self.ser_reset.flush()
        except Exception as e:
            print(f"ส่งคำสั่งไม่สำเร็จ: {e}")