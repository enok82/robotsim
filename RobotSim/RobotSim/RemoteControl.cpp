#include "pch.h"
#include "RemoteControl.h"

RemoteControl::RemoteControl(IControllable & controllable) : controllable_(controllable)
{
}

RemoteControl::~RemoteControl()
{
}

void RemoteControl::Program(Instructions & instructions)
{
}

void RemoteControl::Run(void)
{
}
