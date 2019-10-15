#pragma once
#include "Instructions.h"

class RobotState
{
protected:
	const unsigned int xLimit_ = 5;
	const unsigned int yLimit_ = 5;
	unsigned int x_;
	unsigned int y_;
	compassDirection_e f_;

public:
	RobotState();
	~RobotState();

};
