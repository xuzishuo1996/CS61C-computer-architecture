#include <stdio.h>
#include <stdlib.h>

void f (int *ptr) {
	*(ptr) = 6;
	free (ptr);
}

int main () {
	int *ptr = malloc (sizeof (int));
	*ptr = 1;
	f (ptr);
	(*ptr)++;
	printf ("And the variable is...... %d\n", *ptr);
}
