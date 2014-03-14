/*
//  angrybirds-events.c
//  
//
//  Created by Benoit Favre and Valentin Emiya on 27/02/13.
//	Edited by DRAIDIA Taha Ibrahim
//  Copyright (c) 2013 CNRS LIF, Aix-Marseille Univ. All rights reserved.
*/

#include <unistd.h>
#include "../include/zombie-events.h"
#include "../include/zombie-graphics.h"
#include "../include/zombie-main.h"
#include "../include/zombie-algorithm.h"
User *U;
int i,player_position;
typedef enum {
    TEXT_FINISHED,
    TEXT_CHANGED,
    TEXT_UNCHANGED
} InputStatus;

/** Saisie de texte (voir tutoriel Ez-Draw)
  \param ev : evenement de type KeyPress
  \param text : chaine de caractere ou doit etre ajoute le texte
  \return TEXT_CHANGED si l'affichage doit etre refait, TEXT_FINISHED si texte termine, TEXT_UNCHANGED sinon 
*/
InputStatus input_text (Ez_event *ev, char *text, int max_size)
{
	int i;
    switch (ev->key_sym) {

        case XK_BackSpace :                               /* Touche backspace */
            i = strlen (text);
            if (i == 0) break;
            text[i - 1] = '\0';
            return TEXT_CHANGED;

        case XK_Return :                                     /* Touche Entree */
            return TEXT_FINISHED;

        default :                                 /* Insertion d'un caractere */
            if (ev->key_count != 1) break;
            i = strlen (text);
            if (i >= max_size - 1) break;
            text[i] = ev->key_string[0]; text[i + 1] = '\0';
            return TEXT_CHANGED;
    }
    return TEXT_UNCHANGED;
}


