/*
//  angrybirds-algorithm.c
//  
//
//  Created by Benoit Favre and Valentin Emiya on 27/02/13.
//  Edited by DRAIDIA Taha Ibrahim
//  Copyright (c) 2013 CNRS LIF, Aix-Marseille Univ. All rights reserved.
*/

#include <math.h>
#include <stdlib.h>
#include "../include/zombie-main.h"
#include <time.h>
int i;



/** Teste si l'oiseau est en collision avec un element du jeu. Si c'est le
    cochon, change l'etat du jeu en STATE_HIT, si c'est un element du decor,
    change l'etat du jeu en STATE_MISS. Cette fonction doit aussi mettre a jour
    le score du joueur.
    \switch verifie le niveau du jeu 
*/
int test_collisions (Game_parameters *game) {
	/*collision avec le ghost */
	
	if(sqrt( pow( (game->ghost.center.x)-(game->zombie.center.x),2 )+pow( (game->ghost.center.y)-(game->zombie.center.y),2 ) )<=( (game->zombie.radius)+(game->ghost.radius) ) )
	{
		game->state=STATE_HIT;
		game->current_user->hits++;
		printf("[+] Hit the ghost \n");
		return 1;
	}
	
	
	
	/*collision avec la tombe*/
	if(sqrt( pow( (game->grave.center.x)-(game->zombie.center.x),2 )+pow( (game->grave.center.y)-(game->zombie.center.y),2 ) )<=( (game->zombie.radius)+(game->grave.radius) ) )
	{
		game->state=STATE_MISS;
		printf("[+] Hit the Grave\n");
		return 0;
	}
	
	
	/*collision avec la droite de la fenetre */
	if((game->zombie.center.x+game->zombie.radius)>=(800))
	{
		game->state=STATE_MISS;
        printf("[+] Hit the right window\n");
		return 0;
	}
	/*collision avec le sol*/
	if((game->zombie.center.y+game->zombie.radius)>=600)
	{
		game->state=STATE_MISS;
		printf("[+] Hit the ground\n");
		return 0;
	}
	/*collision avec la gauche de la fenetre */
	if((game->zombie.center.x+game->zombie.radius)<=(0))
	{
		game->state=STATE_MISS;
		printf("[+] Hit the left window\n");
		return 0;
	}
	/**
	 \verifie quel niveau du jeu pour pouvoir gener les collision de chaque caractere
	 sans ceci le teste de collision s'applique a tout les niveau.
	*/
	switch(game->lvl)
	{
		case 3:
						/*collision avec linux  1 */
				
				if(sqrt( pow( (game->linux.center.x)-(game->zombie.center.x),2 )+pow( (game->linux.center.y)-(game->zombie.center.y),2 ) )<=( (game->zombie.radius)+(game->linux.radius) ) )
				{
					game->state=STATE_MISS;
					printf("[+] Hit LINUX 1 \n");
					return 1;
				}
		break;
		case 4:
				/*collision avec linux 1 */
				
				if(sqrt( pow( (game->linux.center.x)-(game->zombie.center.x),2 )+pow( (game->linux.center.y)-(game->zombie.center.y),2 ) )<=( (game->zombie.radius)+(game->linux.radius) ) )
				{
					game->state=STATE_MISS;
					printf("[+] Hit LINUX 1  \n");
					return 1;
				}
		break;
		case 5:
				/*collision avec linux 1 */
				
				if(sqrt( pow( (game->linux.center.x)-(game->zombie.center.x),2 )+pow( (game->linux.center.y)-(game->zombie.center.y),2 ) )<=( (game->zombie.radius)+(game->linux.radius) ) )
				{
					game->state=STATE_MISS;
					printf("[+] Hit LINUX 1 \n");
					return 1;
				}
		break;
		case 6:
					/*collision avec linux 1 */
					
					if(sqrt( pow( (game->linux.center.x)-(game->zombie.center.x),2 )+pow( (game->linux.center.y)-(game->zombie.center.y),2 ) )<=( (game->zombie.radius)+(game->linux.radius) ) )
					{
						game->state=STATE_MISS;
						printf("[+] Hit LINUX 1  \n");
						return 1;
					}
		break;
		case 7:
					/*collision avec linux 1 */
					
					if(sqrt( pow( (game->linux.center.x)-(game->zombie.center.x),2 )+pow( (game->linux.center.y)-(game->zombie.center.y),2 ) )<=( (game->zombie.radius)+(game->linux.radius) ) )
					{
						game->state=STATE_MISS;
						printf("[+] Hit LINUX 1\n");
						return 1;
					}
					/*collision avec linux 2 */
					
					if(sqrt( pow( (game->linux2.center.x)-(game->zombie.center.x),2 )+pow( (game->linux2.center.y)-(game->zombie.center.y),2 ) )<=( (game->zombie.radius)+(game->linux2.radius) ) )
					{
						game->state=STATE_MISS;
						printf("[+] Hit LINUX 2\n");
						return 1;
					}
		break;
		case 8:
					/*collision avec linux 1 */
					
					if(sqrt( pow( (game->linux.center.x)-(game->zombie.center.x),2 )+pow( (game->linux.center.y)-(game->zombie.center.y),2 ) )<=( (game->zombie.radius)+(game->linux.radius) ) )
					{
						game->state=STATE_MISS;
						printf("[+] Hit LINUX 1  \n");
						return 1;
					}
					
		break;
		case 9:
					/*collision avec linux 1 */
					
					if(sqrt( pow( (game->linux.center.x)-(game->zombie.center.x),2 )+pow( (game->linux.center.y)-(game->zombie.center.y),2 ) )<=( (game->zombie.radius)+(game->linux.radius) ) )
					{
						game->state=STATE_MISS;
						printf("[+] Hit LINUX 1 \n");
						return 1;
					}
					/*collision avec linux 2 */
					
					if(sqrt( pow( (game->linux2.center.x)-(game->zombie.center.x),2 )+pow( (game->linux2.center.y)-(game->zombie.center.y),2 ) )<=( (game->zombie.radius)+(game->linux2.radius) ) )
					{
						game->state=STATE_MISS;
						printf("[+] Hit LINUX 2 \n");
						return 1;
					}
		break;
		default: break;
	}
	return true;		
}

