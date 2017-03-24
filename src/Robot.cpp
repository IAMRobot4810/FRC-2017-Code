#include <iostream>
#include <memory>
#include <string>

#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <WPILib.h>
#include <CANTalon.h>
#include <PIDController.h>

using namespace frc;

class Robot: public frc::IterativeRobot {
public:

	CANTalon* flTalon;
	CANTalon* rlTalon;
	CANTalon* frTalon;
	CANTalon* rrTalon;
	RobotDrive* drive;

	CameraServer *cammy;
	SerialPort* rioduino;
	//PIDController* SpeedControl;

	SerialPort* duino;

	char *buff;
	int buffread1;
	int buffread2;
	int buffread3;
	int buffread4;
	int buffread5;
	int buffread6;
	double driveSpeed;

	char *buff2;
	int buff2read1;
	double kP =0.05;


	Robot(){
		flTalon = new CANTalon(2); //1
		rlTalon = new CANTalon(1); //2
		frTalon = new CANTalon(4); //3
		rrTalon = new CANTalon(5); //4
		drive = new RobotDrive(flTalon, rlTalon, frTalon, rrTalon);

		cammy = CameraServer::GetInstance();
		//SpeedControl = new PIDController(0,0,0,0,0);

		duino = new SerialPort(9600, SerialPort::kUSB1);
		buff = new char[6];
		buffread1 = 0;
		buffread2 = 0;
		buffread3 = 0;
		buffread4 = 0;
		buffread5 = 0;
		buffread6 = 0;
		driveSpeed = 0.25;
		//encoder = new PWM(0);
		rioduino = new SerialPort(9600, SerialPort::kMXP);
		buff2 = new char[1];
		buff2read1 = 0;
	}

	~Robot(){
		delete flTalon;
		delete rlTalon;
		delete frTalon;
		delete rrTalon;
		delete drive;
		delete duino;
		delete buff;
		//delete encoder;
		delete buff2;
	}

	void RobotInit() {
		chooser.AddDefault(autoNameDefault, autoNameDefault);
		chooser.AddObject(autoNameCustom, autoNameCustom);
		frc::SmartDashboard::PutData("Auto Modes", &chooser);
	}

	/*
	 * This autonomous (along with the chooser code above) shows how to select
	 * between different autonomous modes using the dashboard. The sendable
	 * chooser code works with the Java SmartDashboard. If you prefer the
	 * LabVIEW Dashboard, remove all of the chooser code and uncomment the
	 * GetString line to get the auto name from the text box below the Gyro.
	 *
	 * You can add additional auto modes by adding additional comparisons to the
	 * if-else structure below with additional strings. If using the
	 * SendableChooser make sure to add them to the chooser code above as well.
	 */
	void AutonomousInit() override {
		autoSelected = chooser.GetSelected();
		// std::string autoSelected = SmartDashboard::GetString("Auto Selector", autoNameDefault);
		std::cout << "Auto selected: " << autoSelected << std::endl;

		if (autoSelected == autoNameCustom) {
			// Custom Auto goes here
		} else {
			// Default Auto goes here
		}

		// cammy->StartAutomaticCapture("Pixy");
		drive->SetSafetyEnabled(false);
		/*drive->TankDrive(0.25, 0.25, false);
		Wait(1.0);
		drive->TankDrive(0.0, 0.0, false);*/
	}

	void AutonomousPeriodic() {
		if (autoSelected == autoNameCustom) {
			// Custom Auto goes here
		} else {
			// Default Auto goes here
		}

		duino->Read(buff, 3);
		buffread1 = (int) buff[0];
		buffread2 = (int) buff[1];
		buffread3 = (int) buff[2];
		buffread4 = (int) buff[3];
		double visDist = buffread1;
		double targetDistInch = 30;

		driveSpeed = 0.15;

		/*if(visDist == 0){
			driveSpeed = 0;
		}
		else{
			if((-0.25<=((visDist-targetDistInch)*kP)) && (((visDist-targetDistInch)*kP) <=0.25)){
				driveSpeed = (visDist-targetDistInch)*kP;
			}else if(((visDist-targetDistInch)*kP)>0.25){
				driveSpeed = 0.25;
			}else if(((visDist-targetDistInch)*kP)<-0.5){
				driveSpeed = -0.5;
			}
		}*/

		if(visDist > (targetDistInch+2)){
			drive->TankDrive(driveSpeed, driveSpeed, false);
		}
		else if((visDist >= (targetDistInch - 2) && visDist <= (targetDistInch + 2)) || visDist == 0){
			drive->TankDrive(0.0, 0.0, false);
		}
		else if (visDist < (targetDistInch-2)){
			drive->TankDrive(-driveSpeed, -driveSpeed, false);
		}
		else{
			drive->TankDrive(0.0, 0.0, false);
		}
		//drive->TankDrive(driveSpeed, driveSpeed, false);

		SmartDashboard::PutNumber("VisDist: ", visDist);
		SmartDashboard::PutNumber("VisDistFromHeight", buffread2);
		SmartDashboard::PutNumber("Height1: ", buffread3);
		SmartDashboard::PutNumber("Height2: ", buffread4);
		SmartDashboard::PutNumber("p", driveSpeed);
	}

	void TeleopInit() {

	}

	void TeleopPeriodic() {
		rioduino->Read(buff2, 1);
		int ready = buff2[0];
		SmartDashboard::PutNumber("ReadingAngle", 1.4117647058823529411764705882353*ready);

		//SmartDashboard::PutNumber("ReadingPosition",encoder->GetPosition());
		//SmartDashboard::PutNumber("ReadingSpeed",encoder->GetSpeed());
	}

	void TestPeriodic() {
		lw->Run();
	}


private:
	frc::LiveWindow* lw = LiveWindow::GetInstance();
	frc::SendableChooser<std::string> chooser;
	const std::string autoNameDefault = "Default";
	const std::string autoNameCustom = "My Auto";
	std::string autoSelected;
};

START_ROBOT_CLASS(Robot)
