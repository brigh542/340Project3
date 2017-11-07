#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include "minix.h"

// Calls from main:
// traverse(fd, 0) for short
// traverse(fd, 1) for -l flag

void traverse(int fd, int detailPrint) {

	if(detailPrint == 0)
		system("ls");
	else if(detailPrint == 1)
		system("ls -l");

}
