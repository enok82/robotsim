#pragma once
#include "Instructions.h"

class IControllable
{
public:
	virtual ~IControllable() {};

	virtual void Place(unsigned int x, unsigned int y, compassDirection_e f) = 0;

	virtual void TurnLeft(void) = 0;

	virtual void TurnRight(void) = 0;

	virtual void MoveForward(void) = 0;

	virtual void Report(void) = 0;
};

