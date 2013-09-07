/*
 * 
 * Created by DRAIDIA Taha Ibrahim.
 *
 *  */

#include<stdio.h>
#include<stdlib.h>
#include "../include/zombie-main.h"
#include "../include/zombie-graphics.h"

/** Cette fonction est appelee lors de l'affichage du score.
  Elle charge les scores des utilisateurs en fonction de leurs nombre de tantative 
  et de reussite plus le nombre de vies.
  \param game: pour pouvoir accedder au current_user  et tries et hits.
  \param vies: limitee le nombre de tantative a cinq => heads dans le fichier zombie-graphics. 
  \return un entier qui represente le score du joueur.
  */
int score(Game_parameters *game, int vies)
{
	float result;
	if(game->current_user->hits == 0)
	{
		result = 0;
	}
	else
	{
		switch(vies)
		{
			case 0: break;
			case 1: 
			result = (100 * ( (float)(game->current_user->tries + vies) / (float)(game->current_user->hits) ) );
			break;
			case 2: 
			result = (100 * ( (float)(game->current_user->tries + vies+50) / (float)(game->current_user->hits) ) );
			break;
			case 3: 
			result = (100 * ( (float)(game->current_user->tries + vies+150) / (float)(game->current_user->hits) ) );
			break;
			case 4: 
			result = (100 * ( (float)(game->current_user->tries + vies+200) / (float)(game->current_user->hits) ) );
			break;
			case 5: 
			result = (100 * ( (float)(game->current_user->tries + vies+250) / (float)(game->current_user->hits) ) );
			break;
			
			default: break;
		}
	}
	return result;
}

