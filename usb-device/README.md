# USB Device

Simple USB device with two end points which react to low level USB interrupts to trigger bulk transfers. EP1 is "control" i.e. setting registers / triggering actions and EP2 is "data" i.e. sending bytes into a large buffer.

Based on [example](https://github.com/raspberrypi/pico-examples/tree/master/usb/device/dev_lowlevel) with a lot of reading of RP2040 data sheet to figure out the rest. Eventually will use this to document a how-to / improve above example. Wanted low-level as use case is interrupt driven.
