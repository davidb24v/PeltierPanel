#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2
#define TEMPERATURE_PRECISION 9

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// arrays to hold device addresses
DeviceAddress hot  = { 0x28, 0xB1, 0xD1, 0x23, 0x05, 0x00, 0x00, 0x70 };
DeviceAddress cold = { 0x28, 0x20, 0x07, 0x24, 0x05, 0x00, 0x00, 0xB2 };

void setup(void)
{
  // start serial port
  Serial.begin(115200);
  Serial.println("Peltier Effect Panel Testing");

  // Start up the library
  sensors.begin();

  // set the resolution to 9 bit
  sensors.setResolution(hot, TEMPERATURE_PRECISION);
  sensors.setResolution(cold, TEMPERATURE_PRECISION);
}

void loop(void)
{ 
  // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus
  sensors.requestTemperatures();

  // Print timestamp and 2 x temperatures
  Serial.print(millis());
  Serial.print(" ");
  float tempC = sensors.getTempC(hot);
  Serial.print(tempC);
  Serial.print(" ");
  tempC = sensors.getTempC(cold);
  Serial.println(tempC);

  delay(1000);
}

