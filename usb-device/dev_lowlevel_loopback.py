#!/usr/bin/env python3

#
# Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
#
# SPDX-License-Identifier: BSD-3-Clause
#

# sudo pip3 install pyusb

import usb.core
import usb.util
import sys

# find our device
dev = usb.core.find(idVendor=0x0000, idProduct=0x0001)

# was it found?
if dev is None:
    raise ValueError("Device not found")

# get an endpoint instance
cfg = dev.get_active_configuration()
intf = cfg[(0, 0)]

outep = usb.util.find_descriptor(
    intf,
    custom_match=lambda e: usb.util.endpoint_direction(e.bEndpointAddress)
    == usb.util.ENDPOINT_OUT,
)

inep = usb.util.find_descriptor(
    intf,
    custom_match=lambda e: usb.util.endpoint_direction(e.bEndpointAddress)
    == usb.util.ENDPOINT_IN,
)

assert inep is not None
assert outep is not None

for j in range(1024):
    setting = chr(j % 8)
    outep.write(setting)
    status = inep.read(1)

    print(f"Device {j}: {status[0]}")
