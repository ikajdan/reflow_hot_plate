# Reflow Hot Plot

Allows visualizing the temperature profile of a reflow soldering process.

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

Commands for controlling the device.

- 1 - starts the soldering procedure `[char]`.
- 0 - stops the soldering procedure `[char]`.

### Receive

Data received from the device.

- Duration - time in seconds since the start of the soldering procedure `[int]`.
- TC - thermocouple temperature in centigrade `[int]`.
- RTD - RTD temperature in centigrade `[int]`.
- Temperature - measured temperature in centigrade `[int]`.
- TargetTemperature - reference temperature in degrees Celsius `[int]`.
- Name - profile name `[string]`.
- Stage - heating stage (0=preheat, 1=soak, 2=reflow, 3=cooldown, 4=idle) `[int]`.
- State - device state (0=welcome, 1=menu, 2=precheck, 3=heating, 4=done, 5=aborted, 6=error) `[int]`.

Example message:

```json
{
  "Duration": 1098,
  "TC": 2350,
  "RTD": 2101,
  "Temperature": 2350,
  "TargetTemperature": 0,
  "Name": "DSP863",
  "Stage": 0,
  "State": 3
}
```
