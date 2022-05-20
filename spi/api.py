import spidev

spi = spidev.SpiDev(0, 0)

spi.max_speed_hz = 1000000
x = [1 for j in range(1024)]
spi.writebytes2(x)
data = spi.readbytes(1024)
print(max(data))
