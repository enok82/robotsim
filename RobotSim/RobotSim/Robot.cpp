#include "pch.h"

#include <iostream>

#include "Robot.h"

Robot::Robot() : VehicleState(), isPlaced(false)
{
}

Robot::~Robot()
{
}

void Robot::Place(unsigned int y,unsigned int x, compassDirection_e f)
{
	x_ = x <= xLimit_ ? x : xLimit_;
	y_ = y <= yLimit_ ? y : yLimit_;
	f_ = f;

	isPlaced = true;
}

void Robot::TurnRobot(turnDirection_e t)
{
	if (isPlaced == true)
	{
		switch (f_)
		{
		case compassDirection_e::NORTH:
		{
			f_ = t == turnDirection_e::LEFT ? compassDirection_e::WEST : compassDirection_e::EAST;
			break;
		}
		case compassDirection_e::SOUTH:
		{
			f_ = t == turnDirection_e::LEFT ? compassDirection_e::EAST : compassDirection_e::WEST;
			break;
		}
		case compassDirection_e::EAST:
		{
			f_ = t == turnDirection_e::LEFT ? compassDirection_e::NORTH : compassDirection_e::SOUTH;
			break;
		}
		case compassDirection_e::WEST:
		{
			f_ = t == turnDirection_e::LEFT ? compassDirection_e::SOUTH : compassDirection_e::NORTH;
			break;
		}
		default:
		{
			break;
		}
		}
	}
}

void Robot::TurnLeft(void)
{
	TurnRobot(turnDirection_e::LEFT);
}

void Robot::TurnRight(void)
{
	TurnRobot(turnDirection_e::RIGHT);
}

void Robot::MoveForward(void)
{
	switch (f_)
	{
	case compassDirection_e::NORTH:
	{
		ConstrainMovement(x_, xLimit_, 1);
		break;
	}
	case compassDirection_e::SOUTH:
	{
		ConstrainMovement(x_, xLimit_, -1);
		break;
	}
	case compassDirection_e::EAST:
	{
		ConstrainMovement(y_, yLimit_, 1);
		break;
	}
	case compassDirection_e::WEST:
	{
		ConstrainMovement(y_, yLimit_, -1);
		break;
	}
	default:
	{
		break;
	}
	}
}

void Robot::ConstrainMovement(unsigned int &axis, unsigned int limit, int step)
{
	if (isPlaced == true)
	{
		axis = (axis + step) <= limit ? axis + step : axis;
	}
}

std::string Robot::GetDirectionString(void)
{
	std::string directionString;

	switch (f_)
	{
	case compassDirection_e::NORTH:
	{
		directionString = "NORTH";
		break;
	}
	case compassDirection_e::SOUTH:
	{
		directionString = "SOUTH";
		break;
	}
	case compassDirection_e::EAST:
	{
		directionString = "EAST";
		break;
	}
	case compassDirection_e::WEST:
	{
		directionString = "WEST";
		break;
	}
	default:
	{
		break;
	}
	}

	return directionString;
}

void Robot::Report(void)
{
	if (isPlaced == true)
	{
		std::cout << y_ << ',' << x_ << ',' << GetDirectionString() << std::endl;
	}
}
