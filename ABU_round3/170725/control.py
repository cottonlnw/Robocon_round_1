import math

class Movement_control:
    def __init__(self, mode, joystick):
        self.joy = joystick
        self.axes = [0] * 6
        self.buttons = [0] * 16
        self.power = [0] * 3
        self.clutch = 1.0
        self.motor_control = [0] * 4
        self.rack_control = [0] * 2
        self.prev_buttons = [0] * 16
        self.toggle_mode = 0

    def get_joy(self):
        result = self.joy.read_ps5()
        if result is None:
            return None
        self.axes, self.buttons = result
        self.power = [self.axes[4], self.axes[3], self.axes[0]]

    def mode_joy(self):
        self.update_toggle()
        self.mode = self.toggle_mode
        self.motor_power_clipped = [max(-255, min(255, p)) for p in self.motor_control]

    def update_toggle(self):
        if self.buttons[9] == 1 and self.prev_buttons[9] == 0:
            self.toggle_mode = 1 - self.toggle_mode
        self.prev_buttons = self.buttons[:]

    def drive_train(self):
        self.clucth_control()
        self.motor_control[0] = self.power[0] + self.power[1] + self.power[2]
        self.motor_control[1] = self.power[0] - self.power[1] - self.power[2]
        self.motor_control[2] = self.power[0] - self.power[1] + self.power[2]
        self.motor_control[3] = self.power[0] + self.power[1] - self.power[2]
        self.motor_control = [int(p * self.clutch) for p in self.motor_control]
        self.mode_joy()
        return [0, 0, 0, 0] if all(abs(p) < 20 for p in self.motor_power_clipped) else self.motor_power_clipped

    def clucth_control(self):
        MAX_L2_VALUE = 170
        self.raw_brake = self.axes[2]
        self.clutch = 1 - (self.raw_brake / MAX_L2_VALUE)
        if self.clutch <= 0.01:
            self.clutch = 0

    def rack_train(self):
        self.rack_control[0] = self.buttons[4]
        self.rack_control[1] = self.buttons[5]
        return self.rack_control