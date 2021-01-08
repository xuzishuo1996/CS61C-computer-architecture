/* File that consists of functions used to handle the information regarding
 * users that have connected to the server.
 * Author: Zishuo */

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "user_utils.h"
#include "client_server_utils.h"
#include "server.h"

/* * * * * * *READ ME* * * * * * * *
 *                                 *
 * BE SURE AND READ USER_UTILS.H   *
 * FOR THE DEFINITION OF THE       *
 * NAME_INFO AND USER_INFO         *
 * STRUCTS.                        *
 * * * * * * * * * * * * * * * * * */


/* Function that takes in a name and creates a fresh pointer with
 * the name copied over. */
char *create_name (char *name) {
	/* YOUR CODE HERE. */
    int length = strlen(name);
    char *p_name = (char *)malloc(length + 1);
    if (p_name == NULL) {
        allocation_failed();
    } else {
        strcpy(p_name, name);
        return p_name;
    }
    return NULL;
}

/* Function that takes in a name and outputs a new name_info
 * struct having that name. You cannot assume the name is valid
 * after the function exits. */

struct name_info *create_name_info (char *name) {
	/* YOUR CODE HERE */
    struct name_info *name_info_to_create = (struct name_info *)malloc(sizeof(struct name_info));
    if (name_info_to_create == NULL) {
        allocation_failed();
    }
    name_info_to_create->name = create_name(name);
    name_info_to_create->total_tracking = 0;
    return name_info_to_create;
}

/* Function that takes in a name and outputs a new struct user_info having
 * that name. The struct should be capable or producing correct
 * functionality immediately. You cannot assume that name will remain
 * a valid pointer after the function exits. One important detail about
 * the functionality is that while no user begins with a nickname all
 * attempts to communicate between two users involves the sender's
 * nickname. If there is no nickname then this
 * value should be the actual name of the user, but the code given
 * DOES NOT perform a check to see if there is nickname and then
 * access the name using the name field of the user_info struct. Instead
 * it ALWAYS uses the value given by *(user->nickname), so this must
 * always contain a valid address whose contents are either the user's
 * nickname or the user's name. */
struct user_info *create_user (char *name) {
    /* YOUR CODE HERE. */
    struct user_info *new_info = (struct user_info *)malloc(sizeof(struct user_info));
    if (new_info == NULL) {
        allocation_failed();
    }

    new_info->name_info = create_name_info(name);

    new_info->nickname = (char **)malloc(sizeof(char*));
    if (new_info->nickname == NULL) {
        allocation_failed();
    }
    *(new_info->nickname) = (char *)malloc(sizeof(strlen(new_info->name_info->name) + 1));
    if (*(new_info->nickname) == NULL) {
        allocation_failed();
    }
    strcpy(*(new_info->nickname), new_info->name_info->name);

    new_info->muted_total = 0;

    new_info->muted_capacity = 10;

    new_info->muted = (struct name_info **)malloc(new_info->muted_capacity * sizeof(struct name_info*));
    if (new_info->muted == NULL) {
        allocation_failed();
    }

    return new_info;
}

/* Function that frees the memory associated with a user. This function
 * should be filled out with some care as it is important that you
 * DO NOT free any pointers that will be accessed later. It may be useful
 * to implement a system for freeing data only once you know
 * it will no longer be used. The only requirement for when data should
 * be freed is that all data must be freed on a proper server exit. */
void cleanup_user (struct user_info *user) {
	 /* YOUR CODE HERE. */
   cleanup_name_info(user->name_info);

   free(*(user->nickname));
   free(user->nickname);

   for (int i = 0; i < user->muted_total; i++) {
      cleanup_name_info(user->muted[i]);
   }
   free(user->muted);

   free(user);
}

/* Function that frees the memory assoicated with a name info. The same
 * suggestion about freeing memory as the above function applies here as
 * well. */
void cleanup_name_info (struct name_info *info) {
	 /* YOUR CODE HERE. */
   free(info->name);
   free(info);
}

/* Function that takes in a name and determines if it is already a user's
 * name. */
bool istaken_name (char *name) {
        unsigned i = 1;
        unsigned ctr = 1;
        while (i < socket_total) {
                if (sockets[ctr] != -1) {
                        i++;
                        if (strcmp (name, users[ctr]->name_info->name) == 0) {
                                return true;
                        }
                }
                ctr++;
        }
        return false;
}

/* Function that determines if a user has a nickname. */
bool has_nickname (struct user_info *user) {
	  /* YOUR CODE HERE. (Completed)*/
    char *name = user->name_info->name;
    char **nickname = user->nickname;
    if (*nickname == NULL) {
        return false;
    } else if (strcmp(name, *nickname) == 0) {
        return false;
    } else {
        return true;
    }
}

/* Function that takes in a name and determines if a user
 * has it as a nickname. You may find the global variables users,
 * socket_total, and sockets helpful here (which are defined as extern
 * in server.h). There are socket_total - 1 clients connected and they
 * can occupy indices starting at one. A client exists at an index i
 * if sockets[i] != -1. Once you have seen all the clients you should
 * not continue checking later indices. Finally simply because a client
 * is connected does not mean they necessarily have user information
 * yet. If a client is connected at index i but does not have user
 * information yet users[i] will be NULL. */
bool istaken_nickname (char *name) {
	/* YOUR CODE HERE.(Completed) */
        int s_index = 1;
        int u_index = 1;  //or 0?
        while (s_index < socket_total) {
            if (sockets[s_index] != -1) {
                s_index++;
                if (has_nickname(users[u_index])) {
                      if(strcmp(name, *(users[u_index]->nickname)) == 0) {
                          return true;
                      }
                }
            }
            u_index++;
        }
        return false;
}

/* Function that takes in a name and return the user who has that name as their
 * actual name. Returns NULL is no user has that actual name. */
struct user_info *find_user (char *name) {
        int start = 1;
        int ctr = 1;
        while (start < socket_total) {
                if (sockets[ctr] != -1) {
                        start++;
                        if (strcmp (users[ctr]->name_info->name, name) == 0) {
                                return users[ctr];
                        }
                }
                ctr++;
        }
        return NULL;
}


/* Takes in a two users and checks if the first user has muted the second
 * user. */
bool ismuted (struct user_info *receiving_user, struct user_info *possibly_muted_user) {
        /* YOUR CODE HERE. (Completed)*/
        int num_of_muted = receiving_user -> muted_total;
        for (int i = 0; i < num_of_muted; i++) {
            if (strcmp( (receiving_user->muted[i])->name, possibly_muted_user->name_info->name) == 0) {
                return true;
            }
        }
        return false;
}
