#pragma once
#include <vector>
#include <fstream>

class InputAquisition
{
private:
	std::ifstream instructionsFile;

public:
	InputAquisition(int argc, char *argv[]);
	~InputAquisition();

	std::vector<std::string> AquireInput(void);
};
