#include <DHT.h>
#include <ThingSpeak.h>
#include <ESP8266WiFi.h>

#include "0_defines.h"
#include "1_state.h"
#include "3_decision.h"
#include "4_thingspeak.h"

WiFiClient client;

EnvironmentState env;
SystemState sys;
DecisionMaker dm;

void setup()
{
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) { //Cek koneksi Wifi.
    delay(500);
    Serial.print(".");
  }

  pinMode(SENSOR_RAINDROP, INPUT);
  pinMode(SENSOR_PHOTO, INPUT);
  pinMode(SENSOR_DHT, INPUT);
  pinMode(SENSOR_WINDOW_TEMPERATURE, INPUT);

  pinMode(OUTPUT_WINDOW, OUTPUT);
  pinMode(OUTPUT_GORDEN, OUTPUT);
  pinMode(OUTPUT_DEFOGGER, OUTPUT);

  ThingSpeak.begin(client);

  sys.dht.begin();
  sys.windowDht.begin();

  sys.isAutoMode = ThingSpeak.readIntField(
    THINGSPEAK_CHANNEL_ID,
    THINGSPEAK_FIELD_IS_AUTO,
    THINGSPEAK_READ_API_KEY
  );
}

void loop()
{
  env.update(sys);

  Serial.printf(
    "isRaining: %d; isNight: %d; isCondensing: %d; isHot: %d\n",
    env.isRaining,
    env.isNight,
    env.isCondensing,
    env.isHot);

  if (sys.isAutoMode) {
    dm.makeDecision(env, sys);
    thingspeakUpdateAuto(sys);
  } else {
    thingspeakGetUserData(sys);
  }

  Serial.printf(
    "isAuto: %d; curtainIsOpened: %d; windowIsOpened: %d; defoggerIsActive: %d\n\n",
    sys.isAutoMode,
    sys.curtainIsOpened,
    sys.windowIsOpened,
    sys.defoggerIsActive);

  digitalWrite(OUTPUT_WINDOW, sys.windowIsOpened);
  digitalWrite(OUTPUT_GORDEN, sys.curtainIsOpened);
  digitalWrite(OUTPUT_DEFOGGER, sys.defoggerIsActive);

  delay(3000);
}
