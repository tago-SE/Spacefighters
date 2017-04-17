/*	Author(s):	Tiago Redaelli
*	Modified:	14-04-2017
*	Version:	0.01
*/

#pragma once

#include "libaries.h"

#define STATE_EXIT				0
#define STATE_GAME_RUNNING		1
#define STATE_MAIN_MENU			2
#define STATE_SETUP_SPACE_SIM	3
#define STATE_RUN_SPACE_SIM		4
//
#define STATE_COUNT				5

void executeNextState();
void setNextState(int state);
int getNextState();	