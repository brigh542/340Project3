//final

#include "shell.h"
#define BUF 10000

char *image;

int mounted = 0;



int main(){

	char *intro = "Welcome to Minix.\n";
	char *nomountMessage = "Please mount the image file.\n";
	char *unmountMessage = "Disk has been unmounted.\n";
	char *mountMessage = "Disk mounted.\n";
	char *fileExistMessage = "File does not exist here.\n";
	char *invalidCommand = "Sorry, that is an invalid command. Type help to view a list of commands.\n"; 
	char *userInput;
	
	int fd;

	write(1, intro, strlen(intro));

	while(1) {
		userInput = (char *) calloc(BUF, 1);
		
		write(1, "minix: ", 7);
		read(0, userInput, BUF);

		if(strcmp(userInput, "help\n") == 0){
			help();
		}
		else if(strcmp(userInput, "quit\n") == 0){
			if(userInput != NULL){
				free(userInput);
				userInput = NULL;			
			}
			quit();
			return 0;
		} 
		else if(strstr(userInput, "minimount")!=NULL){
			image = (char *)calloc(265,1);
			strncpy(image, strstr(userInput, "minimount") + 10, strlen(strstr(userInput, "minimount")+11));
			if(access(image, F_OK) != -1){
				mounted =1;
				write(1, mountMessage, strlen(mountMessage));			
			}
			else{
				write(1,fileExistMessage, strlen(fileExistMessage)); 
			}
		}
		else if(strstr(userInput, "miniumount")!=NULL){
			mounted=0;
			free(image);
			write(1, unmountMessage, strlen(unmountMessage));	
		}
		else if(strstr(userInput, "showsuper\n") !=NULL){
			if(mounted == 1){
				fd = open(image, O_RDONLY);
				showsuper(fd);
			}
			else{
				write(1, nomountMessage, strlen(nomountMessage));
			}
		}
		else if(strstr(userInput, "showzone")!=NULL){

			//first check if mounted
			if(mounted ==1){
				char  *number=(char *)calloc(5, 1);
			
				strncpy(number, strstr(userInput, "showzone")+9, strlen(strstr(userInput, "showzone") +10));
			
				number[sizeof(number) - 1] = '\0';
			
				fd = open(image, O_RDONLY);
				showzone(fd, number);
			}
			else{
				write(1, nomountMessage, strlen(nomountMessage));			
			}
		
		}
		else if(strstr(userInput, "showfile") != NULL){
			if(mounted ==1){
				char *file = (char *) calloc(265, 1);
				strncpy(file,strstr(userInput, "showfile")+9, strlen(strstr(userInput, "showfile")+10));
				fd=open(image, O_RDONLY);
				showfile(fd, file);
			}
			else{
				write(1, nomountMessage, strlen(nomountMessage));
			}
			
		}
		else if(strstr(userInput, "traverse") != NULL){
			if (mounted ==1){
				char *tem = strtok(NULL, "\n ");
				if(tem == NULL){
					fd=open(image, O_RDONLY);
					//traverse(fd, 0);

				}else if(strcmp(tem, "-l") == 0){
					//traverse(fd, 1);
				}else{
					printf("Please try again.\n");
				}
					
			}
			else {
				write(1, nomountMessage, strlen(nomountMessage));
			} 

		}
		else{
			write(1, invalidCommand, strlen(invalidCommand));
		}
		
		free(userInput);
		userInput = NULL;
	}

	free(intro);
	return 0;

}
