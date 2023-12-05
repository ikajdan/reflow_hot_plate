# Reflow Hot Plot

Allows to visualize and control the reflow soldering process.

### Usage

```bash
python reflow_hot_plot.py <serial_port>
```

### Testing

1. Set up a virtual serial port: `socat -d -d pty,raw,echo=0 pty,raw,echo=0`
1. Start the application: `python reflow_hot_plot.py /dev/pts/1`
1. Run the device emulator: `python device_emulator.py /dev/pts/2`

## API Specification

The API specification for communication between a dedicated desktop application and the device via the USB CDC interface.

### Send

Data that can be send to the device.

- 1 - starts the soldering procedure `[char]`.
- 0 - stops the soldering procedure `[char]`.

### Receive

Data received from the device.

- Time - time in seconds since the start of the soldering procedure `[int]`.
- Temperature - measured temperature in degrees Celsius `[int]`.
- TargetTemperature - reference temperature in degrees Celsius `[int]`.
- State - device state (0=idle, 1=preheat, 2=reflow, 3=cooldown) `[int]`.

Example message:

```
{
  "Time": 240,
  "Temperature": 120,
  "TargetTemperature": 118,
  "State": 2
}
```
