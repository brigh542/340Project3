#ifndef MINIX_H_
#define MINIX_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <time.h>

#define SECONDS_PER_DAY 86400
#define DAYS_PER_4YEARS 1461


extern char *image;
extern char *userInput;

struct minix_super_block {
	unsigned short s_ninodes;
	unsigned short s_nzones;
	unsigned short s_imap_blocks;
	unsigned short s_zmap_blocks;
	unsigned short s_firstdatazone;
	unsigned short s_log_zone_size;
	unsigned int s_max_size;
	unsigned short s_magic;
	unsigned short s_state;
	unsigned int s_zones;
};

struct minix_inode
{
	unsigned short i_mode;
	unsigned short i_uid;
	unsigned int i_size;
	unsigned int i_time;
	unsigned char i_gid;
	unsigned char i_nlinks;
	unsigned short i_zone[9];
};

struct minix_dir_entry
{
	unsigned short inode; 
	char name[0]; 		
};

//declare functions
void help();
void quit();
void showsuper(int fd);
void showzone(int fd, int number);
void showfile(int fd, char *file);
void traverse(int fd, int flag);
void changeTime(int seconds, char* string);
void dtoh(char *string, int x);
void process(int x, char * string);
void convert(char *temp, int i);
char* reverseString(char *string);

#endif
