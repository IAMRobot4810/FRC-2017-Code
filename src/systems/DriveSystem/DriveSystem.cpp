#include <systems/DriveSystem/DriveSystem.h>

DriveSystem::DriveSystem(RobotDrive* roboDrive, PWM* leftEncoder, PWM* rightEncoder, AnalogGyro* gyro){
	drov = roboDrive;
	gyr = gyro;
	flE = leftEncoder;
	frE = rightEncoder;
	drov->SetSafetyEnabled(true);
	drov->SetExpiration(0.1);
	/*gyr->InitGyro();
	gyr->Calibrate();*/
}

DriveSystem::~DriveSystem(){

}

void DriveSystem::TankControllerDrive(double leftSpeed, double rightSpeed){
	drov->SetSafetyEnabled(true);
	drov->SetExpiration(0.1);
	drov->TankDrive(leftSpeed, rightSpeed, false);
}

void DriveSystem::ArcadeControllerDrive(double moveSpeed, double turnSpeed){
	drov->SetSafetyEnabled(true);
	drov->SetExpiration(0.1);
	drov->ArcadeDrive(moveSpeed, turnSpeed, false);
}

void DriveSystem::TimeStraightDrive(double driveSpeed, double driveSeconds){
	drov->SetSafetyEnabled(false);
	for(int i = 0; i <= driveSeconds*100; i++){
		drov->ArcadeDrive(driveSpeed, 0.0, false);
		Wait(0.01);
	}
}

double DriveSystem::EncoderScale(int encoderReading, double wheelDiameterInches){
	double wheelIncrement = encoderReading/encoderRotationCounts;
	double wheelCircumference = M_PI*wheelDiameterInches;
	return wheelIncrement*wheelCircumference;
}

void DriveSystem::DistanceStraightDrive(double positiveDriveSpeed, double driveFeet){
	drov->SetSafetyEnabled(false);
	double travelDist = 0;
	double rotations = 0;
	if(driveFeet > 0){
		positiveDriveSpeed = abs(positiveDriveSpeed);
		int initRead = encoderRotationCounts - flE->GetRaw();
		while(travelDist < driveFeet){
			travelDist = EncoderScale(((rotations * encoderRotationCounts) + flE->GetRaw() + initRead), wheelDiameter);
			double dPower = positiveDriveSpeed * ((driveFeet-travelDist)/driveFeet);
			drov->ArcadeDrive(dPower, 0, false);
			if(flE->GetRaw()==0){
				rotations++;
			}
		}
	}
	else{
		positiveDriveSpeed = -abs(positiveDriveSpeed);
		int initRead = flE->GetRaw();
		while(travelDist > driveFeet){
			travelDist = -EncoderScale(((rotations * encoderRotationCounts) + (encoderRotationCounts - flE->GetRaw()) + initRead), wheelDiameter);
			double dPower = positiveDriveSpeed * ((driveFeet-travelDist)/driveFeet);
			drov->ArcadeDrive(dPower, 0, false);
			if(flE->GetRaw()==0){
				rotations++;
			}
		}
	}
	drov->ArcadeDrive(0.0, 0.0, false);
}

void DriveSystem::RotateDrive(double positiveDriveSpeed, double driveDegrees, bool reInitializeGyro){
	drov->SetSafetyEnabled(false);
	if(reInitializeGyro == true){
		gyr->Reset();
		if(driveDegrees > 0){
			positiveDriveSpeed = abs(positiveDriveSpeed);
			while(gyr->GetAngle() <= driveDegrees){
				double dPow = positiveDriveSpeed*((driveDegrees-(gyr->GetAngle()))/driveDegrees);
				drov->ArcadeDrive(0.0, dPow, false);
			}
		}
		else{
			positiveDriveSpeed = -abs(positiveDriveSpeed);
			while(gyr->GetAngle() >= driveDegrees){
				double dPow = positiveDriveSpeed*((driveDegrees-(gyr->GetAngle()))/driveDegrees);
				drov->ArcadeDrive(0.0, dPow, false);
			}
		}
	}
	else{
		double startAngle = gyr->GetAngle();
		double targetAngle = startAngle + driveDegrees;
		if(driveDegrees > 0){
			positiveDriveSpeed = abs(positiveDriveSpeed);
			while(gyr->GetAngle() <= targetAngle){
				double dPow = positiveDriveSpeed*((targetAngle-(gyr->GetAngle()))/driveDegrees);
				drov->ArcadeDrive(0.0, dPow, false);
			}
		}
		else{
			positiveDriveSpeed = -abs(positiveDriveSpeed);
			while(gyr->GetAngle() >= targetAngle){
				double dPow = positiveDriveSpeed*((targetAngle-(gyr->GetAngle()))/driveDegrees);
				drov->ArcadeDrive(0.0, dPow, false);
			}
		}
	}
}

