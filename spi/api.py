import time

import spidev

spi = spidev.SpiDev()
spi.open(0, 1)
spi.mode = 3
spi.bits_per_word = 8
spi.max_speed_hz = 10000000

# defaults?

NN = 100

x = [1 for j in range(20000)]

t0 = time.time()
for j in range(NN):
    data = spi.xfer3(x)
    time.sleep(0.001)
    print(data[-10:])
t1 = time.time()

print("Average %.4f" % ((t1 - t0) / NN))
