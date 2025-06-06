import math
from joystick import Ps5reader

class All_control:
    def __init__(self, mode, joystick):
        self.joy = joystick 
        self.axes = [0] * 6
        self.buttons = [0] * 16
        self.power = [0] * 3 # ค่าแกนaxes indexตำแหน่งที่ 4 speed 3 staft 0 turn
        self.clutch = [0]
        self.motor_control = [0] * 4
        self.rack_control = [0] * 2 
        self.clutch = 1.0
        self.toggle_mode = 0  # 0 = Manual, 1 = Auto
        # print(f'Axes: {self.axes}')
        # print(f'Buttons: {self.buttons}\n')
        
    
    def get_joy(self):
        result = self.joy.read_ps5()
        if result is None:
            return  # ยังไม่มี controller ต่อหรือมีปัญหา ไม่ต้องทำอะไรต่อ

        self.axes, self.buttons = result
        self.power = [self.axes[4], self.axes[3], self.axes[0]]
        # print(f'Axes: {self.axes}')
        # print(f'Buttons: {self.buttons}\n')
        # print(f'motor_control : {self.motor_control}')
    def mode_joy(self): #NOTE - เปลี่ยนโหมด Turbo
        self.update_toggle()  # เรียกก่อนใช้งาน
        self.mode = self.toggle_mode
        if self.mode == 1:
            print('Turbo mode')
            self.motor_power_clipped = [max(-255, min(255, p)) for p in self.motor_control] #NOTE - Turbo
        else:
            print('Manual mode')
            self.motor_power_clipped = [max(-180, min(180, p)) for p in self.motor_control] #NOTE - Normal
            
    def update_toggle(self):     #NOTE - ระบบปุ่มกดดับ กดติด
        if self.buttons[9] == 1 and self.prev_buttons[9] == 0: #NOTE -  ปุ่ม Options 
            self.toggle_mode = 1 - self.toggle_mode
        self.prev_buttons = self.buttons[:]  # อัปเดตสถานะก่อนหน้า
        
        
    #wheel_control
    def drive_train(self): #NOTE - แรงล้อสี่ล้อ
        self.clucth_control()
        self.motor_control[0] = self.power[0] + self.power[1] + self.power[2]
        self.motor_control[1] = self.power[0] - self.power[1] - self.power[2]
        self.motor_control[2] = self.power[0] - self.power[1] + self.power[2]
        self.motor_control[3] = self.power[0] + self.power[1] - self.power[2]

        self.motor_control = [int(p * self.clutch) for p in self.motor_control]
        self.mode_joy()
        # print(self.motor_power_clipped)

        return 0 if all(abs(p) < 20 for p in self.motor_power_clipped) else self.motor_power_clipped
    
    
    def clucth_control(self): #NOTE -  brake
        MAX_L2_VALUE = 170
        self.raw_brake = self.axes[2]     #Max =100 if 200 ==50 %
        self.clutch = 1 - (self.raw_brake / MAX_L2_VALUE)

        if self.clutch <= 0.01:
            self.clutch = 0

        # print(f"L2: {self.raw_brake:.1f} → clutch: {self.clutch:.2f}")
    
    
    def rack_train(self): #NOTE - rack 
        self.rack_control[0] = self.buttons[4] # L1 downrack
        self.rack_control[1] = self.buttons[5] # R1 uprack
        # print(self.rack_control)
        return self.rack_control
    





