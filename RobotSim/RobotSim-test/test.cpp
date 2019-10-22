#include "pch.h"
#include "../RobotSim/InputAquisition.h"
#include "../RobotSim/Robot.h"
#include "../RobotSim/RemoteControl.h"

TEST(InputAquisistion, TooFewArguments) {
	char *argv[2] = { "filename.exe", "inpufile.txt" };

	ASSERT_DEATH({ InputAquisition inputAquisition(1, argv); }, ".*");
}

TEST(InputAquisistion, TooManyArguments) {
	char *argv[2] = { "filename.exe", "inpufile.txt" };

	ASSERT_DEATH({ InputAquisition inputAquisition(3, argv); }, ".*");
}

TEST(InputAquisistion, MissingFile) {
	char *argv[2] = { "filename.exe", "inputfile.txt" };

	ASSERT_DEATH({ InputAquisition inputAquisition(2, argv); }, ".*");
}

TEST(InputAquisistion, AquireTestData) {
	char *argv[2] = { "filename.exe", "../RobotSim/input_a.txt" };

	InputAquisition inputAquisition(2, argv);

	std::vector<std::string> receivedVector = inputAquisition.AquireInput();

	ASSERT_EQ(receivedVector.size(), 3);

	ASSERT_STREQ(receivedVector[0].c_str(), "PLACE 0,0,NORTH");

	ASSERT_STREQ(receivedVector[1].c_str(), "MOVE");
	
	ASSERT_STREQ(receivedVector[2].c_str(), "REPORT");
}

TEST(RemoteControl, ParseOk) {
	std::vector<std::string> inputData = { "PLACE 0,0,NORTH", "LEFT", "LEFT" };

	Robot robot;

	RemoteControl remoteControl(robot);

	remoteControl.Parse(inputData);
}
TEST(RemoteControl, ParseSyntaxError) {
	std::vector<std::string> inputData = { "PLACE 0,0,NORTH", "LEFT", "LEF" };

	Robot robot;

	RemoteControl remoteControl(robot);

	ASSERT_DEATH({ remoteControl.Parse(inputData); }, ".*");
}

TEST(RemoteControl, RunSuccess)
{
	testing::internal::CaptureStdout();

	std::vector<std::string> inputData = { "PLACE 0,0,NORTH", "MOVE", "REPORT" };

	Robot robot;

	RemoteControl remoteControl(robot);

	remoteControl.Parse(inputData);

	remoteControl.Run();

	std::string report(testing::internal::GetCapturedStdout());

	ASSERT_STREQ(report.c_str(), "0,1,NORTH\n");
}

TEST(Robot, Place)
{
	testing::internal::CaptureStdout();

	Robot *robot;

	robot = new Robot;

	robot->Place(5, 5, compassDirection_e::EAST);

	robot->Report();

	std::string report(testing::internal::GetCapturedStdout());

	ASSERT_STREQ(report.c_str(), "5,5,EAST\n");
}

TEST(Robot, MoveOkXPos)
{
	testing::internal::CaptureStdout();

	Robot *robot;

	robot = new Robot;

	robot->Place(4, 4, compassDirection_e::EAST);

	robot->MoveForward();

	robot->Report();

	std::string report(testing::internal::GetCapturedStdout());

	ASSERT_STREQ(report.c_str(), "5,4,EAST\n");
}

TEST(Robot, MoveOkXNeg)
{
	testing::internal::CaptureStdout();

	Robot *robot;

	robot = new Robot;

	robot->Place(4, 4, compassDirection_e::WEST);

	robot->MoveForward();

	robot->Report();

	std::string report(testing::internal::GetCapturedStdout());

	ASSERT_STREQ(report.c_str(), "3,4,WEST\n");
}

