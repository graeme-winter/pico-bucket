import time

import spidev

spi = spidev.SpiDev()
spi.open(0, 0)
spi.mode = 3
spi.bits_per_word = 8
spi.max_speed_hz = 1000000

# defaults?

NN = 3

x = [1 for j in range(20)]

t0 = time.time()
for j in range(NN):
    data = spi.xfer(x)
    print(data)
t1 = time.time()

print("Average %.4f" % ((t1 - t0) / NN))
