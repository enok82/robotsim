#include "pch.h"

#include <stdlib.h>
#include <iostream>

#include "RemoteControl.h"

RemoteControl::RemoteControl(IControllable & controllable) : placeCommand("(PLACE [0-9]{1,2},[0-9]{1,2},)((NORTH)|(SOUTH)|(WEST)|(EAST))"),
	moveCommand("MOVE"),
	leftCommand("LEFT"),
	rightCommand("RIGHT"),
	reportCommand("REPORT"),
	controllable_(controllable)
{
}

RemoteControl::~RemoteControl()
{
}

void RemoteControl::Run(void)
{
	for (std::string instruction : verifiedInstructions_)
	{
		if (std::regex_search(instruction, moveCommand))
		{
			controllable_.MoveForward();
		}
		else if (std::regex_search(instruction, leftCommand))
		{
			controllable_.TurnLeft();
		}
		else if (std::regex_search(instruction, rightCommand))
		{
			controllable_.TurnRight();
		}
		else if (std::regex_search(instruction, reportCommand))
		{
			controllable_.Report();
		}
		else if (std::regex_search(instruction, placeCommand))
		{
			std::string arguments = instruction.substr(instruction.find(' ') + 1, std::string::npos);
			
			size_t token = arguments.find(',');
			
			unsigned int y = stoi(arguments.substr(0, token));
			
			arguments = arguments.substr(token + 1, std::string::npos);

			token = arguments.find(',');

			unsigned int x  = stoi(arguments.substr(0, token));
			
			arguments = arguments.substr(token + 1, std::string::npos);

			controllable_.Place(y, x, directionMap[arguments]);
		}
	}
}

void RemoteControl::Parse(std::vector<std::string> inputData)
{
	std::vector<std::string>::iterator inputDataIterator;

	unsigned int lineNumber = 0;

	for (inputDataIterator = inputData.begin(); inputDataIterator != inputData.end(); inputDataIterator++, lineNumber++)
	{
		bool commandVerified = false;

		std::vector<std::regex>::iterator commandIterator = commandList.begin();

		while ((commandIterator != commandList.end()) && (commandVerified == false))
		{
			if (std::regex_search(*inputDataIterator, *commandIterator))
			{
				commandVerified = true;
			}

			commandIterator++;
		}

		if (commandVerified == false)
		{
			std::cout << "Missformed command on line " << lineNumber << std::endl << std::endl;

			if (lineNumber >= 1)
			{
				std::cout << lineNumber - 1 << ": " << *(inputDataIterator - 1) << std::endl;
			}
			std::cout << lineNumber << ": " << *(inputDataIterator) << " <--" << std::endl <<
				lineNumber + 1 << ": " << *(inputDataIterator + 1) << std::endl;

			std::exit(EXIT_FAILURE);
		}
	}

	verifiedInstructions_ = inputData;
}
