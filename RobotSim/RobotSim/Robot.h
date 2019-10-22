#pragma once
#include "RobotState.h"
#include "Controllable.h"
#include <string>

class Robot : public IControllable, public VehicleState
{
private:
	bool isPlaced;

	std::string GetDirectionString(void);

	void TurnRobot(turnDirection_e t);

	void ConstrainMovement(unsigned int &axis, unsigned int limit, int step);

public:
	Robot();
	~Robot();

	void Place(unsigned int y, unsigned int x, compassDirection_e f);

	void TurnLeft(void);

	void TurnRight(void);

	void MoveForward(void);

	void Report(void);
};

