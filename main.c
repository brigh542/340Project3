#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
//#include "minix.h"

char* path;

//indicates whether image is mounted or not
int mounted = 0; 

//make character global variable to hold the input text. Everytime new variable, put through to function
//quit, print, etc.

int main() {

	char *introString = "Welcome to MINIX.\n";
	write(1, welcome, strlen(welcome));

	char* input;

	while (1) {
		input = (char *) calloc(10000, 1);

		write(1, "minix>>", 7);
		read(0, input, 10000);

		if (strcmp(input, "help\n") == 0) {
			help();
		} else if (strstr(input, "minimount") != NULL) {

			imagePath = (char *)calloc(265, 1);
			strncpy(imagePath, strstr(input, "minimount") + 10,
					strlen(strstr(input, "minimount") + 11));

			if( access( imagePath, F_OK ) != -1 ) {
			    isMounted = 1;
				write(1, "Disk mounted.\n", 14);
			} else {
			    write(1, "File does not exist at that location\n", 37);
			}

		} else if ((strstr(input, "miniumount\n")) != NULL) {

			isMounted = 0;
			free(imagePath);
			write(1, "Disk unmounted.\n", 16); 

		} else if (strstr(input, "showsuper\n") != NULL) {

			showsuper();

		} else if (strstr(input, "traverse") != NULL) {

			char* lSwitch = (char *) calloc(3, 1);
			lSwitch = strstr(input, "traverse") + 9;

			if (strcmp(lSwitch, "-l\n") == 0)
				traverse(1);
			else
				traverse(0);

		} else if (strstr(input, "showzone") != NULL) {

			char* zone = (char *)calloc(5, 1);

			strncpy(zone, strstr(input, "showzone") + 9,
					strlen(strstr(input, "showzone") + 10));
			zone[sizeof(zone) - 1] = '\0';

			showzone(zone);

		} else if (strstr(input, "showfile") != NULL) {

			char* fileName = (char *) calloc(265, 1);
			strncpy(fileName , strstr(input, "showfile") + 9,
					strlen(strstr(input, "showfile") + 10));

			showfile(fileName);

		} else if (strstr(input, "quit") != NULL) {
			write(1, "\nYou will now quit out of the minix shell.\n", 43);
			free(input);
			input = NULL;
			return 0;
			
		} else {
			char* helpMessage =
					"Invalid Command. \nPlease type help to see the list of available commands.\n";
			write(1, helpMessage, strlen(helpMessage));
		}
		free(input);
		input = NULL;
	}

	free(welcome);

	return 0;
}
