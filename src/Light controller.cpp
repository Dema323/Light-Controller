#include <ArduinoOTA.h>
#include <Arduino.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "a17ca41e15d84cbd86870de0b1e1fff7";
char ssid[] = "WiFi-2.4-D4F0";
char pass[] = "A26YXkP73nuz";

int potPin= A0;  //Declare potPin to be analog pin A0
int LEDPin= D4;  // Declare LEDPin to be arduino pin 9
int readValue;  // Use this variable to read Potentiometer
int writeValue; // Use this variable for writing to LED
int brightness = 0; // Start off with LED off
int potValue;

void setup() {
  WiFi.mode(WIFI_STA);
  Serial.begin(9600);      // turn on Serial Port
  Blynk.begin(auth, ssid, pass);
  while (Blynk.connect() == false) {}
  //ArduinoOTA.setHostname("xxxxxxx"); // OPTIONAL
  ArduinoOTA.begin();
  pinMode(potPin, INPUT);  //set potPin to be an input
  pinMode(LEDPin, OUTPUT); //set LEDPin to be an OUTPUT
  potValue = analogRead(potPin);
}

BLYNK_WRITE(V1) // Slider to led
{

  brightness = param.asInt(); // Get slider value.
  analogWrite(LEDPin, brightness); //Send data to LED
}

void Potentiometer() // Potentiometer to led
{
  readValue = analogRead(potPin);
  if(potValue != readValue){
    brightness = (255./1023.) * readValue; //Calculate Write Value for LED
    analogWrite(LEDPin, brightness); //Send data to LED
    potValue = analogRead(potPin);
    //Blynk.virtualWrite(V1, brightness); //Send feedback to slider Widget
  }
  delay(300);
}

void loop() {
 Blynk.run();
 Potentiometer();
 ArduinoOTA.handle();
}
