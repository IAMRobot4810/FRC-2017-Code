/*
 * ClimbSystem.cpp
 *
 *  Created on: Feb 17, 2017
 *      Author: 4810
 */

#include <systems/ClimbSystem/ClimbSystem.h>

ClimbSystem::ClimbSystem(CANTalon* climb1Talon, CANTalon* climb2Talon){
	clmb1Tl = climb1Talon;
	clmb2Tl = climb2Talon;
}

ClimbSystem::~ClimbSystem(){

}

void ClimbSystem::Climb(double speed){
	clmb1Tl->Set(-speed);
	clmb2Tl->Set(speed);

}
