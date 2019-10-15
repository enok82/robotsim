#pragma once
#include "Instructions.h"

class VehicleState
{
protected:
	const unsigned int xLimit_ = 5;
	const unsigned int yLimit_ = 5;
	unsigned int x_;
	unsigned int y_;
	compassDirection_e f_;

public:
	VehicleState();
	~VehicleState();

};
