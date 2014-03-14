/*
//  zombie-user.c
//
//
//  Created by Benoit Favre and Valentin Emiya and Andre Abrame on 04/03/13.
//  Edited by DRAIDIA Taha Ibrahim
//  Copyright (c) 2013 CNRS LIF, Aix-Marseille Univ. All rights reserved.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../include/zombie-user.h"


/** Read the users data file. If there is no file,
    the users list will be initialized empty.
    \param filename: path of the file to read.
    \return a pointer to the first element of the users list.
 */
User* user_read_file(char *filename) {
	char N[USER_MAX_NAME];
	int tries, hits;
    FILE *F;
    User *U, *V=NULL;
    if((F=fopen(filename,"r"))==NULL)
		return(NULL);
	while(fscanf(F,"%s %d %d ", N, &(tries), &(hits)) > 0){
		U=malloc(sizeof(User));
		U->name=malloc((strlen(N)+1)*sizeof(char));
		U->tries=tries;
		U->hits=hits;
		strcpy(U->name,N);
		U->next=V;
		V=U;
	}
	fclose(F);
	return V;
}


/** Writes the users data in a file.
   \param list: pointer to the first element of the users list.
   \param filename : path of the file to write.
*/
void user_write_file(User* list, char *filename) {
    FILE *F=fopen(filename, "w");
    if(F==NULL)
		exit(0);
    while(list != NULL){
        fprintf(F, "%s %d %d\n", list->name, list->tries, list->hits);
        list=list->next;
    }
    fclose(F);
}

/** Search a player in the list and add him if he's doesn't exist. Return a pointer to the player.
    \param list : Pointer adresse to the first element of the users list (can be modified if we add the player)
    \param name : player's name.
    \return a pointer to player's data.
 */
User* user_get(User** list_ptr, const char* name) {
    User *L = *list_ptr, *U;
    while(L != NULL){
        if (strcmp(L->name, name) == 0)
            return (L);
        L=L->next;
    }
    U=malloc(sizeof(User));
    U->tries=0;
    U->hits=0;
    U->name=malloc((strlen(name)+1)*sizeof(char));
    strcpy(U->name, name);
    U->next=*list_ptr;
    *list_ptr=U;
    return U;
}


/** Tidy list player by decreasing score.
    \return un pointeur vers le premier element de la liste rangee.
 */
/* User* user_sort(User* list) {
    return 0;
}
*/

/** Frees the used memory by the users list.
    \param list : pointer to the first element of the list.
 */
void user_free(User* list) {
    User *p;
    while(list != NULL){
		free(list->name);
		p = list->next;
		free(list);
		list = p;
	}
}
