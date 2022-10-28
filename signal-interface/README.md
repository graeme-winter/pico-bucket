# USB Interface to Signal Generator

Mock up of USB interafce to pico-signal-generator.

## API

Three parts to the API - control and data: control allows setting of the frequency, clock etc. while the data in / out end points allow pushing of the bytes to output or reading the signal back. N.B. in practice full signal frequencies greatere than ~ 100 kHz are measurably attenuated by the capacitance of current implementation. All words are little endian.

### Control Endpoint

Control endpoint consists of two main registers - one to set the device up and one to go / stop. Overall the configuration includes:

- CPU frequency
- CPU divider as short / byte i.e. short is integer part, byte is fractional
- High / low count for the external trigger
- Number of points (<= 200,000)

Go / stop needs to trigger both the external clock and the signal pump at the same instant: will need to also (and this is important) reset the DMA etc..

Messages 1: control frequency:

`0x00000000 uint32_t cpu_freq uint16_t div_int uint8_t div_frc uint8_t 0`

Defaults to 125 MHz / 1 / 0 i.e. PIO output at 125,000,000 samples / s.

Message 2: control high / low / #points

`0x00000001 uint32_t high uint32_t low uint32_t npoints`

Message 3: start / stop

`0xffff0000 stop`
`0xffffffff start`

### Control Endpoint (2)

Could also allow messages of the form `XSIN` or `XSQR` for e.g. square wave, sine wave etc. (saw springs to mind as well). These would then take amplitude, phase offset, period in counts and write internally to the signal buffer. In principle could also implement `READ` or similar which would grab from the ADC at a clocked interval and write to allow reproduction of an incoming signal.

### Data Endpoint

API here is very simple: first four bytes are offset, remaining bytes are signal. Offset will be modulo 200,000 to prevent buffer overflow. `nn` must be a multimple of four for the DMA to work correctly.

`uint32_t offset uint8_t signal[nn]`

### Readback Endpoint

Internally maintain a read pointer which is set between 0 and npoints abvove, and allow reading of the signal from this. Useful to fetch back a computed signal from `XSIN` etc. so verification is possible.
