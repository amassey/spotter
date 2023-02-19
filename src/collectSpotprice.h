#ifndef COLLECTSPOTPRICE_H
#define COLLECTSPOTPRICE_H


#include <Arduino.h>

float collectSpotprice();
extern float spotArray[48][2];
float getSpotpriceForHour(int hour);
String getTimeForHour(int hour);

#endif