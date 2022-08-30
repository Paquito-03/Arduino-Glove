import serial  # librerie for read serial port
from pynput.keyboard import Controller  # library for simulate keyboard with python

arduino = serial.Serial(port='COM4', baudrate=9600,
                        timeout=.1)  # change de port to yours | it open the serial COM4, at 9600 bauts
keyboard = Controller()  # for press button

while True:
    cmd = arduino.readline()  # read Serial
    cmd = cmd.decode('utf-8')  # transform data in a string

    if str(cmd):
        # print(cmd[1:6]) DEBUG : print axe x
        # print(cmd [7:12]) DEBUG : print axe y
        # print(cmd [13:18]) DEBUG : print axe z
        # print(cmd [19:24]) DEBUG : print flex
        # print(cmd [29:30]) DEBUG : print switch

        if int(cmd [1:6]) > 8000:  # if for dive
            keyboard.press('l')
            keyboard.release('l')
        while int(cmd [1:6]) < -5000:  # loop for continuing backward
            keyboard.release('z')
            keyboard.press('s')
            cmd = arduino.readline()
            cmd = cmd.decode('utf-8')
        while int(cmd [7:12]) > 5000:  # loop for left
            keyboard.release('z')
            keyboard.press('q')
            cmd = arduino.readline()
            cmd = cmd.decode('utf-8')
        while int(cmd [7:12]) < -5000:  # loop for right
            keyboard.release('z')
            keyboard.press('d')
            cmd = arduino.readline()
            cmd = cmd.decode('utf-8')

        if int(cmd [29:30]) == 1:  # if for jump
            keyboard.press('j')
            keyboard.release('j')
        while int(cmd [19:24]) > 5:  # loop for grap
            keyboard.press('m')
            cmd = arduino.readline()
            cmd = cmd.decode('utf-8')

        # release  all keyboard when the loop is over
        keyboard.release('m')
        keyboard.release('q')
        keyboard.release('d')
        keyboard.release('s')
        keyboard.press('z')
