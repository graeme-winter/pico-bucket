import smbus2
import time

ADDRESS = 0x42

bus = smbus2.SMBus(1)

# write recognised byte pattern - 01010101

sent = []

for j in range(0xFF):
    value = j % 2
    bus.write_byte_data(ADDRESS, j, value)
    sent.append(value)


# read back

recv = []

for j in range(0xFF):
    value = bus.read_byte_data(ADDRESS, j)
    recv.append(value)


matched = True
for j in range(0xFF):
    matched = matched and (sent[j] == recv[j])

print(f"Binary pattern test: {matched}")

# write recognised byte pattern - 0 1 2 3 ...

sent = []

for j in range(0xFF):
    value = j
    bus.write_byte_data(ADDRESS, j, value)
    sent.append(value)


# read back

recv = []

for j in range(0xFF):
    value = bus.read_byte_data(ADDRESS, j)
    recv.append(value)


matched = True
for j in range(0xFF):
    matched = matched and (sent[j] == recv[j])

print(f"Binary counter test: {matched}")

# write and read block data

sent = [0xFF - j for j in range(0xFF)]

for j in range(0, 0xFF, 0x20):
    bus.write_i2c_block_data(ADDRESS, j, sent[j : j + 0x20])

recv = []
for j in range(0, 0xFF, 0x20):
    block = bus.read_i2c_block_data(ADDRESS, j, 0x20)
    recv += block

matched = True
for j in range(0xFF):
    matched = matched and (sent[j] == recv[j])

print(f"Block test: {matched}")
