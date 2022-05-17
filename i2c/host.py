import smbus
import time

ADDRESS = 0x42

bus = smbus.SMBus(1)

# write recognised byte pattern - 01010101

sent = []

for j in range(0xff):
    value = j % 2
    bus.write_byte_data(ADDRESS, j, value)
    sent.append(value)


# read back

recv = []

for j in range(0xff):
    value = bus.read_byte_data(ADDRESS, j)
    recv.append(value)


matched = True
for j in range(0xff):
    matched = matched and (sent[j] == recv[j])

print(f"Binary pattern test: {matched}")

# write recognised byte pattern - 0 1 2 3 ...

sent = []

for j in range(0xff):
    value = j
    bus.write_byte_data(ADDRESS, j, value)
    sent.append(value)


# read back

recv = []

for j in range(0xff):
    value = bus.read_byte_data(ADDRESS, j)
    recv.append(value)


matched = True
for j in range(0xff):
    matched = matched and (sent[j] == recv[j])

print(f"Binary counter test: {matched}")
