#pragma once
#include "Instructions.h"

class Controllable
{
public:
	Controllable();
	~Controllable();

	virtual void Place(unsigned int x, unsigned int y, compassDirection_e f) = 0;

	virtual void TurnLeft(void) = 0;

	virtual void TurnRight(void) = 0;

	virtual void MoveForward(void) = 0;

};