TEST(Robot, MoveOkYPos)
{
	testing::internal::CaptureStdout();

	Robot *robot;

	robot = new Robot;

	robot->Place(4, 4, compassDirection_e::NORTH);

	robot->MoveForward();

	robot->Report();

	std::string report(testing::internal::GetCapturedStdout());

	ASSERT_STREQ(report.c_str(), "4,5,NORTH\n");
}

TEST(Robot, MoveOkYNeg)
{
	testing::internal::CaptureStdout();

	Robot *robot;

	robot = new Robot;

	robot->Place(4, 4, compassDirection_e::SOUTH);

	robot->MoveForward();

	robot->Report();

	std::string report(testing::internal::GetCapturedStdout());

	ASSERT_STREQ(report.c_str(), "4,3,SOUTH\n");
}

TEST(Robot, MoveLimitedYPos)
{
	testing::internal::CaptureStdout();

	Robot *robot;

	robot = new Robot;

	robot->Place(5, 5, compassDirection_e::NORTH);

	robot->MoveForward();

	robot->Report();

	std::string report(testing::internal::GetCapturedStdout());

	ASSERT_STREQ(report.c_str(), "5,5,NORTH\n");
}

TEST(Robot, MoveLimitedYNeg)
{
	testing::internal::CaptureStdout();

	Robot *robot;

	robot = new Robot;

	robot->Place(5, 0, compassDirection_e::SOUTH);

	robot->MoveForward();

	robot->Report();

	std::string report(testing::internal::GetCapturedStdout());

	ASSERT_STREQ(report.c_str(), "5,0,SOUTH\n");
}

TEST(Robot, MoveLimitedXPos)
{
	testing::internal::CaptureStdout();

	Robot *robot;

	robot = new Robot;

	robot->Place(5, 5, compassDirection_e::EAST);

	robot->MoveForward();

	robot->Report();

	std::string report(testing::internal::GetCapturedStdout());

	ASSERT_STREQ(report.c_str(), "5,5,EAST\n");
}

TEST(Robot, TurnLeft)
{
	testing::internal::CaptureStdout();

	Robot *robot;

	robot = new Robot;

	robot->Place(0, 5, compassDirection_e::WEST);

	robot->TurnLeft();

	robot->Report();

	std::string report(testing::internal::GetCapturedStdout());

	ASSERT_STREQ(report.c_str(), "0,5,SOUTH\n");

	robot->TurnLeft();

	testing::internal::CaptureStdout();

	robot->Report();

	report = testing::internal::GetCapturedStdout();

	ASSERT_STREQ(report.c_str(), "0,5,EAST\n");

	robot->TurnLeft();

	testing::internal::CaptureStdout();

	robot->Report();

	report = testing::internal::GetCapturedStdout();

	ASSERT_STREQ(report.c_str(), "0,5,NORTH\n");

	robot->TurnLeft();

	testing::internal::CaptureStdout();

	robot->Report();

	report = testing::internal::GetCapturedStdout();

	ASSERT_STREQ(report.c_str(), "0,5,WEST\n");
}

TEST(Robot, TurnRight)
{
	testing::internal::CaptureStdout();

	Robot *robot;

	robot = new Robot;

	robot->Place(0, 5, compassDirection_e::WEST);

	robot->TurnRight();

	robot->Report();

	std::string report(testing::internal::GetCapturedStdout());

	ASSERT_STREQ(report.c_str(), "0,5,NORTH\n");

	robot->TurnRight();

	testing::internal::CaptureStdout();

	robot->Report();

	report = testing::internal::GetCapturedStdout();

	ASSERT_STREQ(report.c_str(), "0,5,EAST\n");

	robot->TurnRight();

	testing::internal::CaptureStdout();

	robot->Report();

	report = testing::internal::GetCapturedStdout();

	ASSERT_STREQ(report.c_str(), "0,5,SOUTH\n");

	robot->TurnRight();

	testing::internal::CaptureStdout();

	robot->Report();

	report = testing::internal::GetCapturedStdout();

	ASSERT_STREQ(report.c_str(), "0,5,WEST\n");
}
