/*
 * Deadband.cpp
 *
 *  Created on: Feb 11, 2017
 *      Author: Anish
 */

#include "Deadband.h"

Deadband::Deadband(double LowBound, double HighBound){
	this->LowBound = LowBound;
	this->HighBound = HighBound;
}
double Deadband::ReturnBoundedValue(double value){
	if(value<0 && value<=LowBound || value>0 && value>=HighBound){
		return value;
	}else{
		return 0;
	}
}