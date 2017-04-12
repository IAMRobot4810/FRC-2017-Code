//Source file for Weedwhacker.h
#include <Weedwhacker.h>

using namespace frc;

Weedwhacker::Weedwhacker(){ //Constructor
	//DriveSystem objects
	flTalon = new CANTalon(flTalID);
	rlTalon = new CANTalon(rlTalID);
	frTalon = new CANTalon(frTalID);
	rrTalon = new CANTalon(rrTalID);
	robotDrive = new RobotDrive(flTalon, rlTalon, frTalon, rrTalon);
	gyration = new AnalogGyro(gyroID);
	drive = new DriveSystem(robotDrive, gyration);

	//GearSystem objects
	gearClawNoid = new DoubleSolenoid(pcmID, clawNoidForwardID, clawNoidReverseID);
	gearRaiseNoid = new DoubleSolenoid(pcmID, raiseNoidForwardID, raiseNoidReverseID);
	gear = new GearSystem(gearRaiseNoid, gearClawNoid);
	gearSensor = new DigitalInput(gearSensorID);
	pegSensor = new DigitalInput(pegSensorID);

	//ClimbSystem objects
	climb1Roller = new CANTalon(roller1TalID);
	climb2Roller = new CANTalon(roller2TalID);
	climb = new ClimbSystem(climb1Roller, climb2Roller);

	//ShootSystem objects
	feedingTal = new CANTalon(feederTalID);
	meteringTal = new CANTalon(meterTalID);
	shooterTal = new CANTalon(shooterTalID);
	ball = new ShootSystem(feedingTal, meteringTal, shooterTal);

	//Teleop objects
	control1 = new XboxController(controller1ID);
	control2 = new XboxController(controller2ID);
	tlp = new Teleop(control1, control2, drive, gear, gearSensor, pegSensor, climb, ball);

	//Autonomous objects
	ato = new Auto(drive, gear, gearSensor, pegSensor, ball);

	//Sight cameras
	cammy = CameraServer::GetInstance();
	cammy2 = CameraServer::GetInstance();

	//Status indicator/decoration LEDs
	rLED = new Relay(rLEDID, Relay::kBothDirections);
	gLED = new Relay(gLEDID, Relay::kBothDirections);
	bLED = new Relay(bLEDID, Relay::kBothDirections);
}

Weedwhacker::~Weedwhacker(){ //Destructor
	delete flTalon;
	delete rlTalon;
	delete frTalon;
	delete rrTalon;
	delete robotDrive;
	delete drive;

	delete gearClawNoid;
	delete gearRaiseNoid;
	delete gear;
	delete gearSensor;
	delete pegSensor;

	delete climb1Roller;
	delete climb2Roller;
	delete climb;

	delete feedingTal;
	delete meteringTal;
	delete shooterTal;
	delete ball;

	delete control1;
	delete control2;
	delete tlp;

	delete gyration;
	delete ato;

	//delete pdp;

	delete rLED;
	delete gLED;
	delete bLED;
}

void Weedwhacker::RobotInit(){ //Initializes robot, runs at startup
	//Starting capture from sight cameras
	cammy->StartAutomaticCapture(camera1ID);
	cammy2->StartAutomaticCapture(camera2ID);

	//Initializing autonomous modes chooser
	autoChooser.AddDefault(autoNameDefault, autoNameDefault);
	autoChooser.AddObject(autoNameMGear, autoNameMGear);
	autoChooser.AddObject(autoNameLBall, autoNameLBall);
	autoChooser.AddObject(autoNameMBall, autoNameMBall);
	autoChooser.AddObject(autoNameHBall, autoNameHBall);
	autoChooser.AddObject(autoNameMBall, autoNameMBallGear);
	autoChooser.AddObject(autoNameMBall, autoNameMGearBall);
	SmartDashboard::PutData("Auto Modes", &autoChooser);

	//Initializing Teleop modes chooser
	teleChooser.AddDefault(teleNameDefault, teleNameDefault);
	teleChooser.AddObject(teleName1s, teleName1s);
	teleChooser.AddObject(teleName1ns, teleName1ns);
	SmartDashboard::PutData("Tele Modes", &teleChooser);
}

void Weedwhacker::AutonomousInit(){ //Runs once when autonomous is enabled
	//Getting input from autonomous modes chooser
	autoSelected = autoChooser.GetSelected();
	std::string autoSelected = SmartDashboard::GetString("Auto Selector", autoNameDefault);
	std::cout << "Auto selected: " << autoSelected << std::endl;

	ato->AutoInitialize();
}

void Weedwhacker::AutonomousPeriodic(){ //Autonomous loop
	//Running selected autonomous mode
	/*if(autoSelected == autoNameMGear){
		ato->GearAuto(Auto::kMiddleAuto);
	}
	else if(autoSelected == autoNameLBall){
		ato->BallAuto(Auto::kLowPow);
	}
	else if(autoSelected == autoNameMBall){
		ato->BallAuto(Auto::kMidPow);
	}
	else if(autoSelected == autoNameHBall){
		ato->BallAuto(Auto::kHighPow);
	}
	if(autoSelected == autoNameMBallGear){
		ato->BallGearAuto(Auto::kMiddleAuto);
	}
	if(autoSelected == autoNameMGearBall){
		ato->GearBallAuto(Auto::kMiddleAuto);
	}
	else{ // Default autonomous mode
		ato->BaselineAuto();
	}*/
	//ato->BallAuto(Auto::kMidPow);
	ato->BallGearAuto(Auto::kMiddleAuto, Auto::kMidPow);
}

void Weedwhacker::TeleopInit(){ //Runs once when teleop is enabled
	//Getting input from teleop modes chooser
	teleSelected = teleChooser.GetSelected();
	std::string teleSelected = SmartDashboard::GetString("Teleop Selector", teleNameDefault);
	std::cout << "Teleop selected: " << teleSelected << std::endl;

	//Stopping weedwhacker
	ball->SpinShoot(STOP);
	ball->SpinFeed(STOP);
	ball->SpinMeter(STOP);
}

void Weedwhacker::TeleopPeriodic(){ //Teleop loop
	//Running selected teleop mode
	if(teleSelected == teleName1s) {
		tlp->TeleopOneController(true);
	}
	else if(teleSelected == teleName1ns){
		tlp->TeleopOneController(false);
	}
	else {
		tlp->TeleopTwoController(true);
	}

	//Printing some values for testing
	SmartDashboard::PutNumber("shootSpeed", shooterTal->GetSpeed());
	SmartDashboard::PutNumber("shootVel", shooterTal->GetEncVel());
	SmartDashboard::PutNumber("shootVolt", shooterTal->GetBusVoltage());
}

void Weedwhacker::TestInit(){ //Runs once when test mode is enabled, for testing

}

void Weedwhacker::TestPeriodic(){ //Test mode loop, for testing

}

void Weedwhacker::DisabledInit(){ //Runs once when robot is disabled
	//Prepping GearSystem
	gear->raiseClaw();
	gear->closeClaw();
}

void Weedwhacker::DisabledPeriodic(){ //Disabled mode loop
	//Prepping GearSystem
	gear->raiseClaw();
	gear->closeClaw();
}

START_ROBOT_CLASS(Weedwhacker)
