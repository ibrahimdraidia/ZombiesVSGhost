/*
//  angrybirds-algorithm.h
//  
//
//  Created by Benoit Favre and Valentin Emiya on 27/02/13.
* 	Edited by DRAIDIA Taha Ibrahim
//  Copyright (c) 2013 CNRS LIF, Aix-Marseille Univ. All rights reserved.
*/

#ifndef _zombie_algorithm_h
#define _zombie_algorithm_h

#include "ez-draw.h"

void init_simulation (Game_parameters *game);
int simulation_step (Game_parameters *game);
void stop_simulation (Game_parameters *game);
void moveGraveGhost (Game_parameters *game);
#endif
