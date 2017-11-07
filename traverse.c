#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include "shell.h"

// Calls from main:
// traverse(fd, 0) for short
// traverse(fd, 1) for -l flag
void getsuper(fd, struct minix_super_block *super){
	lseek(fd, 1024, SEEK_SET);
	read(fd, super, sizeof(struct minix_super_block));
}
void traverse(int fd, int flag) {
	struct minix_super_block super;
	getsuper(fd, &super);
	
	lseek(fd, 4*1024, SEEK_SET);
	struct minix_inode root;
	read(fd, &root, sizeof(struct minix_inode));
	
	long address = (root,i_zone[0] + super.s_firstdatazone) * 1024;
	lseek(fd, address, SEEK_SET);
	
	for(int firstAddress =0; firstAddress < 1024-16; firstAddress += 16){
		struct minix_dir_entry entry;
		read(fd, &entry, 16);
		
		if(strcmp(entry.name, "")){
			if(flag ==1){
				lseek(fd, (super.s_zmap_blocks +super.s_imap_blocks+2)*1024, SEEK_SET);
				lseek(fd, ((entry.inode-1)*32), SEEK_CUR);
				struct minix_inode node;
				read(fd, &node, 32);
				
				//print
				short mode = node.i_mode;
				short directoryMask = 0x4000;
				short mr1 = 0x0100;
				short mw1 = 0x0080;
				short mx1 = 0x0040;
                		short mr2 = 0x0020;
                		short mw2 = 0x0010;
                		short mx2 = 0x0008;
                		short mr3 = 0x0004;
                		short mw3 = 0x0002;
                		short mx3 = 0x0001;
				
				if((mode&directoryMask)>0){
					printf("d");
				}else{
					printf("-");
				}
				
				(mode&mr1)>0 ? printf("r") : printf("-");
                		(mode&mw1)>0 ? printf("w") : printf("-");
                		(mode&mx1)>0 ? printf("x") : printf("-");
                		(mode&mr1)>0 ? printf("r") : printf("-");
				(mode&mw2)>0 ? printf("w") : printf("-");
				(mode&mx2)>0 ? printf("x") : printf("-");
				(mode&mr3)>0 ? printf("r") : printf("-");
				(mode&mw3)>0 ? printf("w") : printf("-");
				(mode&mx3)>0 ? printf("x") : printf("-");
				
				printf(" %d ", node.i_uid);
                printf("%d ", node.i_size);
                if(node.i_size<1000 ) //helps with spacing
                {
                    printf(" ");
                }

                struct tm *info;
                info = localtime( &node.i_time );

                if(info->tm_mon==0) printf("Jan ");
                if(info->tm_mon==1) printf("Feb ");
                if(info->tm_mon==2) printf("Mar ");
                if(info->tm_mon==3) printf("Apr ");
                if(info->tm_mon==4) printf("May ");
                if(info->tm_mon==5) printf("Jun ");
                if(info->tm_mon==6) printf("Jul ");
                if(info->tm_mon==7) printf("Aug ");
                if(info->tm_mon==8) printf("Sep ");
                if(info->tm_mon==9) printf("Oct ");
                if(info->tm_mon==10) printf("Nov ");
                if(info->tm_mon==11) printf("Dec ");

                printf("%d ",info->tm_mday);

                
                printf("%d ",info->tm_year);

                lseek(fd,address+firstAddress+16,SEEK_SET);
            }

            for (int i = 0; i < 14; i++) {
                printf("%c", entry.name[i]);
            }
            printf("\n");
        }
    }
}
