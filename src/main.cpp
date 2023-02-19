#include <WiFi.h>
#include "collectSpotprice.h"
#include "servoControll.h"
#include <ESP32Servo.h>

const char* ssid = "Mandfons household";
const char* password = "Pontus01";
Servo myServo;


void setup() {
  gpio_set_direction(GPIO_NUM_0,GPIO_MODE_OUTPUT);
  gpio_set_direction(GPIO_NUM_5,GPIO_MODE_OUTPUT);
  digitalWrite(0, HIGH);
  myServo.attach(22);
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(5, HIGH);
    WiFi.begin(ssid, password);
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  Serial.println("Connected to WiFi");
}

void loop() {

  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(5, HIGH);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Connection to WiFi was lost.. Trying to re-connect...");
    delay(1000);
    }
  }
  digitalWrite(5, LOW);
  //float collectSpotprice();
  //float spotPrice = collectSpotprice();
  int test;
  test = 0;
  int currentHour = getTimeForHour(test);
  double currentSpotPrice = getSpotpriceForHour(currentHour);
   Serial.print("Current hour: ");
  Serial.println(currentHour);
  Serial.print("Spot price for current hour: ");
  Serial.println(currentSpotPrice);
 // Serial.print("Spot price: ");
 // Serial.println(spotPrice);
 // setServoPosition(spotPrice, myServo);
  
  delay(10000); // Wait for 5 seconds before checking again
}