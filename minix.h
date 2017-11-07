
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
#include <dirent.h>

#define DAYS_PER_4YEARS 1461

#define SECONDS_PER_DAY 86400



//define global variables

extern char* image;
extern int mounted;

//declare structures

typedef struct minix_super_block {
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
} minix_super_block;

typedef struct minix_inode
{
	unsigned short i_mode;
	unsigned short i_uid;
	unsigned int i_size;
	unsigned int i_time;
	unsigned char i_gid;
	unsigned char i_nlinks;
	unsigned short i_zone[9];
} minix_inode;

typedef struct minix_dir_entry
{
	unsigned short inode; 
	char name[0]; 		
} minix_dir_entry;

void help();
void showsuper();
void traverse(int fd, int detailPrint);
void showzone(int fd, int zone);
void showfile(char* fileName);
void quit();

//helper functions
char * itoa(char *s, int x);

/*
//helper functions 
void processImode(int a, char* returnString);
void processPermissionBytes(char* permissionBytes, char* returnString);
void convertTime(int seconds, char* returnString);
void hexDump (void *addr, int len);
void dtoh(char* returnString, int d);
char* strrev(char *str);
char* negateHex(char* hex);
*/
#endif

