# sudo pip3 install pyusb

import usb.core
import usb.util
import string
import time

dev = usb.core.find(idVendor=0x0000, idProduct=0x0001)

print(dev)

if dev is None:
    raise ValueError("Device not found")

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

assert outep is not None

blob = bytearray([x % 256 for x in range(0x10000)])

t0 = time.time()
for j in range(0x10):
    outep[0].write("")
    outep[1].write(blob)
t1 = time.time()
print("%.1f bytes / s" % ((0x10000 * 0x10) / (t1 - t0)))