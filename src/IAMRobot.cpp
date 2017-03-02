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
	ato = new Auto(drive, gear, gearSensor, pegSensor);
	cammy = CameraServer::GetInstance();
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
	delete ato;
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
	autoChooser.AddDefault(autoNameDefault, autoNameDefault);
	autoChooser.AddObject(autoNameCustom, autoNameCustom);
	SmartDashboard::PutData("Auto Modes", &autoChooser);

	cammy->StartAutomaticCapture(0);
}

void IAMRobot::AutonomousInit(){
	autoSelected = autoChooser.GetSelected();
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
	teleChooser.AddDefault(teleNameDefault, teleNameDefault);
	teleChooser.AddObject(teleName2ns, teleName2ns);
	teleChooser.AddObject(teleName1s, teleName1s);
	teleChooser.AddObject(teleName2ns, teleName1ns);
	SmartDashboard::PutData("Teleop Modes", &teleChooser);

	teleSelected = teleChooser.GetSelected();
	std::string teleSelected = SmartDashboard::GetString("Teleop Selector", teleNameDefault);
	std::cout << "Teleop selected: " << teleSelected << std::endl;

	if(teleSelected == teleName1s) {
		// Custom Auto goes here
	}
	else if(teleSelected == teleName1ns){

	}
	else if(teleSelected == teleName2ns){

	}
	else {
		// Default Auto goes here
	}
}

void IAMRobot::TeleopPeriodic() {
	/*if(teleSelected == teleName1s) {
		tlp->TeleopRun(Teleop::OneContSensors);
	}
	else if(teleSelected == teleName1ns){
		tlp->TeleopRun(Teleop::OneContNoSensors);
	}
	else if(teleSelected == teleName2ns){
		tlp->TeleopRun(Teleop::TwoContNoSensors);
	}
	else {
		tlp->TeleopRun(Teleop::TwoContSensors);
	}*/

	tlp->TeleopRun(Teleop::TwoContSensors);
}

void IAMRobot::TestPeriodic() {

}

START_ROBOT_CLASS(IAMRobot)
