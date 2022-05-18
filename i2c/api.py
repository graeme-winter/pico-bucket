import random
import smbus
import struct
import time

ADDRESS = 0x42

bus = smbus.SMBus(1)

message = struct.pack("IIII", 100, 101, 102, 103)

# write and read block data

sent = list(message)

#bus.write_i2c_block_data(ADDRESS, 0x0, [])
bus.read_i2c_block_data(ADDRESS, 0x0, 0x4)

bus.write_i2c_block_data(ADDRESS, 0x1, sent)

bus.write_i2c_block_data(ADDRESS, 0x2, [])
