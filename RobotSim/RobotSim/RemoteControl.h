#pragma once
#include <vector>
#include <string>
#include <regex>
#include <map>

#include "Controllable.h"

class RemoteControl
{
private:
	std::regex placeCommand;
	std::regex moveCommand;
	std::regex leftCommand;
	std::regex rightCommand;
	std::regex reportCommand;

	std::map<std::string, compassDirection_e> directionMap = {
	{"NORTH", compassDirection_e::NORTH},
	{"SOUTH", compassDirection_e::SOUTH},
	{"WEST", compassDirection_e::WEST},
	{"EAST", compassDirection_e::EAST}
	};

	std::vector<std::regex> commandList = { moveCommand, leftCommand, rightCommand, reportCommand, placeCommand };

	IControllable &controllable_;

	std::vector<std::string> verifiedInstructions_;

public:
	RemoteControl(IControllable & controllable);
	~RemoteControl();

	void Run(void);

	void Parse(std::vector<std::string> inputData);
};