/** Fonction qui traite les evenements (voir sujet pour details) :
      Expose: reafficher le contenu de la fenetre
      KeyPress: gerer l'appui sur les touches dans le menu et lors de la saisie du nom
      MotionNotify: mouvement de la souris lors de la selection de la vitesse d'origine
      ButtonRelease: quand on clique
      TimerNotify: met a jour la simulation au bout de 10ms
   Cette fonction est appelee par le gestionnaire de fenetre.
*/
void win1_event (Ez_event *ev) {
    Game_parameters *game = ez_get_data (ev->win);
    
    switch (ev->type) {
            
        case Expose :
            redraw(ev->win);
            break;
            
        case KeyPress :
            /* A COMPLETER */
			switch(game->state)
			{
				case STATE_ENTERING_NAME:
				
					switch(input_text(ev,game->typed_text,USER_MAX_NAME)) 
						{

							case TEXT_FINISHED:
								game->current_user=user_get(&(game->users),game->typed_text);
								game->state=STATE_MENU;
								ez_send_expose(ev->win);
								break;
						
							case TEXT_CHANGED:
								ez_send_expose(ev->win);
								break;
								
							case TEXT_UNCHANGED:
								ez_send_expose(ev->win);
								break;
							default:
							
							break;
			
						}
						break;
				break;
				
				case STATE_MENU: /* menu */
					switch(ev->key_sym)
                    {
                       case XK_h:
                            game->state=STATE_HELP;
                            ez_send_expose(ev->win);
                            break;
                        case XK_q:
                            ez_quit();
                            break;
                            case XK_a:
                            game->state=STATE_ABOUT;
                            ez_send_expose(ev->win);
                            break;
                        case XK_Return:
							ez_timer_add(ev->win, 10);
                            game->state=STATE_AIMING;
                            init_simulation(game);
                            ez_timer_add(ev->win, 10);
                            ez_send_expose(ev->win);
                            break;
                        case XK_s:
                            game->state=STATE_TOPSCORES;
                            /*game->users=user_sort(game->users);*/
                            ez_send_expose(ev->win);
                            break;
                        case XK_n:
                            game->typed_text[0]='\0';
                            game->state=STATE_ENTERING_NAME;
                            ez_send_expose(ev->win);
                            break;
                        
                        default:
							
                        break;
                    }
                    break;
                    
                    
					
					case STATE_TOPSCORES:
							switch(ev->key_sym)
						{
							case XK_m:
                            game->state=STATE_MENU;
                            ez_send_expose(ev->win);
                            break;
                            
							case XK_q:
                            ez_quit();
                            break;
						}
					break;
					
					case STATE_HELP:
							switch(ev->key_sym)
						{
							case XK_h:
                            system("firefox www.draidia.us/zombieVSghost/help &");
                            break;
                            
							case XK_m:
                            game->state=STATE_MENU;
                            ez_send_expose(ev->win);
                            break;
                            
							case XK_q:
							printf("[+] Good bye see you soon\n");
                            ez_quit();
                            break;
						}
					break;
					case STATE_ABOUT:
							switch(ev->key_sym)
						{
							case XK_w:
                            system("firefox www.draidia.us/zombieVSghost/ &");
                            break;
                            
							case XK_m:
                            game->state=STATE_MENU;
                            ez_send_expose(ev->win);
                            break;
                            
							case XK_q:
							printf("[+] Good bye see you soon\n");
                            ez_quit();
                            break;
						}
					break;
					case STATE_AIMING:
							
							
							switch(ev->key_sym)
						{
							
							case XK_m:
                            game->state=STATE_MENU;
                            ez_send_expose(ev->win);
                            break;
                            
							case XK_q:
                            ez_quit();
                            break;
						}
					break;
					case STATE_FLYING:  /* Fly */
							
							switch(ev->key_sym)
						{
							case XK_m:
                            game->state=STATE_MENU;
                            ez_send_expose(ev->win);
                            break;
                            
							case XK_q:
                            ez_quit();
                            break;
						}
					break;
					case STATE_HIT:
							
							switch(ev->key_sym)
						{
							case XK_n:
                            game->lvl++;
                            if(game->lvl == 9)
                            {
								game->state=STATE_FINISH;
								ez_send_expose(ev->win);
							}
							else
							{
							ez_timer_add(ev->win, 10);
							game->state=STATE_AIMING;
							init_simulation(game);
                            ez_send_expose(ev->win);
							}
                            break;
							case XK_Return:
                            ez_timer_add(ev->win, 10);
							game->state=STATE_AIMING;
							init_simulation(game);
							ez_send_expose(ev->win);
                            break;
							case XK_m:
                            game->state=STATE_MENU;
                            ez_send_expose(ev->win);
                            break;
                            
							case XK_q:
							printf("[+] Good bye see you soon\n");
                            ez_quit();
                            break;
						}
					break;
					break;
					case STATE_MISS:
							
							switch(ev->key_sym)
						{
							case XK_Return:
							
                            game->state=STATE_AIMING;
                            init_simulation(game);
                            ez_send_expose(ev->win);
                           
                            break;
							case XK_m:
						
                            game->state=STATE_MENU;
                            ez_send_expose(ev->win);
                            break;
                            
							case XK_q:
							printf("[+] Good bye see you soon\n");
                            ez_quit();
                            break;
						}
					break;
					
					/* lose */
					
					case STATE_LOSE:
						switch(ev->key_sym)
						{
							case XK_Return:
							game->lvl = 1;
                            game->state=STATE_AIMING;
                            init_simulation(game);
                            ez_send_expose(ev->win);
                            break;
                            
							case XK_m:
							
                            game->state=STATE_MENU;
                            ez_send_expose(ev->win);
                            break;
						}
					break;
					/* FIN DU JEU */
					case STATE_FINISH:
						switch(ev->key_sym)
						{
							case XK_Return:
                            game->state=STATE_MENU;
                            ez_send_expose(ev->win);
                            break;
                            
							case XK_q:
							printf("[+] Good bye see you soon\n");
                            ez_quit();
                            break;
						}
						break;
					
					
					default:
					
					break;
					break;
				}
				

			case MotionNotify :
				
				switch(game->state)
				{
					case STATE_AIMING:
						game->mouse.x=ev->mx;
						game->mouse.y=ev->my;
						ez_send_expose(ev->win);
					break;
					default: break;
					}
					break;
				
				
				
				

			case ButtonRelease :
				
				switch(game->state)
				{
					case STATE_HIT:
							/*  next lvl button */
							 if ((ev->mx >= 150) && (ev->mx <= 260) && (ev->my >=  214) && (ev->my <= 280) ) 
							 {
									game->lvl++;
									if(game->lvl == 9)
									{
										game->state=STATE_FINISH;
										ez_send_expose(ev->win);
									}
									else
									{
									ez_timer_add(ev->win, 10);
									game->state=STATE_AIMING;
									init_simulation(game);
									ez_send_expose(ev->win);
									}
							}
								/*  play again button */
							 if ((ev->mx >= 150) && (ev->mx <= 295) && (ev->my >=  294) && (ev->my <= 361) ) 
							 {
									ez_timer_add(ev->win, 10);
									game->state=STATE_AIMING;
									init_simulation(game);
									ez_send_expose(ev->win);
							}
								/*  menu button */
							 if ((ev->mx >= 150) && (ev->mx <= 260) && (ev->my >=  375) && (ev->my <= 443) ) 
							 {
									game->state=STATE_MENU;
									ez_send_expose(ev->win);
							}
					break;
					case STATE_TOPSCORES:
								/*  reset  button */
							 if ((ev->mx >= 54) && (ev->mx <= 157) && (ev->my >=  454) && (ev->my <= 522) ) 
							 {
									U=game->users;
									i=0;
									player_position=1;
									while((U != NULL) && (player_position < 11)){
										U->name = "empty";
										U->hits = 0;
										U->tries = 0;
										ez_draw_text(ev->win, EZ_TL, 50, 200+i, "%d : %s %d %d", player_position, U->name, U->hits, U->tries);
										i+=20;
										U=U->next;
										player_position++;
									}
									game->state=STATE_TOPSCORES;
									ez_send_expose(ev->win);
							 }
							
								/*  back to menu button */
							 if ((ev->mx >= 170) && (ev->mx <= 273) && (ev->my >=  454) && (ev->my <= 522) ) 
							 {
									game->state=STATE_MENU;
									ez_send_expose(ev->win);
							 }
					break;
					case STATE_LOSE:
								/*  play again  button */
							 if ((ev->mx >= 150) && (ev->mx <= 260) && (ev->my >=  473) && (ev->my <= 540) ) 
							 {
									/* init lvl*/
									game->lvl = 1;
									/*  init  hits et tries */
									game->current_user->hits = 0;
									game->current_user->tries = 0;
									game->state=STATE_AIMING;
									init_simulation(game);
									ez_send_expose(ev->win);
							 }
							
								/*  back to menu button */
							 if ((ev->mx >= 540) && (ev->mx <= 644) && (ev->my >=  473) && (ev->my <= 540) ) 
							 {
									game->state=STATE_MENU;
									ez_send_expose(ev->win);
							 }
					break;
					case STATE_ABOUT:
								/*  web page button  */
							 if ((ev->mx >= 150) && (ev->mx <= 260) && (ev->my >=  457) && (ev->my <= 519) ) 
							 {
									printf("[+]---Web page---[+]\n");
									system("firefox www.draidia.us/zombieVSghost/ &");
							 }
							
								/*  back to menu button  */
							 if ((ev->mx >= 270) && (ev->mx <= 490) && (ev->my >=  457) && (ev->my <= 519) ) 
							 {
									game->state=STATE_MENU;
									ez_send_expose(ev->win);
							 }
					break;
					case STATE_HELP:
								/*  web  page button */
							 if ((ev->mx >= 150) && (ev->mx <= 260) && (ev->my >=  457) && (ev->my <= 519) ) 
							 {
									printf("[+]---Web page---[+]\n");
									system("firefox www.draidia.us/zombieVSghost/ &");
							 }
							
								/*  back to menu button */
							 if ((ev->mx >= 270) && (ev->mx <= 490) && (ev->my >=  457) && (ev->my <= 519) ) 
							 {
									game->state=STATE_MENU;
									ez_send_expose(ev->win);
								 }
					break;
					case STATE_MENU:
								/*  new game button  */
							 if ((ev->mx >= 150) && (ev->mx <= 260) && (ev->my >=  55) && (ev->my <= 121) ) 
							 {
									/*  inintialisation des variable hits et tries */
									game->current_user->hits = 0;
									game->current_user->tries = 0;
									game->state=STATE_AIMING;
									init_simulation(game);
									ez_send_expose(ev->win);
							 }
							
								/*  Nickname  button */
							 if ((ev->mx >= 150) && (ev->mx <= 260) && (ev->my >=  135) && (ev->my <= 201) ) 
							 {
									game->state=STATE_ENTERING_NAME;
									ez_send_expose(ev->win);
							 }
								/*  topscores  button */
							 if ((ev->mx >= 150) && (ev->mx <= 260) && (ev->my >=  214) && (ev->my <= 280) ) 
							 {
									game->state=STATE_TOPSCORES;
									ez_send_expose(ev->win);
							}
								/*  help  button */
							
							 if ((ev->mx >= 150) && (ev->mx <= 295) && (ev->my >=  294) && (ev->my <= 361) ) 
							 {
									game->state=STATE_HELP;
									ez_send_expose(ev->win);
							}
								/*  about button  */
							 if ((ev->mx >= 150) && (ev->mx <= 260) && (ev->my >=  375) && (ev->my <= 443) ) 
							 {
									game->state=STATE_ABOUT;
									ez_send_expose(ev->win);
							}
								/*  exit button  */
							 if ((ev->mx >= 150) && (ev->mx <= 260) && (ev->my >=  455) && (ev->my <= 522) ) 
							 {
									ez_quit();
							 }
							game->mouse.x=ev->mx;
							game->mouse.y=ev->my;
							ez_send_expose(ev->win);
					break;
					case STATE_AIMING:
							/* update tries  */ 
							game->current_user->tries++;
							game->velocity.x = (game->zombie.center.x - game->mouse.x)/20;
							game->velocity.y = (game->zombie.center.y - game->mouse.y)/20;
							ez_timer_add(ev->win, 10);
							game->state=STATE_FLYING;
							ez_send_expose(ev->win);
					break;
					default: break;
					}
				
				break;

			case TimerNotify:
			
				
				/* page de loading 5 secondes */
				if(game->state == STATE_SPLASH)
				{
					ez_send_expose (ev->win);
					sleep(5);
					game->state=STATE_ENTERING_NAME;
				}
				/* pour pouvoir rendre le jeu dynamique 'les caracteres qui bougent ' */
				if(game->state == STATE_AIMING)
				{
					ez_timer_add(ev->win, 10);
					/* fonction qui rends le jeu animé  'bouger l'enemies et obstacle '*/
					moveGraveGhost (game);
					ez_send_expose(ev->win);
				}
				 if(game->state == STATE_FLYING)
				{
					/* fonction qui rends le jeu animé  'bouger l'enemies et obstacle '*/
					moveGraveGhost (game);
					if(simulation_step(game) == true)
					{
						ez_timer_add(ev->win, 10);
						ez_send_expose(ev->win);
					}
					ez_send_expose(ev->win);
					
				}
				
				break;
				
			 default:  break;
		}
    
}
