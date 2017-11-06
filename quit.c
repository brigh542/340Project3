#include "minix.h"

void quit() {
	if (mounted == 1)
		free(image);
	printf("Exiting Minix shell.");
	exit(0);
}
