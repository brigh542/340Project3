#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "minix.h"

void showsuper(){

  if(mounted ==1) {

    char *buffer = (char *)calloc(BLOCK_SIZE,1);

    int fd = open(image, O_RDONLY);

    lseek(fd, 1024, SEEK_SET);
    //2nd block
    read(fd, buffer, BLOCK_SIZE);

    struct super_block *super = (struct super_block *) buffer;

    char* temp=(char *) calloc(4,1);

    write(1, "The number of I-nodes are:  ",19);

    itoa(temp, super->ninodes);
    write(1, temp, 4);
    write(1, "\n",1);

    temp = (char *)calloc(4,1);

    write(1, "The number of zones:  ",18);
    itoa(temp,super->nzones);

    write(1, temp,4);
    write(1, "\n",1);

    temp = (char *)calloc(4, 1);

    write(1, "The number of imap_blocks:  ",24);
    itoa(temp, super->imap_blocks);
    write(1, temp, 4);
    write(1, "\n", 1);

    temp = (char *)calloc(4, 1);

    write(1, "The number of zmap_blocks:  ", 24);
    itoa(temp, super->zmap_blocks);
    write(1, temp, 4);
    write(1, "\n",1);

    temp = (char *)calloc(4, 1);

    write(1, "The first data zone:  ", 18);
    itoa(temp, super->firstdatazone);
    write(1, temp, 4);
    write(1, "\n", 1);

    temp = (char *)calloc(4, 1);

    write(1, "The log zone size:  ", 24);
    itoa(temp, super->log_zone_size);
    write(1, temp, 4);
    write(1, "\n", 1);

    temp = (char *)calloc(4, 1);

    write(1, "The max size: ", 19);
    itoa(temp, super->max_size);
    write(1, temp, 4);
    write(1, "\n", 1);

    temp = (char *)calloc(4, 1);

    write(1, "Magic:  ", 24);
    itoa(temp, super->magic);
    write(1, temp, 4);
    write(1, "\n", 1);

    temp = (char *)calloc(4, 1);

    write(1, "State:  ", 24);
    itoa(temp, super->state);
    write(1, temp, 4);
    write(1, "\n", 1);

    temp = (char *)calloc(4, 1);

    write(1, "Zones:  ", 24);
    itoa(temp, super->zones);
    write(1, temp, 4);
    write(1, "\n", 1);

    close(fd);
  }
  else {//not mounted
    char *message = "The minix image file is not mounted. Please mount and try again.";
    write(1, message, strlen(message));
  }
}

void minimount(){
    image = (char *)calloc(265, 1);
    strncopy(image, strstr(userInput, "minimount")+10, strlen(strstr(userInput, "minimount"));

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




