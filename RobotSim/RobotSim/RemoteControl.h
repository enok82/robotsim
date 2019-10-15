#pragma once
#include "Controllable.h"

class RemoteControl
{
private:
	IControllable &controllable_;

public:
	RemoteControl(IControllable & controllable);
	~RemoteControl();

	void Program(Instructions & instructions);

	void Run(void);
};

