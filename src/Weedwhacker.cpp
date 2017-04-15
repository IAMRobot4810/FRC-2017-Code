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
	gyration = new ADXRS450_Gyro(SPI::kOnboardCS0);
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
	gearAuto = true;
	shootAutoPower = 2;
	gearPosEnum = Auto::kMiddleAuto;
	shootPowerEnum = Auto::kMidPow;
	gearFirst = false;

	//Sight cameras
	cammy = CameraServer::GetInstance();
	cammy2 = CameraServer::GetInstance();
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
}

void Weedwhacker::RobotInit(){ //Initializes robot, runs at startup
	//Starting capture from sight cameras
	cammy->StartAutomaticCapture(camera1ID);
	cammy2->StartAutomaticCapture(camera2ID);

	SmartDashboard::PutBoolean("Gear in Auto?", true);
	SmartDashboard::PutNumber("Auto Shooting Power", 2);
	SmartDashboard::PutBoolean("Gear First in Auto?", false);
}

void Weedwhacker::AutonomousInit(){ //Runs once when autonomous is enabled
	ato->AutoInitialize();
	gearAuto = SmartDashboard::GetBoolean("Gear in Auto?", true);
	if(!gearAuto){
		gearPosEnum = Auto::kLeftAuto;
	}
	else{
		gearPosEnum = Auto::kMiddleAuto;
	}

	shootAutoPower = SmartDashboard::GetNumber("Auto Shooting Power", 2);
	if(shootAutoPower == 0){
		shootPowerEnum = Auto::kNoPow;
	}
	else if(shootAutoPower == 1){
		shootPowerEnum = Auto::kLowPow;
	}
	else if(shootAutoPower == 3){
		shootPowerEnum = Auto::kHighPow;
	}
	else{
		shootPowerEnum = Auto::kMidPow;
	}

	gearFirst = SmartDashboard::GetBoolean("Gear First in Auto?", false);
}

void Weedwhacker::AutonomousPeriodic(){ //Autonomous loop
	if(gearFirst){
		ato->GearBallAuto(gearPosEnum, shootPowerEnum);
	}
	else{
		ato->BallGearAuto(gearPosEnum, shootPowerEnum);
	}
}

void Weedwhacker::TeleopInit(){ //Runs once when teleop is enabled
	//Stopping weedwhacker
	ball->SpinShoot(STOP);
	ball->SpinFeed(STOP);
	ball->SpinMeter(STOP);
}

void Weedwhacker::TeleopPeriodic(){ //Teleop loop
	tlp->TeleopTwoController(true);
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
