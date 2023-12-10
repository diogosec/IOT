/* 
  Sketch generated by the Arduino IoT Cloud Thing "Untitled"
  https://create.arduino.cc/cloud/things/c7e5162f-b003-4662-bc9f-aef8235e31de 

  Arduino IoT Cloud Variables description

  The following variables are automatically generated and updated when changes are made to the Thing

  float numero;
  bool lightStatus;
  bool smartModeSwitch;
  bool switchLight;

  Variables which are marked as READ/WRITE in the Cloud Thing will also have functions
  which are called when their values are changed from the Dashboard.
  These functions are generated with the Thing and added at the end of this sketch.
*/

#include "thingProperties.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>

int x = 1;


const int pinoRelay = 5;

Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);



const int pinoSDA = 10;  // Pino SDA
const int pinoSCL = 11;  // Pino SCL

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(500); 

  switchLight = true;

  pinMode(pinoRelay, OUTPUT);

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  Wire.begin(pinoSDA, pinoSCL);
  
  if(!tsl.begin()) {
    Serial.println("Couldn't find TSL2561 sensor");
    while(1);
  }

  // Set the gain to 1x (no gain) - use 16x for very dark situations
  tsl.setGain(TSL2561_GAIN_1X);

  // Set the integration time to 13ms - lower value for bright light, higher for dim light
  tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);
  
  
  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
 */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();


  if(smartModeSwitch == true){
    alternateLight();
  }else{
    onOffMode();
  }
  delay(500); 
}

void onOffMode(){
  if(switchLight == true){
    digitalWrite(pinoRelay, HIGH);
    lightStatus = true;
  }else{
    digitalWrite(pinoRelay, LOW);
    lightStatus = false;
  }
}

void alternateLight(){
    
  sensors_event_t event;
  tsl.getEvent(&event);

  // Display the sensor values
  Serial.println(F("Lux: ")); Serial.println(event.light);
  numero = event.light;

  if(switchLight == true){
    if(event.light < 400){
      digitalWrite(pinoRelay, HIGH);
      Serial.println("Output Relay HIGH");
      lightStatus = true;
      }else{
        digitalWrite(pinoRelay, LOW);
        Serial.println("Output Relay LOW");
        lightStatus = false;
      }
  }else{
    digitalWrite(pinoRelay, LOW);
    lightStatus = false;
  }
}


/*
  Since Numero is READ_WRITE variable, onNumeroChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onNumeroChange()  {
  alternateLight();
}


/*
  Since SwitchLight is READ_WRITE variable, onSwitchLightChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onSwitchLightChange()  {
  
  
}

/*
  Since LightStatus is READ_WRITE variable, onLightStatusChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onLightStatusChange()  {
  // Add your code here to act upon LightStatus change
}

/*
  Since SmartModeSwitch is READ_WRITE variable, onSmartModeSwitchChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onSmartModeSwitchChange()  {
  // Add your code here to act upon SmartModeSwitch change
}