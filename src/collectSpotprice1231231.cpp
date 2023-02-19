#include <HTTPClient.h>
#include <ArduinoJson.h>

float collectSpotprice() {
  float spotPrice;
  HTTPClient http;
  String url = "https://www.elbruk.se/timpriser-se3-stockholm";
  http.begin(url);
  int httpCode = http.GET();
  String payload = http.getString();
  http.end();
  
  // Find the spot price in the payload
 int startIndex = payload.lastIndexOf("Aktuellt pris");
 if (startIndex >= 0) {
  startIndex += 51;
  int endIndex = payload.indexOf("</span> <span>öre/kWh</", startIndex);
  String spotPriceStr = payload.substring(startIndex, endIndex);
  // Remove any commas from the string and convert to float
  String processedStr = "";
  for (int i = 0; i < spotPriceStr.length(); i++) {
    char c = spotPriceStr.charAt(i);
    if (c != ',' && c != '.') {
      processedStr += c;
    }
    if (c == ',') {
      processedStr += '.';
    }
  }
  spotPrice = processedStr.toFloat();
 }
else {
  Serial.println("Substring not found in payload");
  spotPrice = 1337;
} 
  return spotPrice;

}