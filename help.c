#include <stdio.h>

void help() {
	printf("Help\n\n");
	printf("Usage: minix <command>\n\n");
	printf("Commands:\n");
	printf("help\n");
	printf("\t displays this help\n");
	printf("minimount <argument>\n");
	printf("\t mounts a local minix disk; <argument> is the name of the image file to mount\n");
	printf("miniumount\n");
	printf("\t unmounts the currently mounted disk\n");
	printf("showsuper\n");
	printf("\t lists the information in the super block\n");
	printf("traverse [-l]\n");
	printf("\t lists the contents of the root directory\n");
	printf("\t using the -l switch displays detailed information of the contents\n");
	printf("showzone <zone number>\n");
	printf("\t shows the ASCII content of the specified zone\n");
	printf("quit\n");
	printf("\t quit the minix shell\n");
}
