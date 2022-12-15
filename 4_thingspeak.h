#ifndef H_4_THINGSPEAK
#define H_4_THINGSPEAK

#include "1_state.h"

void thingspeakSetToManual();
void thingspeakUpdateAuto(SystemState &sys);
void thingspeakGetUserData(SystemState &sys);

#endif
