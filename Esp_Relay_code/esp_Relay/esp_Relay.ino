#include <WiFi.h>
//#include <HTTPClient.h>
//#include<iostream>
//#include <string>
using namespace std;

String lux;

const int pinoRelay = 5;
const int pinoInputRelay = 7;

unsigned long previousMillis = 0;
const long interval = 5000; 

int relayState = 0;

void setup() {
  Serial.begin(115200);
  
  pinMode(pinoRelay, OUTPUT);
  pinMode(pinoInputRelay, INPUT);

  digitalWrite(pinoRelay, LOW);

}

void loop() {

  relayState = digitalRead(pinoInputRelay);
  Serial.println(relayState);


  if(relayState == HIGH){
    digitalWrite(pinoRelay, HIGH);
  }else{
    digitalWrite(pinoRelay, LOW);
  }

  delay(3000);

}
