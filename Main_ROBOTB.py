from control import All_control
from joystick import Ps5reader

def main():
    joy.read_ps5()
    control.get_joy()
    result = control.drive_train()
    print(f'Drive result: {result}')
    control.rack_train()

if __name__ == "__main__":
    joy = Ps5reader()
    control = All_control(0, joy)
    joy.checkconnect()

    while True:
        main()
