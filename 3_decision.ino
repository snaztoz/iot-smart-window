#include "3_decision.h"
#include "4_thingspeak.h"

void DecisionMaker::makeDecision(EnvironmentState &env, SystemState &sys)
{
  if (!sys.isAutoMode || env == this->prevState) {
    // just skip if it is not in auto mode or there is no change
    // in environment condition
    return;
  }

  // curtain condition is only based on whether it
  // is currently night or day
  sys.curtainIsOpened = !env.isNight;

  // defogger condition is only based on whether it
  // is currently condensing or not
  sys.defoggerIsActive = env.isCondensing;

  // window conditions

  std::array<bool, 3> windowClosingConditions = {
    env.isNight,
    env.isRaining,
    !env.isHot,
  };

  int shouldCloseWindowConditionsCount = std::count_if(
    windowClosingConditions.begin(),
    windowClosingConditions.end(),
    [](bool shouldClose) { return shouldClose; }
  );

  if (shouldCloseWindowConditionsCount == 3) {
    sys.windowIsOpened = false;
  } else if (shouldCloseWindowConditionsCount == 0) {
    sys.windowIsOpened = true;
  } else {
    // can't determine automatically, user must
    // handle manually
    sys.isAutoMode = false;
    thingspeakSetToManual();
  }

  // update new states
  this->prevState = env;
}
