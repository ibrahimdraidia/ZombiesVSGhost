/*
//  angrybirds-game.c
//  
//
//  Created by Benoit Favre and Valentin Emiya on 27/02/13.
//	Edited by DRAIDIA Taha Ibrahim.
//  Copyright (c) 2013 CNRS LIF, Aix-Marseille Univ. All rights reserved.
*/

#include "../include/zombie-main.h"
#include "../include/zombie-events.h"


/** Cette fonction est appelee une fois au debut du programme.
  Elle charge les scores des utilisateurs, charge les images pour l'affichage,
  initialise le vecteur representant la force de gravite, et initialise les
  divers parametres du jeu.
  */
void init_game (Game_parameters *game) {
    /* design */
    game->zombieImage = ez_load_image("../img/head.png", 0xff00ff);
    game->bossImage = ez_load_image("../img/boss.png", 0xff00ff);
    game->ghostImage = ez_load_image("../img/ghost.png", 0xff0000);
    game->bg = ez_load_image("../img/bg.png", EZ_IMAGE_NO_MASK);
    game->menu = ez_load_image("../img/menu.png", EZ_IMAGE_NO_MASK);
    game->load = ez_load_image("../img/load.png", EZ_IMAGE_NO_MASK);
    game->gameOver = ez_load_image("../img/over.png", EZ_IMAGE_NO_MASK);
    game->graveImage = ez_load_image("../img/grave.png", 0xff00ff);
    game->tank = ez_load_image("../img/tank.png", 0xff00ff);
    /*game->sniper = ez_load_image("../img/sniper.png", 0xff00ff);*/       
    game->linuxImage = ez_load_image("../img/angel.png", 0xff00ff);
    /* buttons img */
    game->newGame = ez_load_image("../img/buttons/new.png", EZ_IMAGE_NO_MASK);
    game->nickname = ez_load_image("../img/buttons/name.png", EZ_IMAGE_NO_MASK);
    game->scores = ez_load_image("../img/buttons/scores.png", EZ_IMAGE_NO_MASK);
    game->about = ez_load_image("../img/buttons/about.png", EZ_IMAGE_NO_MASK);
    game->help = ez_load_image("../img/buttons/help.png", EZ_IMAGE_NO_MASK);
    game->exit = ez_load_image("../img/buttons/exit.png", EZ_IMAGE_NO_MASK);
    game->replay = ez_load_image("../img/buttons/replay.png", EZ_IMAGE_NO_MASK);
    game->web = ez_load_image("../img/buttons/web.png", EZ_IMAGE_NO_MASK);
    game->btmenu = ez_load_image("../img/buttons/menu.png", EZ_IMAGE_NO_MASK);
    game->reset = ez_load_image("../img/buttons/reset.png", EZ_IMAGE_NO_MASK);
    game->next = ez_load_image("../img/buttons/next.png", EZ_IMAGE_NO_MASK);
    /* init gravity */
    game->typed_text = malloc(USER_MAX_NAME);
    game->typed_text[0] = '\0';
	game->gravity.x = 0;
	game->gravity.y = 0.1;
	game->users = user_read_file(USER_FILE);
	/* init level */
    game->lvl = 1;
    /* init speed */
    game->sdlinux.x = 2;
    game->sdlinux.y = 2;
	game->speed.x = 3;
	game->speed.y = 3;
    game->state = STATE_SPLASH;

}

/** Cette fonction est appelee une fois avant de quitter le programme.
  Elle doit liberer la memoire associee aux image, ecrire le fichier
  d'utilisateurs et liberer la memoire occupee par la liste d'utilisateurs.
  */
void end_game(Game_parameters *game) {
    /* free design imagies */
    ez_free_image(game->zombieImage);
    ez_free_image(game->ghostImage);
    ez_free_image(game->menu);
    ez_free_image(game->bg);
    ez_free_image(game->graveImage);
    ez_free_image(game->load);
    ez_free_image(game->bossImage);
    ez_free_image(game->linuxImage);
    ez_free_image(game->gameOver);
    ez_free_image(game->tank);
    /* free buttons img */
    ez_free_image(game->newGame);
    ez_free_image(game->btmenu);
    ez_free_image(game->next);
    ez_free_image(game->reset);
    ez_free_image(game->web);
    ez_free_image(game->about);
    ez_free_image(game->help);
    ez_free_image(game->exit);
    ez_free_image(game->scores);
    ez_free_image(game->replay);
    ez_free_image(game->nickname);
    free(game->typed_text);
	user_write_file(game->users,USER_FILE);
	user_free(game->users);
    

}


/** Programme principal qui s'occupe d'initialiser le jeu, creer la fenetre
  lancer la boucle d'evenements ez-draw et de finir le jeu.
  */
int main ()
{
	
    Game_parameters game;
    Window win;
    
    if (ez_init() < 0)
        exit(EXIT_FAILURE);
    
    /* Initilisation des paramètres */
    init_game(&game);
    
    /* Création de la fenêtre */
   
    win = ez_window_create (800, 600, "Zombies VS Ghost By DRAIDIA Taha Ibrahim", win1_event);
    
    /* Mémorisation les paramètres dans la fenêtre */
    ez_set_data (win, &game);
    
    /* configure ez-draw to use double buffering to prevent screen flickering */
    ez_window_dbuf(win, true);
	
	/* timer pour le splash * */
	ez_start_timer (win, 10);
	
	
    /* process events */
    ez_main_loop ();

    /* free structures and save scores */
    end_game(&game);

    exit(EXIT_SUCCESS);
}
