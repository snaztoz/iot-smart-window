#include "2_math.h"

float getDewPoint(float temperature, float humidity)
{
  return temperature - ((100 - humidity) / 5);
}
