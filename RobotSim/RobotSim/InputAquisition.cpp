#include "pch.h"

#include <iostream>
#include <stdlib.h>
#include <string>

#include "InputAquisition.h"

InputAquisition::InputAquisition(int argc, char * argv[])
{
	if ((argc < 2) || (argc > 2))
	{
		std::string executable(argv[0]);
		size_t pos = 0;

		while ((pos = executable.find('\\')) != std::string::npos)
		{
			executable = executable.substr(pos + 1, std::string::npos);
		}

		std::cout << "Please supply " << executable << " with ONE path to file containing instructions to the vehicle" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	else
	{
		std::string fileName = argv[1];

		instructionsFile.open(fileName, std::ifstream::in);

		if (!instructionsFile.is_open())
		{
			perror(("Could not open " + fileName).c_str());
		}
	}
}

InputAquisition::~InputAquisition()
{
	
}

std::vector<std::string> InputAquisition::AquireInput(void)
{
	std::vector<std::string> aquiredLines;
	std::string line;

	while (getline(instructionsFile, line))
	{
		aquiredLines.emplace_back(line);
	}

	return aquiredLines;
}
