#include "pch.h"
#include "RobotState.h"

VehicleState::VehicleState() : x_(0), y_(0), f_(compassDirection_e::NORTH)
{
}

VehicleState::~VehicleState()
{
}