/** Effectue un pas de la simulation: met a jour la position de l'oiseau en
    fonction de sa vitesse; met a jour la vitesse de l'oiseau en fonction de la
    gravite. Si l'oiseau entre en collision, arrete la simulation.
    \return false is simulation is stopped, true if it continues
*/
int simulation_step (Game_parameters* game) {

    
    
	game->zombie.center.x += game->velocity.x;
	game->velocity.x += game->gravity.x;
	game->zombie.center.y += game->velocity.y;
	game->velocity.y += game->gravity.y;
	
	
	return test_collisions(game);
		
}

/** 
 \c'est la fonction qui rends les personnages 
*/

void moveGraveGhost (Game_parameters *game)
{
	switch(game->lvl)
	{
		case 1:
				
		break;
		case 2:
		
		/* speed 1.5 */
		
		if(game->ghost.center.x <= 700)
			{
				game->ghost.center.x -= game->speed.x;
				if(game->ghost.center.x <= 450 )
				{
					game->speed.x = -1.5;
					game->ghost.center.x -= game->speed.x;
				}
				
			}else
			{
				game->speed.x = 1.5;
				game->ghost.center.x -= game->speed.x;
			}	
		
				
		break;
		case 3:
		
					
					
						/* speed linux 1 lvl3 1.5 */
		
					if(game->linux.center.x <= 695)
						{
							game->linux.center.x -= game->speed.x;
							if(game->linux.center.x <= 450 )
							{
								game->speed.x = -1.5;
								game->linux.center.x -= game->speed.x;
							}
							
						}else
						{
							game->speed.x = 1.5;
							game->linux.center.x -= game->speed.x;
						}	
			
		break;
		case 4:
				/* linux  lvl 4*/
					if(game->linux.center.y <= 521)
						{
							
							game->linux.center.y -= game->sdlinux.y;
							if(game->linux.center.y <= 290 )
							{
								game->sdlinux.y = -2;
								game->linux.center.y -= game->sdlinux.y;
							}
							
						}else
						{
							game->sdlinux.y = 2;
							game->linux.center.y -= game->sdlinux.y;
						}	
				
		break;
		case 5:
					
						/* speed linux 1 lvl5  */
		
					if(game->linux.center.x <= 600)
						{
							
							game->linux.center.x -= game->sdlinux.x;
							if(game->linux.center.x <= 480 )
							{
								game->sdlinux.x = -2;
								game->linux.center.x -= game->sdlinux.x;
							}
							
						}else
						{
							game->sdlinux.x = 2;
							game->linux.center.x -= game->sdlinux.x;
						}	
						
						/* speed ghost  lvl5 */
		
					if(game->ghost.center.x <= 700)
						{
							game->ghost.center.x -= game->speed.x;
							if(game->ghost.center.x <= 450 )
							{
								game->speed.x = -1.5;
								game->ghost.center.x -= game->speed.x;
							}
							
						}else
						{
							game->speed.x = 1.5;
							game->ghost.center.x -= game->speed.x;
						}	
					
		break;
		case 6:
				/* lvl 6 */
				
				if(game->ghost.center.x <= 700)
					{
						game->ghost.center.x -= 2;
						if(game->ghost.center.x <= 550 )
						{
							game->speed.y = 2;
							game->ghost.center.y -= game->speed.y;
							if(game->ghost.center.y <= 310)
							{
								game->speed.y = -2;
								game->ghost.center.x += game->speed.y;
							}
							if(game->ghost.center.y <100)
							{
								game->ghost.center.y= 501;
								game->ghost.center.x = 700;
							}
						}
					}	
					
					/* speed linux 1 lvl3 1.5 */
		
					if(game->linux.center.x <= 400)
						{
							
							game->linux.center.x -= game->sdlinux.x;
							if(game->linux.center.x <= 10 )
							{
								game->sdlinux.x = -2;
								game->linux.center.x -= game->sdlinux.x;
							}
							
						}else
						{
							game->sdlinux.x = 2;
							game->linux.center.x -= game->sdlinux.x;
						}	
		break;
		case 7:
					/* speed linux 2 lvl 7  */
		
					if(game->linux2.center.y <= 450)
						{
							
							game->linux2.center.y -= game->sdlinux.y;
							if(game->linux2.center.y <= 90 )
							{
								game->sdlinux.y = -2;
								game->linux2.center.y -= game->sdlinux.y;
							}
							
						}else
						{
							game->sdlinux.y = 2;
							game->linux2.center.y -= game->sdlinux.y;
						}	
					/* speed linux 1 lvl 7  */
		
					if(game->linux.center.x <= 600)
						{
							
							game->linux.center.x -= game->sdlinux.x;
							if(game->linux.center.x <= 480 )
							{
								game->sdlinux.x = -2;
								game->linux.center.x -= game->sdlinux.x;
							}
							
						}else
						{
							game->sdlinux.x = 2;
							game->linux.center.x -= game->sdlinux.x;
						}	
						
						/* speed ghost  lvl 7 */
		
					if(game->ghost.center.x <= 700)
						{
							game->ghost.center.x -= game->speed.x;
							if(game->ghost.center.x <= 450 )
							{
								game->speed.x = -1.5;
								game->ghost.center.x -= game->speed.x;
							}
							
						}else
						{
							game->speed.x = 1.5;
							game->ghost.center.x -= game->speed.x;
						}	
		break;
		case 8:
					
					
					/* speed linux 1 lvl 8 */
		
					if(game->linux.center.y <= 450)
						{
							
							game->linux.center.y -= game->sdlinux.y;
							if(game->linux.center.y <= 90 )
							{
								game->sdlinux.y = -2;
								game->linux.center.y -= game->sdlinux.y;
							}
							
						}else
						{
							game->sdlinux.y = 2;
							game->linux.center.y -= game->sdlinux.y;
						}	
						
						if(game->linux.center.x <= 600)
						{
							
							game->linux.center.x -= game->sdlinux.x;
							if(game->linux.center.x <= 480 )
							{
								game->sdlinux.x = -2;
								game->linux.center.x -= game->sdlinux.x;
							}
							
						}else
						{
							game->sdlinux.x = 2;
							game->linux.center.x -= game->sdlinux.x;
						}	
						
						/* speed ghost  lvl 8 */
		
					if(game->ghost.center.x <= 700)
						{
							game->ghost.center.x -= game->speed.x;
							if(game->ghost.center.x <= 450 )
							{
								game->speed.x = -1.5;
								game->ghost.center.x -= game->speed.x;
							}
							
						}else
						{
							game->speed.x = 1.5;
							game->ghost.center.x -= game->speed.x;
						}	
		break;
		
		default: break;
	}
		
}

