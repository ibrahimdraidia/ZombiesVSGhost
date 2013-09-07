/*
//  angryzombies-graphics.c
//  
//
//  Created by Benoit Favre and Valentin Emiya on 27/02/13.
//	Edited by DRAIDIA Taha Ibrahim
//  Copyright (c) 2013 CNRS LIF, Aix-Marseille Univ. All rights reserved.
*/

#include <stdio.h>
#include <unistd.h>
#include "../include/zombie-main.h"
#include "../include/zombie-score.h"
#include "../include/zombie-algorithm.h"
User *U;
int heads = 5;
int i;
int player_position;


/** Dessine le contenu de la fenetre lors du jeu en fonction de l'etat du jeu
 * et de la position des differents elements.
*/

void redraw (Window win) {

	
    Game_parameters *game;
    game = ez_get_data (win);
    ez_set_nfont (2);
	switch(game->state)
	{
		case STATE_SPLASH:
			ez_draw_image(win,game->load,0,0);
		break;
		
		case STATE_ENTERING_NAME:
				/* color */
			ez_set_color (ez_red);
			/*  background lenu */ 
			ez_draw_image(win,game->menu,0,0);
			/* line */
			ez_draw_line (win,  200,  290, 300,  290);
			
			ez_draw_text(win,EZ_ML,100,290,"Nickname : %s\n", game->typed_text);
		break;
		case STATE_MENU:
		    /* init tantatives */
		    heads = 5;
		    /* init lvl */
		    game->lvl = 1;
		  
			/*  background menu */ 
			ez_draw_image(win,game->menu,0,0);
		
			ez_set_color (ez_red);
			
			/*  Buttons */ 
			ez_draw_image(win,game->newGame,150,50);
			ez_draw_image(win,game->nickname,150,130);
			ez_draw_image(win,game->scores,150,210);
			ez_draw_image(win,game->help,150,290);
			ez_draw_image(win,game->about,150,370);
			ez_draw_image(win,game->exit,150,450);
			
            
		break;
		
		case STATE_AIMING:
		
			
			/* image du background */
			ez_draw_image(win,game->bg,0,0);
			 /** 
				verifie le nombre de vies qui reste au joueur si 0 renvoi vers LOSE sinon terminer le jeu 
				avec le nombre de vie qui reste
			 */ 
			if(heads == 0)
			{
					game->state=STATE_LOSE;
					ez_send_expose(win);
			}else
			{
			
				switch(game->lvl)
				{
					case 1:
						
						/* ghost */
						ez_draw_image(win,game->ghostImage,game->ghost.center.x,game->ghost.center.y);
						
				    break;
				    case 2:
					 
						ez_timer_add(win, 10);
						/* ghost */
						ez_draw_image(win,game->ghostImage,game->ghost.center.x,game->ghost.center.y);
					 
						
				    break;
				    case 3:
						 
						ez_timer_add(win, 10);
						 /* ghost */
						ez_draw_image(win,game->ghostImage,game->ghost.center.x,game->ghost.center.y);
						 /* linux */
						ez_draw_image(win,game->linuxImage,game->linux.center.x,game->linux.center.y);
						
				    break;
					case 4:
						
						ez_timer_add(win, 10);
						/* ghost */
						ez_draw_image(win,game->ghostImage,game->ghost.center.x,game->ghost.center.y);
						/* linux */
						ez_draw_image(win,game->linuxImage,game->linux.center.x,game->linux.center.y);
					break;
					case 5:
						 
						ez_timer_add(win, 10);
						/* ghost */
						ez_draw_image(win,game->ghostImage,game->ghost.center.x,game->ghost.center.y);
						/* linux 1 */
						ez_draw_image(win,game->linuxImage,game->linux.center.x,game->linux.center.y);
						
						
					break;
					case 6:
					
						ez_timer_add(win, 10);
						/* ghost */
						ez_draw_image(win,game->ghostImage,game->ghost.center.x,game->ghost.center.y);
						/*  linux 1*/ 
						ez_draw_image(win,game->linuxImage,game->linux.center.x,game->linux.center.y);
					break;
					case 7:
						
						ez_timer_add(win, 10);
					
						/* ghost */
						ez_draw_image(win,game->ghostImage,game->ghost.center.x,game->ghost.center.y);
						/*  linux 1 */ 
						ez_draw_image(win,game->linuxImage,game->linux.center.x,game->linux.center.y);
						/*  linux 2 */ 
						ez_draw_image(win,game->linuxImage,game->linux2.center.x,game->linux2.center.y);
						
					break;
					case 8:
						
						ez_timer_add(win, 10);
						
						
						/* final boss 'death' */
						ez_draw_image(win,game->bossImage,game->ghost.center.x,game->ghost.center.y);
						/*  ghost */ 
						ez_draw_image(win,game->ghostImage,game->linux.center.x,game->linux.center.y);
						
					break;
					
					default: break;
				}
			
		 	/* couleur noir & tableau de status*/
			ez_set_color (ez_black);
			ez_fill_rectangle (win, 300, 10, 790, 65);

			/* player profil */	
			ez_set_nfont (2);	
			ez_set_color (ez_white);
			ez_draw_text(win,EZ_ML,310,50,"Player : %s   level: %d  tries: %d  hits: %d \n", game->current_user->name, game->lvl,game->current_user->tries, game->current_user->hits);
		
			ez_draw_image(win,game->tank,game->zombie.center.x,game->zombie.center.y);
			
			/*  grave 'obstacle ' */ 
			ez_draw_image(win,game->graveImage,game->grave.center.x,game->grave.center.y);
			
			/*ez_draw_image(win,game->sniper,game->mouse.x - 15,game->mouse.y );*/
			switch(heads)
			{
				
				case 1:
							
					
					ez_draw_image(win,game->zombieImage,15,10);
					
					
				break;
				
				case 2:
							
					ez_draw_image(win,game->zombieImage,15,10);
					ez_draw_image(win,game->zombieImage,65,10);
					
				break;
				case 3:
					
					ez_draw_image(win,game->zombieImage,15,10);
					ez_draw_image(win,game->zombieImage,65,10);
					ez_draw_image(win,game->zombieImage,115,10);
					break;
				case 4:
						
					
					ez_draw_image(win,game->zombieImage,15,10);
					ez_draw_image(win,game->zombieImage,65,10);
					ez_draw_image(win,game->zombieImage,115,10);
					ez_draw_image(win,game->zombieImage,165,10);
					break;
				case 5:
						
					
					ez_draw_image(win,game->zombieImage,15,10);
					ez_draw_image(win,game->zombieImage,65,10);
					ez_draw_image(win,game->zombieImage,115,10);
					ez_draw_image(win,game->zombieImage,165,10);
					ez_draw_image(win,game->zombieImage,215,10);
					
				break;
				default:
					printf("[+] 3 heads only\n");
				break;
				
				
			}
		}	
		break;
		
		case STATE_FLYING:
		   
			
			/*  background */ 
			ez_draw_image(win,game->bg,0,0);
			if(heads == 0)
			{
				game->state=STATE_LOSE;
				ez_send_expose(win);
			}else
			{
			/* switch level */
				switch(game->lvl)
				{
					case 1:
						/* ghost */
						ez_draw_image(win,game->ghostImage,game->ghost.center.x,game->ghost.center.y);
						
				    break;
				    case 2:
						/*  timer */
						ez_timer_add(win, 10);
						/* ghost */
						ez_draw_image(win,game->ghostImage,game->ghost.center.x,game->ghost.center.y);
						
				    break;
				    case 3:
						/*  timer */
						ez_timer_add(win, 10);
						/* ghost */
						ez_draw_image(win,game->ghostImage,game->ghost.center.x,game->ghost.center.y);
						/*  grave*/ 
						ez_draw_image(win,game->graveImage,game->grave.center.x,game->grave.center.y);
						/*  linux */ 
						ez_draw_image(win,game->linuxImage,game->linux.center.x,game->linux.center.y);
				    break;
					case 4:
						/*  timer */
						ez_timer_add(win, 10);
						ez_draw_image(win,game->ghostImage,game->ghost.center.x,game->ghost.center.y);
						/* linux */
						ez_draw_image(win,game->linuxImage,game->linux.center.x,game->linux.center.y);
					break;
					case 5:
						/*  timer */
						ez_timer_add(win, 10);
						ez_draw_image(win,game->ghostImage,game->ghost.center.x,game->ghost.center.y);
						/* linux */
						ez_draw_image(win,game->linuxImage,game->linux.center.x,game->linux.center.y);
						
					break;
					case 6:
						/*  timer */
						ez_timer_add(win, 10);
						ez_draw_image(win,game->ghostImage,game->ghost.center.x,game->ghost.center.y);
						/*  linux */ 
						ez_draw_image(win,game->linuxImage,game->linux.center.x,game->linux.center.y);
					break;
					case 7:
						/*  timer */
						ez_timer_add(win, 10);
						/* ghost */
						ez_draw_image(win,game->ghostImage,game->ghost.center.x,game->ghost.center.y);
						/*  linux 1 */ 
						ez_draw_image(win,game->linuxImage,game->linux.center.x,game->linux.center.y);
						/*  linux 2 */ 
						ez_draw_image(win,game->linuxImage,game->linux2.center.x,game->linux2.center.y);
						
					break;
					case 8:
						/*  timer */
						ez_timer_add(win, 10);
						/* final boss 'death' */
						ez_draw_image(win,game->bossImage,game->ghost.center.x,game->ghost.center.y);
						/*  ghost */ 
						ez_draw_image(win,game->ghostImage,game->linux.center.x,game->linux.center.y);
						
					break;
					
					default: break;
				}
				
				/* tableau */	
			ez_set_color (ez_black);
			ez_fill_rectangle (win, 300, 10, 790, 65);
			/* player profil */	
			ez_set_nfont (2);	
			ez_set_color (ez_white);
			ez_draw_text(win,EZ_ML,310,50,"Player : %s   level: %d  tries: %d  hits: %d \n", game->current_user->name, game->lvl,game->current_user->tries, game->current_user->hits);
			/* zombie */
			ez_draw_image(win,game->zombieImage,game->zombie.center.x,game->zombie.center.y);
			/* tank */
			ez_draw_image(win,game->tank,120,450);
			/*  grave */ 
		    ez_draw_image(win,game->graveImage,game->grave.center.x,game->grave.center.y);
			
			switch(heads)
			{
				
				case 1:
							
					/*  tries  */
					ez_draw_image(win,game->zombieImage,15,10);
					
					
				break;
				
				case 2:
							
					/*  tries  */
					ez_draw_image(win,game->zombieImage,15,10);
					ez_draw_image(win,game->zombieImage,65,10);
				
				break;
				case 3:
						
					/*  tries  */
					ez_draw_image(win,game->zombieImage,15,10);
					ez_draw_image(win,game->zombieImage,65,10);
					ez_draw_image(win,game->zombieImage,115,10);
					
				break;
				case 4:
						
					/*  tries  */
					ez_draw_image(win,game->zombieImage,15,10);
					ez_draw_image(win,game->zombieImage,65,10);
					ez_draw_image(win,game->zombieImage,115,10);
					ez_draw_image(win,game->zombieImage,165,10);
					break;
				case 5:
						
					/*  tries  */
					ez_draw_image(win,game->zombieImage,15,10);
					ez_draw_image(win,game->zombieImage,65,10);
					ez_draw_image(win,game->zombieImage,115,10);
					ez_draw_image(win,game->zombieImage,165,10);
					ez_draw_image(win,game->zombieImage,215,10);
					
				break;
				default:
					printf("[+] 3 heads only\n");
				break;
				
				
			}
		}	
			
		break;
		
		case STATE_HIT:
			/*  background */ 
			ez_draw_image(win,game->menu,0,0);
			ez_draw_image(win,game->next,150,210);
			ez_draw_image(win,game->replay,150,290);
			ez_draw_image(win,game->btmenu,150,370);
			/* border */
			ez_set_color (ez_red);
			ez_draw_rectangle (win, 100, 90, 300, 180);
			ez_set_color (ez_white);
			ez_draw_text (win, EZ_TL, 110, 100,"Congratulation !!!\nYour score: %d\nyou have %d head(s)", score(game, heads), heads );
			
		break;
		case STATE_MISS:
			/* nombre de vies - 1 a chaque miss */
			heads--;
			game->state=STATE_AIMING;
            init_simulation(game);
            ez_send_expose(win);
			
		break;
		case STATE_TOPSCORES:
			/*  background menu */ 
			ez_draw_image(win,game->menu,0,0);
			/*  reset button */ 
			ez_draw_image(win,game->reset,50,450);
			/*  Menu Button*/ 
			ez_draw_image(win,game->btmenu,165,450);
			ez_set_color (ez_red);
            U=game->users;
            i=0;
            player_position=1;
            while((U != NULL) && (player_position < 11)){
                ez_draw_text(win, EZ_TL, 50, 200+i, "%d : %s %d %d", player_position, U->name, U->hits, U->tries);
                i+=20;
                U=U->next;
                player_position++;
			}
		break;
		case STATE_ABOUT:
			/*  background lenu */ 
			ez_draw_image(win,game->menu,0,0);
			/* border */
			ez_set_color (ez_red);
			ez_draw_rectangle (win, 20, 10, 410, 410);
			printf("[+] About \n");
			ez_set_color (ez_white);
			ez_draw_text (win, EZ_TL, 40, 100,
					"          About :   \n\n" 
                    "Tilte: ZOMBIE vs GHOST\n"
                    "Author: DRAIDIA Taha Ibrahim\n"
                    "Email: ibrahim@draidia.us\n"
                    "Website: www.draidia.us\n");
            /*  Web button */ 
			ez_draw_image(win,game->web,150,450);
			/*  Menu Button*/ 
			ez_draw_image(win,game->btmenu,265,450);
            
		break;
		case STATE_HELP:
			/*  background menu */ 
			ez_draw_image(win,game->menu,0,0);
			/* border */
			ez_set_color (ez_red);
			ez_draw_rectangle (win, 30, 10, 400, 410);
			printf("[+] Help \n");
			ez_set_color (ez_white);
			ez_draw_text (win, EZ_TL, 50, 20,
					"           Help :   \n" 
                    "         Shortcuts: \n"
                    "'m': back to menu from everywhere\n"
                    "'q': exit\n"
                    "Menu:\n"
                    "'Enter': new game\n"
                    "'n': change nickname\n"
                    "'s': Topscore\n"
                    "'h': help\n"
                    "'a': about\n"
                    "'q': exit\n"
                    "Help & about:\n"
                    "'w': open the webpage\n"
                    "Hit:\n"
                    "'n' next level\n"
                    "'enter' play again\n");
            /*  Web button */ 
			ez_draw_image(win,game->web,150,450);
			/*  Menu Button*/ 
			ez_draw_image(win,game->btmenu,265,450);
            
		break;
		/* lose */
		case STATE_LOSE:
		    /* ini tries */
			heads = 5;
			/*  background  */ 
			ez_draw_image(win,game->gameOver,0,0);
			/* game over */
			ez_set_color (ez_white);
			ez_draw_text (win, EZ_TL, 345, 300,"player: %s\nhits: %d\ntries: %d\nyour score: %d\n",game->current_user->name, game->current_user->hits,game->current_user->tries,score(game, heads));
			/*WriteData(game,".score",heads);*/
			/*  play again button */ 
			ez_draw_image(win,game->replay,150,470);
			/*  Menu Button*/ 
			ez_draw_image(win,game->btmenu,535,470);
			
		break;
		/* fin du  jeu */
		case STATE_FINISH:
			/*  background lenu */ 
			ez_draw_image(win,game->menu,0,0);
			/* border */
			ez_set_color (ez_red);
			ez_draw_rectangle (win, 20, 10, 410, 410);
			printf("[+] Finished the game \n");
			ez_set_color (ez_white);
			ez_draw_text (win, EZ_TL, 40, 100,
					"You have finished the game :   \n\n" 
                    "I hope you enjoyed the game lol\n"
                    "Author: DRAIDIA Taha Ibrahim\n"
                    "Email: ibrahim@draidia.us\n"
                    "Website: www.draidia.us\n"
                    "Enter: back to menu\n"
                    "q: exit\n");
			
		break;
		
		default:
			printf("[*] Hors state\n ");
			
		break;
	}
    
    
  

}

