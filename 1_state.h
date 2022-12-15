#ifndef H_1_STATE
#define H_1_STATE

#include <ThingSpeak.h>
#include <DHT.h>

#include "0_defines.h"

class SystemState
{
public:
  bool isAutoMode;
  bool curtainIsOpened;
  bool windowIsOpened;
  bool defoggerIsActive;

  DHT dht{ SENSOR_DHT, DHT11 };
  DHT windowDht{ SENSOR_WINDOW_TEMPERATURE, DHT11 };

  SystemState()
  {
    isAutoMode = true;
    curtainIsOpened = false;
    windowIsOpened = false;
    defoggerIsActive = false;
  }

  float getAirTemperature()
  {
    return dht.readTemperature();
  }

  float getAirHumidity()
  {
    return dht.readHumidity();
  }

  float getWindowTemperature()
  {
    return windowDht.readTemperature();
  }
};

class EnvironmentState
{
public:
  bool isRaining;
  bool isNight;
  bool isCondensing;
  bool isHot;

  EnvironmentState()
  {
    isRaining = false;
    isNight = false;
    isCondensing = false;
    isHot = false;
  }

  void update(SystemState &sys);

  bool operator== (EnvironmentState &rhs)
  {
    return isCondensing == rhs.isCondensing
        && isHot == rhs.isHot
        && isNight == rhs.isNight
        && isRaining == rhs.isRaining;
  }
};

#endif
