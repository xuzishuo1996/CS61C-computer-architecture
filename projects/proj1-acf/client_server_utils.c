/* File of shared functions between the server and the client
 * Author: Zishuo Xu */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "client_server_utils.h"


/* Function that finds the index at which the newline character exists in the
 * message. Returns -1 if no newline exists in the string. START is in the
 * index in the start at which the search should begin. */
int find_message_end (char *msg, int start) {
        /* YOUR CODE HERE. */
        int index = start;
        char *curr = msg + start;
        while ((*curr) != '\0') {
            if((*curr) != '\n') {
                curr += 1;
                index++;
            } else {
                return index;
            }
        }
        return -1;
}

/* Function that takes a char * which is a buffer of data received. This
 * buffer contains 1 or MESSAGES where a message is defined as being a
 * series of characters ending in a newline. Its other parameter, end,
 * is the length of the first message in the buffer. If MESSAGES contains more
 * than one message then these messages WILL NOT be separated by a null
 * terminator. However, MESSAGES will always be terminated by a null
 * terminator. The function should malloc and outputs a new char * consisting
 * of the first message (which needs end + 1 Bytes). It should also update
 * MESSAGES so that its contents are a string that contains any remaining
 * messages and just a null terminator if no more messages remain. You may
 * want to use some combination of strlen, strcpy, and strncpy. As an
 * important note if you elect to attempt to use strcpy or strncpy for this
 * function the dst pointer and the src pointer cannot contain addresses that
 * will overlap. This means the address of any information from src cannot be
 * the same as an address that gets written to in dst */
char *generate_message (char *messages, int end) {
	      /* YOUR CODE HERE.*/
        /* Extracts the first message. */
        char *first_message = (char *)malloc(end + 1);  //null terminator included.
        if (first_message == NULL) {
            allocation_failed ();
        }
        strncpy(first_message, messages, end);
        first_message[end] = '\0';    //Appends a null terminator.

        char *remain = (char *)malloc(strlen(messages + end) + 1);  //null terminator included.
        if (remain == NULL) {
            allocation_failed ();
        }
        strcpy(remain, messages + end);
        strcpy(messages, remain);
        free(remain);

        return first_message;
}

/* Function that terminates the program when a malloc fails. */
void allocation_failed () {
        fprintf (stderr, "Unable to allocate enough memory\n");
        exit (1);
}