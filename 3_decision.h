#ifndef H_3_HANDLER
#define H_3_HANDLER

#include "1_state.h"

class DecisionMaker
{
public:
  void makeDecision(EnvironmentState &env, SystemState &system);

private:
  EnvironmentState prevState;
};

#endif
