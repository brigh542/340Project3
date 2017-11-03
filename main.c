#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
//#include <sys/types.h>
//#include <sys/stat.h>
#define BUF 10000

#include "minix.h"

char *image;


//indicates whether image is mounted
int mounted=0;

int main(){

  char *intro = "Welcome to MINIX.\n";

  write(1, intro, strlen(welcome)); //write welcome message, size

  //holds standard input
  char *userInput;

  //while (1) - indicates that no error or nothing written
  //calls functions based on user input
  while(1) {

    userInput = (char *)calloc(BUF, 1);

    write(1, "minix>>",7);
    read(0, userInput, BUF);

    //use string compare to
    if(strcmp(userInput, "minimount")!= NULL){
      //call minimount function

    }

    else if (strcmp(userInput, "miniumount")){
      //call miniumount function
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
      free(image);
      write(1, "Disk has been unmounted.\n", 24);

    }

    else if(strcmp(userInput, "showsuper\n")!= NULL){
        //call showsuper function
        showsuper();
    }
    else if(strcmp(userInput, "traverse\n") != NULL){
      //call traverse function
      traverse(0);

    }
    else if(strcmp(userInput, "traverse -l\n") != NULL){
      //call traverse -1
      traverse(1);
    }

    else if (strcmp(userInput, "showzone") != NULL){
      //call showzone function
    }
    else if(strcmp(userInput, "quit") != NULL){
      //call quit function
      quit();
      if( userInput != NULL){
        free(userInput);
        userInput = NULL;
      }
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
