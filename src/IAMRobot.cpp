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
	drive = new DriveSystem(robotDrive, 0);

	gearClawNoid = new DoubleSolenoid(pcmID, clawNoidForwardID, clawNoidReverseID);
	gearRaiseNoid = new DoubleSolenoid(pcmID, raiseNoidForwardID, raiseNoidReverseID);
	gear = new GearSystem(gearRaiseNoid, gearClawNoid);
	gearSensor = new DigitalInput(gearSensorID);
	pegSensor1 = new DigitalInput(pegSensor1ID);
	pegSensor2 = new DigitalInput(pegSensor2ID);

	climb1Roller = new CANTalon(roller1TalID);
	climb2Roller = new CANTalon(roller2TalID);
	climb = new ClimbSystem(climb1Roller, climb2Roller);

	feedingTal = new CANTalon(feederTalID);
	pdp = new PowerDistributionPanel(1);
	meteringTal = new CANTalon(meterTalID);
	shooterTal = new CANTalon(shooterTalID);
	shooterTal->SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);
	shooterTal->SetSensorDirection(false);
	//shooterTal->SetTalonControlMode(CANTalon::kSpeedMode);
	shooterTal->SetInverted(true);
	/*shooterTal->SetEncPosition(0);
	shooterTal->SetPID(0.0, 0.0, 0.0, 0.02);
	shooterTal->SetPosition(0.0);
	shooterTal->EnableControl();*/
	ball = new ShootSystem(feedingTal, meteringTal, shooterTal);

	control1 = new XboxController(controller1ID);
	control2 = new XboxController(controller2ID);
	tlp = new Teleop(control1, control2, drive, gear, gearSensor, pegSensor1, climb, ball);
	ato = new Auto(drive, gear, gearSensor, pegSensor1, ball);
	cammy = CameraServer::GetInstance();
	cammy2 = CameraServer::GetInstance();

	rLED = new Relay(rLEDID, Relay::kBothDirections);
	gLED = new Relay(gLEDID, Relay::kBothDirections);
	bLED = new Relay(bLEDID, Relay::kBothDirections);
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
	delete pegSensor1;
	delete pegSensor2;
	delete climb1Roller;
	delete climb2Roller;
	delete climb;
	delete feedingTal;
	delete pdp;
	delete meteringTal;
	delete shooterTal;
	delete ball;
	delete flEncoder;
	delete frEncoder;
	delete rLED;
	delete gLED;
	delete bLED;
}

void IAMRobot::RobotInit() {
	autoChooser.AddDefault(autoNameDefault, autoNameDefault);
	autoChooser.AddObject(autoNameCustom, autoNameCustom);
	SmartDashboard::PutData("Auto Modes", &autoChooser);

	cammy->StartAutomaticCapture(camera1ID);
	cammy2->StartAutomaticCapture(camera2ID);
}

void IAMRobot::AutonomousInit(){
	autoSelected = autoChooser.GetSelected();
	std::string autoSelected = SmartDashboard::GetString("Auto Selector", autoNameDefault);
	std::cout << "Auto selected: " << autoSelected << std::endl;

	/*if (autoSelected == autoNameCustom) {
		// Custom Auto goes here
		ato->AutonRun(true);
	} else {
		// Default Auto goes here
		ato->AutonRun(false);
	}*/
	//ato->AutoInitialize(false);
	ball->SpinSequence(0.8, 1.0, 0.5, 1.0, 7.0);
	drive->TimeStraightDrive(-0.3, 2.5);
	/*Wait(0.5);
	gear->openClaw();
	gear->lowerClaw();
	Wait(0.5);
	drive->TimeStraightDrive(0.3, 2.5);
	ball->SpinSequence(0.8, 1.0, 0.5, 1.0, 3.0);*/
}

void IAMRobot::AutonomousPeriodic() {
	if (autoSelected == autoNameCustom) {
		// Custom Auto goes here
	} else {
		// Default Auto goes here
	}
	//ato->AutonRun(true, false, true);
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
	ball->SpinShoot(0.0);
	ball->SpinFeed(0.0);
	ball->SpinMeter(0.0);
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
	SmartDashboard::PutNumber("shootSpeed", shooterTal->GetSpeed());
	SmartDashboard::PutNumber("shootVel", shooterTal->GetEncVel());
	SmartDashboard::PutNumber("shootVolt", shooterTal->GetBusVoltage());
	SmartDashboard::PutNumber("blendCurrent", pdp->GetCurrent(3));
}

void IAMRobot::TestPeriodic() {

}

void IAMRobot::DisabledInit(){
	gear->raiseClaw();
}

void IAMRobot::DisabledPeriodic(){
	gear->raiseClaw();
}

START_ROBOT_CLASS(IAMRobot)
