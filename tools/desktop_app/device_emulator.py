#!/usr/bin/env python3

"""
Emulates a device that sends data over the USB CDC serial port.
"""

import sys
import serial
import random
import time

if len(sys.argv) < 2:
    print("Usage: python device_emulator.py <serial_port>")
    sys.exit(1)

# fmt: off
serial_path = sys.argv[1]
stages = [0, 60, 270, 330]
target_temperature = [18,  19,  20,  22,  23,  24,  26,  27,  29,  30,  32,  33,  35,  36,  38,  39,  41,  43,
                      44,  46,  47,  49,  50,  52,  53,  54,  56,  57,  58,  60,  61,  62,  63,  64,  65,  67,
                      68,  69,  69,  70,  71,  72,  73,  74,  74,  75,  76,  76,  77,  78,  78,  79,  79,  80,
                      80,  81,  81,  81,  82,  82,  82,  82,  83,  83,  83,  83,  84,  84,  84,  84,  84,  84,
                      84,  84,  84,  85,  85,  85,  85,  85,  85,  85,  85,  85,  85,  85,  85,  85,  85,  85,
                      85,  85,  85,  85,  86,  86,  86,  86,  86,  86,  86,  86,  86,  86,  86,  86,  87,  87,
                      87,  87,  87,  87,  87,  88,  88,  88,  88,  88,  88,  89,  89,  89,  89,  89,  90,  90,
                      90,  90,  91,  91,  91,  91,  92,  92,  92,  92,  93,  93,  93,  93,  93,  94,  94,  94,
                      94,  95,  95,  95,  95,  96,  96,  96,  96,  97,  97,  97,  97,  97,  98,  98,  98,  98,
                      99,  99,  99,  99,  99,  99, 100, 100, 100, 100, 100, 100, 101, 101, 101, 101, 101, 101,
                      101, 102, 102, 102, 102, 102, 102, 102, 103, 103, 103, 103, 103, 103, 103, 103, 104, 104,
                      104, 104, 104, 104, 104, 105, 105, 105, 105, 105, 106, 106, 106, 106, 106, 107, 107, 107,
                      107, 108, 108, 108, 109, 109, 109, 110, 110, 110, 111, 111, 112, 112, 113, 113, 114, 114,
                      115, 115, 116, 116, 117, 117, 118, 119, 119, 120, 120, 121, 122, 123, 123, 124, 125, 125,
                      126, 127, 128, 129, 129, 130, 131, 132, 133, 133, 134, 135, 136, 137, 138, 139, 139, 140,
                      141, 142, 143, 144, 145, 145, 146, 147, 148, 149, 149, 150, 151, 151, 152, 153, 153, 154,
                      155, 155, 156, 156, 157, 157, 157, 158, 158, 158, 159, 159, 159, 159, 159, 159, 159, 159,
                      159, 159, 158, 158, 158, 157, 157, 156, 156, 155, 154, 154, 153, 152, 151, 150, 149, 148,
                      147, 145, 144, 143, 141, 140, 138, 137, 135, 134, 132, 130, 129, 127, 125, 123, 122, 120,
                      118, 116, 115, 113, 111, 109, 108, 106, 105, 103, 102, 101,  99,  98,  97,  96,  96,  95,]
# fmt: off

serial_port = serial.Serial(serial_path, baudrate=9600, timeout=1)

try:
    for i in range(len(target_temperature)):
        # Add some noise to the temperature
        temperature = target_temperature[i] + random.randint(-3, 3)
        # Determine the process stage based on the current time
        for j in range(len(stages)):
            if i >= stages[j]:
                stage = j + 1
            else:
                break
        message = f'{{"Time":{i}, "Temperature":{temperature},"TargetTemperature":{target_temperature[i]},"State":{stage}}}'
        serial_port.write(message.encode("utf-8"))
        print("Sent:", message)
        time.sleep(1)

except KeyboardInterrupt:
    print("\nScript interrupted by user.")

finally:
    serial_port.close()
