/*
 * Auto.h
 *
 *  Created on: Feb 21, 2017
 *      Author: 4810
 *
 *  Class for autonomous modes.
 */

//Header guards
#ifndef SRC_AUTO_AUTO_H_
#define SRC_AUTO_AUTO_H_

//Includes
#include <systems/DriveSystem/DriveSystem.h>
#include <systems/GearSystem/GearSystem.h>
#include <systems/ShootSystem/ShootSystem.h>
#include <util/ConstantVals.h>
#include <DigitalInput.h>
#include <SerialPort.h>
#include <AnalogGyro.h>

class Auto { //Autonomous class

public:
	Auto(DriveSystem* driveSystem, GearSystem* gearSystem, DigitalInput* gearDetectSensor,
			DigitalInput* pegDetectSensor1, ShootSystem* shootSystem); //Constructor
	~Auto(); //Destructor

	//Starting positions for autonomous
	enum AutoPosition{
		kMiddleAuto = 0,
		kLeftAuto = 1,
		kRightAuto = 2
	};

	/* Because the field is not rotationally symmetric, for shooting there
	 * is no positional parameter, but rather a shooting power parameter so
	 * it can be specified no matter the alliance.
	 */
	enum shooterPowMode{
		kLowPow = 0,
		kMidPow = 1,
		kHighPow = 2
	};

	void AutonRun(bool gear, bool ball, bool sensor); //A messy function that will be removed

	void AutoInitialize(); //Initializes autonomous variables
	void BaselineAuto(); //Autonomous to just reach the baseline and stop
	void BallAuto(shooterPowMode power); //Shoots balls and reaches baseline
	void GearAuto(AutoPosition position); //Places a gear on the peg
	void GearVisionAuto(AutoPosition position); //Vision-based GearAuto
	void BallGearAuto(AutoPosition position, Auto::shooterPowMode shootPower); //Shoots balls then places a gear
	void BallGearVisionAuto(AutoPosition position); //Vision-based BallGearAuto
	void GearBallAuto(AutoPosition position); //Places a gear, drives back, then shoots balls
	void GearBallVsionAuto(AutoPosition position); //Vision-based GearBallAuto

private:
	//Objects
	DriveSystem* drv;
	GearSystem* gr;
	DigitalInput* gDetect;
	DigitalInput* pDetect1;
	ShootSystem* sht;
	SerialPort* duino;
	PowerDistributionPanel* powerPanel;

	//Autonomous variables to stop from looping in periodic
	bool baselineReached = false;
	bool shotBalls = false;
	bool gearPlaced = false;

	int jamCycles;
	int unjamCycles;

	//Part of messy AutonRun
	bool ingear = false;
	bool ballDone = false;
	bool backedup = false;
	char *buff;
	int buffread1;
	int buffread2;
	int buffread3;

protected:

};

#endif /* SRC_AUTO_AUTO_H_ */
