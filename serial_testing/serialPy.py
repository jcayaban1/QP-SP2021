import serial

ser = serial.Serial("/dev/cu.usbmodem14101")

while True:
    line = ser.readline()
    print(line.decode("utf"), end = '')