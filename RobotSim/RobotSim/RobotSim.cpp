#include "pch.h"

#include <iostream>

#include "Robot.h"
#include "RemoteControl.h"
#include "RobotSim.h"
#include "InputAquisition.h"

int main(int argc, char *argv[])
{
	InputAquisition inputAquisition(argc, argv);

	Robot wally;

	RemoteControl remoteControl(wally);

	remoteControl.Parse(inputAquisition.AquireInput());

	remoteControl.Run();
}
