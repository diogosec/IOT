#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>

// Create the TSL2561 sensor object
Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);

void setup(void) {
  Serial.begin(9600);
  
  if(!tsl.begin()) {
    Serial.println("Couldn't find TSL2561 sensor");
    while(1);
  }

  // Set the gain to 1x (no gain) - use 16x for very dark situations
  tsl.setGain(TSL2561_GAIN_1X);

  // Set the integration time to 13ms - lower value for bright light, higher for dim light
  tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);
}

void loop(void) {
  // Get a new sensor event
  sensors_event_t event;
  tsl.getEvent(&event);

  // Display the sensor values
  Serial.print(F("Lux: ")); Serial.println(event.light);

  delay(500);  // wait for half a second
}
