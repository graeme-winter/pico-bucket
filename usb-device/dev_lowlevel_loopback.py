#!/usr/bin/env python3

#
# Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
#
# SPDX-License-Identifier: BSD-3-Clause
#

# sudo pip3 install pyusb

import usb.core
import usb.util
import time

# find our device
dev = usb.core.find(idVendor=0x0000, idProduct=0x0001)

print(dev)

# was it found?
if dev is None:
    raise ValueError("Device not found")

# get an endpoint instance
cfg = dev.get_active_configuration()
intf = cfg[(0, 0)]

outep = tuple(
    usb.util.find_descriptor(
        intf,
        find_all=True,
        custom_match=lambda e: usb.util.endpoint_direction(e.bEndpointAddress)
        == usb.util.ENDPOINT_OUT,
    )
)

print("******" * 10)
print(outep)

assert outep is not None

time.sleep(3)

for j in range(100):
    print(j)
    setting = "ABCD"
    outep[j % 2].write(setting)
