from machine import Pin
from rp2 import PIO, StateMachine, asm_pio
import array
import struct
import math

# eight bit DAC - keep each 8 bit assignment for 5 clock ticks as need to allow
# time for jmp and pull calls
@asm_pio(
    out_init=(
        PIO.OUT_LOW,
        PIO.OUT_LOW,
        PIO.OUT_LOW,
        PIO.OUT_LOW,
        PIO.OUT_LOW,
        PIO.OUT_LOW,
        PIO.OUT_LOW,
        PIO.OUT_LOW,
    ),
    out_shiftdir=PIO.SHIFT_RIGHT,
)
def eight_bit_dac():
    label("loop")
    pull()
    out(pins, 8)[4]
    out(pins, 8)[4]
    out(pins, 8)[4]
    out(pins, 8)
    jmp("loop")[2]


# generate input as a byte array - here sine wave lifted to be > 0

nn = 100

b = array.array(
    "B", [127 + int(round(127 * math.sin(_ * math.pi / nn))) for _ in range(2 * nn)]
)

# pack into four-byte ints
data = array.array("I", struct.unpack("I" * 50, b))

# sm to 50 kHz -> each update above takes 5 ticks so 10 kHz wave, and emable
sm = StateMachine(0, eight_bit_dac, freq=50000, out_base=Pin(2))
sm.active(1)

while True:
    sm.put(data)
