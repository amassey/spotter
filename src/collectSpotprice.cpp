#include "collectSpotprice.h"
#include <HTTPClient.h>
#include <ArduinoJson.h>


float collectSpotprice() {
  HTTPClient http;
  String url = "https://www.elbruk.se/timpriser-se3-stockholm";
  http.begin(url);
  int httpCode = http.GET();
  
  if (httpCode > 0) {
    Serial.println("Payload received");
    String payload = http.getString();
    int startIndex = payload.lastIndexOf("table table-striped mb30");
    
    if (startIndex >= 0) {
      for (int i = 0; i < 48; i++) {
        startIndex = payload.lastIndexOf("Kl.", startIndex) + 2;
        int endIndex = startIndex + 2;
        String spotTimeStr = payload.substring(startIndex, endIndex);
        String processedStr = "";
        for (int j = 0; j < spotTimeStr.length(); j++) {
          char c = spotTimeStr.charAt(j);
          if (c != ',' && c != '.') {
            processedStr += c;
          }
          if (c == ',') {
            processedStr += '.';
          }
        }
        float spotTime = processedStr.toFloat();
        spotArray[i][0] = spotTime;

        startIndex = payload.lastIndexOf("Pris");
        startIndex = payload.indexOf(">", startIndex) + 1;
        endIndex = payload.indexOf("<", startIndex);
        String spotPriceStr = payload.substring(startIndex, endIndex);
        processedStr = "";
        for (int j = 0; j < spotPriceStr.length(); j++) {
          char c = spotPriceStr.charAt(j);
          if (c != ',' && c != '.') {
            processedStr += c;
          }
          if (c == ',') {
            processedStr += '.';
          }
        }
        float spotPrice = processedStr.toFloat();
        spotArray[i][1] = spotPrice;
      }
    }
    else {
      Serial.println("Table not found in payload");
    }
    http.end();
  }
  else {
    Serial.println("Failed to connect to server");
  }
}

float getSpotpriceForHour(int hour) {
  if (hour >= 0 && hour < 24) {
    int index = hour * 2;
    if (index < 48) {
      return spotArray[index][1];
    }
    else {
      Serial.println("Invalid hour value");
      return -1;
    }
  }
  else {
    Serial.println("Invalid hour value");
    return -1;
  }
}

float getTimeForHour(int hour) {
  if (hour >= 0 && hour < 24) {
    int index = hour * 2;
    if (index < 48) {
      return spotArray[index][0];
    }
    else {
      Serial.println("Invalid hour value");
      return -1;
    }
  }
  else {
    Serial.println("Invalid hour value");
    return -1;
  }
}