# USB Interface to Signal Generator

Mock up of USB interafce to pico-signal-generator.

## API

Two parts to the API - control and data: control allows setting of the frequency, clock etc. while the data end point allows pushing of the bytes to output. N.B. in practice full signal frequencies greatere than ~ 100 kHz are measurably attenuated by the capacitance of current implementation. All words are little endian.

### Control Endpoint

Control endpoint consists of two main registers - one to set the device up and one to go / stop. Overall the configuration includes:

- CPU frequency
- CPU divider as short / byte i.e. short is integer part, byte is fractional
- High / low count for the external trigger
- Number of points (<= 200,000)

Go / stop needs to trigger both the external clock and the signal pump at the same instant: will need to also (and this is important) reset the DMA etc..

### Data Endpoint

API here is very simple: first four bytes are offset, remaining bytes are signal. Offset will be modulo 200,000 to prevent buffer overflow.
