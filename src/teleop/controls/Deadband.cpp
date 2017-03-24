/*
 * Deadband.h
 *
 *  Created on: Feb 11, 2017
 *      Author: 4810
 */

#include <teleop/controls/Deadband.h>

Deadband::Deadband(){

}

Deadband::~Deadband(){

}

double Deadband::DeadbandOut(double input, double deadBandLimit){
	double deadOut = 0;
	if((input > 0 && input > deadBandLimit) || (input < 0 && input < -deadBandLimit)){
		deadOut = input;
	}
	else{
		deadOut = 0;
	}
	return deadOut;
}
