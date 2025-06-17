import pygame

class Ps5reader:
    def __init__(self):
        pygame.init()
        pygame.joystick.init()
        self.controller = None
        self.axes = []
        self.buttons = []

    def checkconnect(self):
        pygame.joystick.quit()
        pygame.joystick.init()
        if pygame.joystick.get_count() > 0:
            self.controller = pygame.joystick.Joystick(0)
            self.controller.init()
        else:
            self.controller = None

    def read_ps5(self):
        if self.controller is None:
            self.checkconnect()
            if self.controller is None:
                return None

        try:
            pygame.event.pump()
            if not self.controller.get_init():
                self.controller = None
                return None

            raw_axes = [self.controller.get_axis(i) for i in range(self.controller.get_numaxes())]
            self.axes = self.scale_axes(raw_axes)
            self.axes = [self.low_power(v) for v in self.axes]

            if len(self.axes) > 1:
                self.axes[1] = -self.axes[1]
            if len(self.axes) > 4:
                self.axes[4] = -self.axes[4]

            self.buttons = [self.controller.get_button(i) for i in range(self.controller.get_numbuttons())]
            hat = self.controller.get_hat(0) if self.controller.get_numhats() > 0 else (0, 0)
            self.buttons += [
                int(hat[0] == -1), int(hat[0] == 1),
                int(hat[1] == -1), int(hat[1] == 1),
            ]

            return self.axes, self.buttons

        except Exception as e:
            print(f"Exception in read_ps5: {e}")
            self.controller = None
            return None

    def scale_axes(self, raw_axes):
        NORMALIZATION_FACTOR = 0.95
        scaled_axes = [round(a / NORMALIZATION_FACTOR * 255) for a in raw_axes]
        if len(raw_axes) > 2:
            scaled_axes[2] = max(0, min(100, (raw_axes[2] + 1.0) * 50))
        return scaled_axes

    def low_power(self, value):
        return 0 if -5 < value < 5 else value