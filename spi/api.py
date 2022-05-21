import spidev

spi = spidev.SpiDev(0, 0)

# defaults?
spi.mode = 3
spi.bits_per_word = 8
spi.max_speed_hz = 1000000

x = [1 for j in range(20000)]
data = spi.xfer3(x)
print(max(data))
