/*
//  angrybirds-user.h
//  
//
//  Created by Benoit Favre and Valentin Emiya and Andre Abrame on 04/03/13.
//	Edited by DRAIDIA Taha Ibrahim.
//  Copyright (c) 2013 CNRS LIF, Aix-Marseille Univ. All rights reserved.
*/

#ifndef _zombie_user_h
#define _zombie_user_h

#define USER_MAX_NAME 256
#define USER_FILE ".utilisateurs"

typedef struct user {
  char *name;
  int tries;
  int hits;
  struct user* next;
} User;

User* user_read_file(char *filename);
void user_write_file(User* list, char *filename);
User* user_get(User** list, const char* name);
User* user_sort(User* list);
void user_free(User* list);

#endif
