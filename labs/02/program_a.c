#include <stdlib.h>
#include <stdio.h>

int *pi;

void f () {
	pi = malloc (sizeof (int));
	*pi = 3;
	printf ("*pi is %d\n", *pi);
	free (pi);
}

int main () {
	pi = malloc (sizeof (int));
	*pi = 4;
	f ();
}
