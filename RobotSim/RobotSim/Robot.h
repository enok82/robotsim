#pragma once
#include "RobotState.h"
#include "Controllable.h"
#include <string>

class Robot : public IControllable, public VehicleState
{
public:
	Robot();
	~Robot();

	void Place(unsigned int x, unsigned int y, compassDirection_e f);

	void TurnLeft(void);

	void TurnRight(void);

	void MoveForward(void);

	void Report(void);

	void TurnRobot(turnDirection_e t);

	void ConstrainMovement(unsigned int axis, unsigned int limit, int step);

	std::string GetDirectionString(void);
};

