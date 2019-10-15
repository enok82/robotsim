#pragma once
enum class compassDirection_e {
	NORTH,
	SOUTH,
	WEST,
	EAST,
};

enum class turnDirection_e {
	LEFT,
	RIGHT,
};

class Instructions
{
public:
	Instructions();
	~Instructions();

	void Parse(void);
};
