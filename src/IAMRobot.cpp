#include <IAMRobot.h>

using namespace frc;

IAMRobot::IAMRobot(){
	flTalon = new CANTalon(flTalID);
	rlTalon = new CANTalon(rlTalID);
	frTalon = new CANTalon(frTalID);
	rrTalon = new CANTalon(rrTalID);
	robotDrive = new RobotDrive(flTalon, rlTalon, frTalon, rrTalon);
	flEncoder = new PWM(flEncID);
	frEncoder = new PWM(frEncID);
	drive = new DriveSystem(robotDrive, flEncoder, frEncoder, 0);

	gearClawNoid = new DoubleSolenoid(pcmID, clawNoidForwardID, clawNoidReverseID);
	gearRaiseNoid = new DoubleSolenoid(pcmID, raiseNoidForwardID, raiseNoidReverseID);
	gear = new GearSystem(gearRaiseNoid, gearClawNoid);
	gearSensor = new DigitalInput(gearSensorID);
	pegSensor = new DigitalInput(pegSensorID);

	climbRoller = new CANTalon(rollerTalID);
	climbLeft = new CANTalon(intake1TalID);
	climbRight = new CANTalon(intake2TalID);
	climb = new ClimbSystem(climbRoller, climbLeft, climbRight);

	ballWall1Tal = new CANTalon(ballPick1TalID);
	ballWall2Tal = new CANTalon(ballPick2TalID);
	pickupSol = new DoubleSolenoid(pcmID, ballSolForwardID, ballSolReverseID);
	ball = new BallSystem(ballWall1Tal, ballWall2Tal, pickupSol);

	control1 = new XboxController(controller1ID);
	control2 = new XboxController(controller2ID);
	tlp = new Teleop(control1, control2, drive, gear, gearSensor, pegSensor, climb, ball);
	//ato = new Auto(drive, gear, gearSensor, pegSensor);
}

IAMRobot::~IAMRobot(){
	delete flTalon;
	delete rlTalon;
	delete frTalon;
	delete rrTalon;
	delete robotDrive;
	delete drive;
	delete gearClawNoid;
	delete gearRaiseNoid;
	delete gear;
	delete control1;
	delete control2;
	delete tlp;
	//delete ato;
	delete gearSensor;
	delete pegSensor;
	delete climbRoller;
	delete climbLeft;
	delete climbRight;
	delete climb;
	delete ballWall1Tal;
	delete ballWall2Tal;
	delete pickupSol;
	delete ball;
	delete flEncoder;
	delete frEncoder;
}

void IAMRobot::RobotInit() {
	chooser.AddDefault(autoNameDefault, autoNameDefault);
	chooser.AddObject(autoNameCustom, autoNameCustom);
	SmartDashboard::PutData("Auto Modes", &chooser);
}

void IAMRobot::AutonomousInit(){
	autoSelected = chooser.GetSelected();
	std::string autoSelected = SmartDashboard::GetString("Auto Selector", autoNameDefault);
	std::cout << "Auto selected: " << autoSelected << std::endl;

	if (autoSelected == autoNameCustom) {
		// Custom Auto goes here
	} else {
		// Default Auto goes here
	}
	//ato->AutonRun(true);
}

void IAMRobot::AutonomousPeriodic() {
	if (autoSelected == autoNameCustom) {
		// Custom Auto goes here
	} else {
		// Default Auto goes here
	}
}

void IAMRobot::TeleopInit() {

}

void IAMRobot::TeleopPeriodic() {
	tlp->TeleopRun(true);
}

void IAMRobot::TestPeriodic() {

}

START_ROBOT_CLASS(IAMRobot)
