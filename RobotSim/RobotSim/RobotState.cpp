#include "pch.h"
#include "RobotState.h"

RobotState::RobotState() : x_(0), y_(0), f_(compassDirection_e::NORTH)
{
}

RobotState::~RobotState()
{
}
