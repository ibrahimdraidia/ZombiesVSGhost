/*
//  zombie-main.h
//  
//
//  Created by Benoit Favre and Valentin Emiya on 27/02/13.
* 	Edited by DRAIDIA Taha Ibrahim.
//  Copyright (c) 2013 CNRS LIF, Aix-Marseille Univ. All rights reserved.
*/

#ifndef _angrybirds_main_h
#define _angrybirds_main_h


#include "ez-image.h"

#include "zombie-user.h"

#define true 1
#define false 0

/** vecteur a 2 dimensions
  */
typedef struct {
    double x;
    double y;
} Vector;

/** rectangle aligne avec les axes determine par sont origine, sa longueur et
   sa hauteur
  */
typedef struct {
    double x, y, width, height;
} Rectangle;

/** cercle defini par son centre et son rayon
  */
typedef struct {
    Vector center;
    double radius;
} Circle;

/** etats possible pour le jeu
  */
enum Game_state {
    STATE_SPLASH, 	    /*  SplashScreen */
    STATE_ENTERING_NAME,    /* le joueur est en train de saisir son nom */
    STATE_MENU,             /* le menu est affiche */
    STATE_TOPSCORES,        /* les 10 meilleurs scores sont affiches */
    STATE_ABOUT,            /* About */
    STATE_HELP,		        /* Help */
    STATE_AIMING,           /* le joueur est en train de choisir la force de depart de l'oiseau */
    STATE_FLYING,           /* simulation du vol de l'oiseau */
    STATE_HIT,              /* l'oiseau a touche le cochon */
    STATE_MISS,              /* l'oiseau a touche le decor */
    STATE_LOSE,             /*  lose */ 
    STATE_FINISH             /* fin du jeu */
};

/** Cette structure contient tous les parametres du jeu
  */
typedef struct game_parameters {
    enum Game_state state;       /* etat du jeu */
	
	Circle grave;			/* position et rayon de la tombe */
    Circle zombie;            /* position et rayon de zombie */
    Circle ghost;             /* position et rayon du ghost */
    Circle linux;           /*  linux enemie 2 */
    Circle linux2;          /* linux2 enemie 3 */ 
    Rectangle obstacle;     /* obstacle rectangulaire */
    Vector velocity;        /* vitesse de l'oiseau */
    Vector speed;         	/* vitesse du ghost */
    Vector sdlinux;			/* vitesse du linux*/
    Vector gravity;         /* force de gravite */

    Vector mouse;           /* position de la souris */
    char* typed_text;       /* text tape lors de la saisie de texte */

    /* images pour afficher les acteurs du jeu (on pourrait rajouter le décor, l'obstacle...) */
    Image *zombieImage;
    Image *ghostImage;
	Image *bg;
	Image *menu;
	Image *graveImage;
	Image *bossImage;
	Image *load;
	Image *tank;
	Image *sniper;
	Image *alien;
	Image *linuxImage;
	Image *gameOver;
	/* buttons img */
	Image *newGame;
	Image *nickname;
	Image *scores;
	Image *help;
	Image *about;
	Image *exit;
	Image *web;
	Image *replay;
	Image *btmenu;
	Image *reset;
	Image *next;
	
    /* nom et score des joueurs */
    User *current_user;     /* joueur courant */
    User *users;            /* liste chainee des utilisateurs connus */
    
    /* level */
    int lvl;
    
} Game_parameters;

void init_game (Game_parameters *game);
void end_game(Game_parameters *game);

#endif
