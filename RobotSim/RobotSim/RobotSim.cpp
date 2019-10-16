#include "pch.h"
#include <iostream>
#include <stdlib.h>
#include "Robot.h"
#include "RemoteControl.h"
#include "RobotSim.h"

int main(int argc, char *argv[])
{
	if ((argc < 2) || (argc > 2))
	{
		std::string executable(argv[0]);
		size_t pos = 0;

		while ((pos = executable.substr(0, pos).find("\\")) != std::string::npos) //TODO: not working
		{
			;
		}

		std::cout << "Please supply " << executable.substr(0, pos) << " with a file containing instructions to the vehicle" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	Robot wally;

	Instructions instructions;

	RemoteControl remoteControl(wally);

	instructions.Parse();

	remoteControl.Program(instructions);

	remoteControl.Run();
}