/** Cette fonction initialise l'aire de jeu avant de lancer la simulation.
    Elle place l'oiseau sur le lance-pierre et initialise sa vitesse a zero.
    Elle place le cochon aleatoirement sur le sol. Elle place l'obstacle
    aleatoirement entre le cochon et le lance-pierre.
    \switch la position du ghost varie de chaque niveau  
*/
void init_simulation (Game_parameters *game) {
    
    /* A COMPLETER */
    
    srand (time(NULL));
    
    /* position du Zombie*/
    
    									
    
	
	game->zombie.center.x = 120;
	game->zombie.center.y = 450;
	game->zombie.radius = 20;
	
	
	/* position du grave*/
	game->grave.center.x = 410;
	game->grave.center.y = 501;
	game->grave.radius = 30;
	
    switch(game->lvl)
    {
		case 1:
		
						/* position ghost lvl 1 */
					
				game->ghost.center.x = rand()%200 + 500;
				game->ghost.center.y = 501;
				game->ghost.radius = 20;
		
		break;
		case 2:
				
							/* position ghost lvl 2*/  
				game->ghost.center.x = 700;
				game->ghost.center.y = 485;
				game->ghost.radius = 20;
						
		
		break;
		case 3:
				
				/* position ghost lvl 3*/  
				game->ghost.center.x = rand()%200 + 500;
				game->ghost.center.y = 521;
				game->ghost.radius = 25;
				
				/* position linux */
				game->linux.center.x = 700;
				game->linux.center.y = 450;
				game->linux.radius = 20;
						
		break;
		case 4:
				/* position ghost lvl 4*/  
				game->ghost.center.x = 700;
				game->ghost.center.y = 485;
				game->ghost.radius = 20;
				
				/* position linux lvl 4*/
				game->linux.center.x = 550;
				game->linux.center.y = 521;
				game->linux.radius = 20;
				
		break;
		case 5:
				/* position ghost lvl 5*/  
				game->ghost.center.x = 700;
				game->ghost.center.y = 521;
				game->ghost.radius = 20;
				
				/* position linux lvl 5*/
				game->linux.center.x = 600;
				game->linux.center.y = 450;
				game->linux.radius = 20;
				
				
				
		break;
		case 6:
				/* position ghost lvl 6*/  
				game->ghost.center.x = 700;
				game->ghost.center.y = 485;
				game->ghost.radius = 40;
				/* position linux lvl 5*/
				game->linux.center.x = 400;
				game->linux.center.y = 350;
				game->linux.radius = 20;
				
		break;
		case 7:
				/* position ghost lvl 7*/  
				game->ghost.center.x = 700;
				game->ghost.center.y = 485;
				game->ghost.radius = 20;
				
				/* position linux1 lvl 7*/
				game->linux.center.x = 400;
				game->linux.center.y = 350;
				game->linux.radius = 20;
				
				/* position linux2 lvl 7*/
				game->linux2.center.x = 430;
				game->linux2.center.y = 450;
				game->linux2.radius = 20;
		break;
		case 8:
				/* position ghost lvl 8*/  
				game->ghost.center.x = 700;
				game->ghost.center.y = 485;
				game->ghost.radius = 20;
				
				/* position linux1 lvl 7*/
				game->linux.center.x = 400;
				game->linux.center.y = 350;
				game->linux.radius = 20;
				
				
				
		break;
		
		default: 
			printf("There's no configuration for this level\n");
		break;
	}
    
	
	
	
    
    
    

}

