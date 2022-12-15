#include "0_defines.h"
#include "1_state.h"
#include "2_math.h"

void EnvironmentState::update(SystemState &sys)
{
  float dp = getDewPoint(
    sys.getAirTemperature(),
    sys.getAirHumidity());

  this->isRaining = digitalRead(SENSOR_RAINDROP) == 0;
  this->isNight = digitalRead(SENSOR_PHOTO) == 1;
  this->isCondensing = sys.getWindowTemperature() <= dp;
  this->isHot = sys.getAirTemperature() > 28.0;
}
