/*
 * 
 * Created by DRAIDIA Taha Ibrahim.
 *
 *  */

#ifndef _zombie_score_h
#define _zombie_score_h

int score(Game_parameters *game, int vies);
void WriteData(Game_parameters *game,char *fileName, int vies);
void ReadData(Window win,char *fileName);

#endif
