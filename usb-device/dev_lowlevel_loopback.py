# sudo pip3 install pyusb

import usb.core
import usb.util
import string
import time

dev = usb.core.find(idVendor=0x0000, idProduct=0x0001)
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

blob = 10 * (string.ascii_lowercase + string.ascii_uppercase)

t0 = time.time()
for j in range(1000):
    setting = blob + "MESSAGE %d" % j
    print(j, outep[j % 2].write(setting))
t1 = time.time()
print(t1 - t0)