#include <ThingSpeak.h>

#include "0_defines.h"
#include "4_thingspeak.h"

void thingspeakSetToManual()
{
  ThingSpeak.writeField(
    THINGSPEAK_CHANNEL_ID,
    THINGSPEAK_FIELD_IS_AUTO,
    0,
    THINGSPEAK_WRITE_API_KEY
  );
}

void thingspeakUpdateAuto(SystemState &sys)
{
  ThingSpeak.writeField(
    THINGSPEAK_CHANNEL_ID,
    THINGSPEAK_FIELD_WINDOW_STATUS,
    sys.windowIsOpened,
    THINGSPEAK_WRITE_API_KEY
  );
  ThingSpeak.writeField(
    THINGSPEAK_CHANNEL_ID,
    THINGSPEAK_FIELD_CURTAIN_STATUS,
    sys.curtainIsOpened,
    THINGSPEAK_WRITE_API_KEY
  );
  ThingSpeak.writeField(
    THINGSPEAK_CHANNEL_ID,
    THINGSPEAK_FIELD_DEFOGGER_STATUS,
    sys.defoggerIsActive,
    THINGSPEAK_WRITE_API_KEY
  );
}

void thingspeakGetUserData(SystemState &sys)
{
  sys.isAutoMode = ThingSpeak.readIntField(
    THINGSPEAK_CHANNEL_ID,
    THINGSPEAK_FIELD_IS_AUTO,
    THINGSPEAK_READ_API_KEY
  );

  if (sys.isAutoMode) {
    return;
  }

  sys.windowIsOpened = ThingSpeak.readIntField(
    THINGSPEAK_CHANNEL_ID,
    THINGSPEAK_FIELD_IS_AUTO,
    THINGSPEAK_READ_API_KEY
  );
  sys.curtainIsOpened = ThingSpeak.readIntField(
    THINGSPEAK_CHANNEL_ID,
    THINGSPEAK_FIELD_CURTAIN_STATUS,
    THINGSPEAK_READ_API_KEY
  );
  sys.defoggerIsActive = ThingSpeak.readIntField(
    THINGSPEAK_CHANNEL_ID,
    THINGSPEAK_FIELD_DEFOGGER_STATUS,
    THINGSPEAK_READ_API_KEY
  );
}
