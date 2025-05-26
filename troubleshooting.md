# 🛠️ Troubleshooting Guide: Smart Irrigation System

## LCD Not Displaying Text
- ✅ Ensure correct wiring to pins: RS, E, D4-D7
- ✅ Adjust the potentiometer to improve LCD contrast

## DHT11 Showing 'NaN' or '0'
- ✅ Check if the DHT library is properly installed
- ✅ Ensure the DHT11 data pin is connected to Pin 10
- ✅ Add a pull-up resistor (4.7k–10kΩ) if unstable readings

## Soil Moisture Always 0% or 100%
- ✅ Ensure proper sensor contact with moist soil
- ✅ Check analog pin A0 connection
- ✅ Test the sensor output with a multimeter

## Pump Not Turning On
- ✅ Verify pump power supply and relay module connections
- ✅ Confirm logic: `LOW` signal turns the pump ON (depending on relay type)

## Serial Monitor Not Showing Data
- ✅ Ensure correct COM port is selected in Arduino IDE
- ✅ Baud rate should be 9600
