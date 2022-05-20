import machine

cs = machine.Pin(17, machine.Pin.OUT)
cs.value(1)
spi = machine.SPI(
    0,
    baudrate=1000000,
    polarity=1,
    phase=1,
    bits=8,
    firstbit=machine.SPI.MSB,
    sck=machine.Pin(18),
    mosi=machine.Pin(19),
    miso=machine.Pin(16),
)

# write 1024 bytes
data = bytearray([(j + 0x80) % 0x100 for j in range(20000)])
buffer = bytearray([0xFF for j in range(20000)])
import time

t0 = time.time()
for j in range(10):
    cs.value(0)
    spi.write_readinto(data, buffer)
    cs.value(1)
print((time.time() - t0) / 10)
