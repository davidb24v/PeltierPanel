import serial
import time
import signal
import sys

ser = serial.Serial(port="/dev/ttyACM0", baudrate=115200, timeout=2.0)

# Reset the Arduino
ser.setDTR(False)
time.sleep(0.05)
ser.setDTR(True)
time.sleep(2)

def signal_handler(signal, frame):
    fh.close()
    sys.exit(0)

signal.signal(signal.SIGINT, signal_handler) 

fh = open("temperatures.csv", "w")
ser.flushInput()
ser.readline()

while True:
    data = ser.readline()
    time, hot, cold = data.strip().split()
    time = int(time)//1000
    fh.write('{},{},{}\n'.format(time, hot, cold))
    fh.flush()
    print time, hot, cold
    
