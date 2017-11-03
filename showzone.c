#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "minix.h"


void showzone(int fd, int zone) {
 
  int zoneNum = zone;
  struct minix_super_block superBlock;
  getSuperBlock(fd,&superBlock);
  printf("first zone value: %d\n", superBlock.s_firstdatazone);
  long address = (superBlock.s_firstdatazone + zone) * 1024;
  lseek(fd, address, SEEK_SET);
  char buffer[1024];
  read(fd, buffer, 1024);
  int i = 0;
  int n;
  printf("\t 0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f\n0");
  while(i<1024){
    
    for(n = 0;n<16;n++){
      if(n == 0){
	printf("\t");
      }
      if (isprint(buffer[i])) {
	printf("%c ",buffer[i]);
      }
      else{
	printf(" ");
      }
      if(n==15){
	printf("\n%x",i+1);
      }
      i++;
    }
 
  }
  printf("\n");

     




}
