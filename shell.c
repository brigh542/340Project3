#include "shell.h"


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

void quit(){
	printf("Quitting minix shell...\n");
}

void showsuper(int fd){

	char *temp = (char *)calloc(1024, 1);
	
	lseek(fd, 1024, SEEK_SET);
	read(fd, temp, 1024);
	struct minix_super_block *superblock = (struct minix_super_block *) temp;

	char *inode ="number of inodes:\t";
	char *zones ="number of zones:\t";
	char *imapBlocks = "number of imap_blocks:\t";
	char *zmapBlocks = "number of zmap_blocks:\t";
	char *firstdatazone ="first data zone:\t";
	char *logzonesize= "log zone size:\t";
	char *maxsize = "max size:\t";
	char *magic ="magic:\t";
	char *state = "state:\t";
	char *szones = "zones:\t";

	char *message ="Must mount image file before executing.\n";

	printf("%s%d\n", inode, superblock->s_ninodes);
	printf("%s%d\n", zones, superblock->s_nzones);
	printf("%s%d\n", imapBlocks, superblock->s_imap_blocks);
	printf("%s%d\n", zmapBlocks, superblock->s_zmap_blocks);
	printf("%s%d\n", firstdatazone, superblock->s_firstdatazone);
	printf("%s%d\n", logzonesize, superblock->s_log_zone_size);
	printf("%s%d\n", maxsize, superblock->s_max_size);
	printf("%s%d\n", magic, superblock->s_magic);
	printf("%s%d\n", state, superblock->s_state);
	printf("%s%d\n", szones, superblock->s_zones);

}

void showzone(int fd, char *zone){
	char *temp = (char*) calloc(1024, 1);
	lseek(fd, 1024*atoi(zone), SEEK_SET);

	read(fd, temp, 1024);
	//hexDump(temp, 1024);
	
	
	struct minix_super_block super;
	//lseek(fd, 1024, SEEK_SET);
	//read(fd, superblock, sizeof(struct minix_super_block));
	printf("first zone value: %d\n", super.s_firstdatazone);
}



















void showfile(int fd, char *file){

	char *temp = (char *) calloc(32, 1);
	int inumber;
	
	int ifTrue=0;
	
	struct minix_dir_entry* directory;
	
	lseek(fd, 1024*5, SEEK_SET);
	read(fd, temp, 32);
	
	struct minix_inode *root = (struct minix_inode *) temp;
	
	free(temp);

	temp=(char *)calloc(16, 1);
	int x=0;
	
	while(x < 7){
		for(int y=0; y<1024; y=  y+16){
			if(root->i_zone[x] == '\0')
				break;
			else
				lseek(fd, (root->i_zone[x] *1024)+y, SEEK_SET);

			read(fd, temp, 16);

			if(strlen(temp) > 0) {

				directory = (struct minix_dir_entry *) temp;
				char* path = (char *)calloc(100,1);
				path = directory->name;

				if(strcmp(file, path) == 0){
					inumber=directory->inode;
					ifTrue=1;				
				}
			}
		}
		x++;
	}


	free(temp);
	temp=(char *)calloc(1024, 1);
	char *var = (char *) calloc(1,1);

	if( ifTrue ==1){
		lseek(fd, (1024*5) + ((inumber -1)*32), SEEK_SET);
		read(fd, temp, 32);
		
		struct minix_inode* inode = (struct minix_inode *) temp;
		
		int i=0;
		while(i<7){
			if(inode->i_zone[i] == '\0')
				break;

			lseek(fd, (inode->i_zone[i]*1024), SEEK_SET);
			for(int z=0; z<1024;z++){
				read(fd, var, 1);
				printf("%02x ", (unsigned int)(unsigned char) var[0]);

				if(((z+1)%16) == 0)
					printf("\n");
			}

			
			i++;
		}

	}else{
		printf("Sorry, the file does not exist.\n");
	}

	fflush(stdout);
	free(temp);
	temp=NULL;

} 




