#include "minix.h"
#define BUF 10000

char* image;

int mounted = 0;

int main() {

	
	char *intro = "Welcome to MINIX.\n";
	
	write(1, intro, strlen(intro));

	char* userInput;

	//while (1) - indicates that no error or nothing written
  	//calls functions based on user input
	while (1) {
	
    userInput = (char *) calloc(BUF, 1);

    write(1, "minix ",7);
    read(0, userInput, BUF);

    //use string compare to
    if(strstr(userInput, "minimount")!= NULL){
      //call minimount function
      
	image = (char *)calloc(265,1);

	strncpy(image, strstr(userInput, "minimount")+10, strlen(strstr(userInput, "minimount") +11));

	if(access(image, F_OK) != -1){
		mounted =1;
		char *mountedMessage = "Disk has been successfully mounted.\n";

		write(1, mountedMessage, strlen(mountedMessage));
	}

	else {
		char *mountedMessage = "Sorry, the file does not exist at the location.\n";

		write(1, mountedMessage, strlen(mountedMessage));
  	}
    }

    else if (strstr(userInput, "miniumount\n")){
  
	char *unmountMessage;
	if(mounted == 0){
		unmountMessage = "Disk has already been unmounted.\n";
		write(1, unmountMessage, strlen(unmountMessage));
	}
  	else{
    		free(image);
    		unmountMessage = "Disk has been unmounted.\n";
   		write(1, unmountMessage, strlen(unmountMessage));
  	}
    
    }

    else if(strstr(userInput, "showsuper\n")!= NULL){
        //call showsuper function
        //showsuper();
    }
    else if(strstr(userInput, "traverse\n") != NULL){
      //call traverse function
      //traverse(0);

    }
    else if(strstr(userInput, "traverse -l\n") != NULL){
      //call traverse -1
      //traverse(1);
    }

    else if (strstr(userInput, "showzone") != NULL){
      //call showzone function
      //showzone();
    }
    else if(strstr(userInput, "quit") != NULL){
      //call quit function
      if( userInput != NULL){
  		free(userInput);
  		userInput = NULL;
      }
      quit();
      return 0;
    }
    else if(strcmp(userInput, "help\n") ==0){
      //call help function
      help();
    }
    else{
      char *message = "Sorry, that is an invalid command. Type help to see a list of commands. \n";
      write(1, message, strlen(message));
    }

    free(userInput);
    userInput=NULL;
  }


	free(intro);

	return 0;
}

