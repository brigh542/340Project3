#include "shell.h"

void traverse(int fd, int flag){

	char* buffer = (char*)calloc(32,1);
	char* buffer2= (char*)calloc(32,1);

	struct minix_dir_entry* directory;

	lseek(fd, 1024*5, SEEK_SET);
	read(fd, buffer, 32);
	
	struct minix_inode *root=(struct minix_inode *)buffer;
	free(buffer);

	buffer=(char*)calloc(16,1);
	int x=0;
	int y=0;

	while(x<7){

		while(y<1024){

			if(root->i_zone[x] == '\0'){
				break;
			}else{
				lseek(fd, (root->i_zone[x]*1024)+y, SEEK_SET);
			}

			read(fd, buffer, 16);
			if(strlen(buffer)>0){

				directory = (struct minix_dir_entry *)buffer;
				if(strcmp(directory->name, ".") != 0  &&  strcmp(directory->name, ".") != 0){
					char* name= (char*)calloc(100,1);
					name=directory->name;

					if(flag ==1){

						int point = (1024*5) + (directory->inode-1)*32;
						lseek(fd, point, SEEK_SET);
						read(fd, buffer2, 32);
			
						struct minix_inode* inode= (struct minix_inode* )buffer2;

						char* print = (char *)calloc(100,1);
						char* var = (char *)calloc(8,1);
	
						process(inode->i_mode, print);


						strcat(print, " ");

						convert(var, inode->i_uid);
						strcat(print, var);
						strcat(print, " ");

						var = (char *)calloc(4,1);
						convert(var, inode->i_size);
						strcat(print, var);
						strcat(print, " ");

						var = (char *)calloc(12, 1);
						changeTime(inode->i_time, var);
						strcat(print, var);
						strcat(print, " ");
						strcat(print, name);
			

						write(1, print, strlen(print));

						write(1, "\n", 1);

						
					}else{
						write(1, name, strlen(name));
						write(1, "\n", 1);
					}
				}
			}

			y=y+16;
		}
		x++;
	}

	close(fd);

}


void convert(char *temp, int i){

	char *ex = temp;
	unsigned x = i;

	do{
		*ex++ = '0' + x%10;
		x /=10;

	}while(x);

	while(temp < --ex){
		char var = *temp;
		*temp++ = *ex;
		*ex = var;
	}
}



void process(int x, char * string){

	char* binary = (char *)calloc(17,1);
	char* permission=(char *)calloc(10,1);

	binary=binary +15;

	int y= 15;

	while(y>=0){
		*binary-- = (x&1) + '0';
		x >>=1;
	}

	binary +=1;
	permission = binary +7;

	if(binary[0] == '1')
		strcat(string, "-");
	else if(binary[1] == '1')
		strcat(string, "d");

	
	
	int n =0;
	int m=0;

	while(n<3){
		while(m<3){
			if((m == 0) && (permission[(n*3) +m] == '1'))
				strcat(string, "r");
			else if((m==1) && (permission[(n*3) + m] == '1'))
				strcat(string, "w");
			else if((m == 2) && (permission[(n*3) +m] == '1'))
				strcat(string, "x");
			else
				strcat(string, "-");
		}
	}
}


void dtoh(char *string, int x){
	int n = 0;
	if(x<0){
		x= -x;
		n = 1;
	}
	
	int m,i=0;

	char hex[]= "0123456789abcdef";

	//convert
	while(x != 0){
		m = x%16;
		*(string + i) = hex[m];
		x /= 16;
		i++;
	}

	*(string + i) = '\0';
	string = reverseString(string);

	if(n==1){
		//negatehex
		int count;
		char *returnString = (char *) calloc(strlen(string),1);

		char *hexes= "0123456789abcdef";

		for(count = 0; count<strlen(string) ; count++){
			char temp2 = *(string + count);

			int index= (int)(strchr(hexes, temp2) -hexes);

			if(index == 0)
				*(returnString + count) = '0';
			else
				*(returnString + count) = *(hexes + (16 - index));
		}

	}
}

char* reverseString(char *string){

	char *s1, *s2;

	if(!string || !*string){
		return string;
	}
		
	for(s1 = string, s2 = string+ strlen(string) -1; s2>s1; ++s1, --s2){

		*s1 ^= *s2;
		*s2 ^= *s1;
		*s1 ^= *s2;
	}
	
	return string;
}

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


void showzone(int fd, int number) {

  char *temp = (char *)calloc(1024, 1);

  lseek(fd, 1024*number, SEEK_SET);
  read(fd, temp, 1024);
 
  struct minix_super_block super;

  long address = (super.s_firstdatazone + number) * 1024;
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
  close(fd);

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
	close(fd);

} 

void changeTime(int seconds, char* string){

	int daysPassed = seconds/ SECONDS_PER_DAY;

	int yearsPassed= ((daysPassed / DAYS_PER_4YEARS) *4) + ((daysPassed % DAYS_PER_4YEARS) / 365);
	
	int year = 1970 + yearsPassed;

	int daysCurrentYear = ((daysPassed % DAYS_PER_4YEARS) % 365) +1;
	char *month = (char *) calloc(4, 1);
	char *temp = (char *)calloc(8,1);
	
	int leapyear =0;
	if(year % 4 == 0)
		leapyear = 1;

	int day = 0;

	if(daysCurrentYear <= 31){
		day = daysCurrentYear;
		month = "Jan";		
	}else if (daysCurrentYear <= 59 + leapyear){
		day = daysCurrentYear - 31;
		month = "Feb";
	}else if(daysCurrentYear <=90 +leapyear){
		day = daysCurrentYear - 59 - leapyear;
		month = "Mar";
	}else if(daysCurrentYear <= 120 +leapyear){
		day = daysCurrentYear - 90 - leapyear;
		month = "Apr";
	}else if(daysCurrentYear <= 151 + leapyear){
		day=daysCurrentYear - 120 - leapyear;
		month ="May";
	}else if(daysCurrentYear <= 181 + leapyear){
		day = daysCurrentYear -151 - leapyear;
		month = "Jun";
	}else if(daysCurrentYear <= 212 + leapyear){
		day = daysCurrentYear -181 - leapyear;
		month ="Jul";
	}else if(daysCurrentYear <= 243 + leapyear){
		day = daysCurrentYear - 212 - leapyear;
		month = "Aug";
	}else if(daysCurrentYear <= 273 + leapyear){
		day = daysCurrentYear - 243 - leapyear;
		month = "Sep";
	}else if(daysCurrentYear <= 304 +leapyear){
		day = daysCurrentYear - 273 - leapyear;
		month = "Oct";
	}else if(daysCurrentYear <= 334 + leapyear){
		day = daysCurrentYear - 304 - leapyear;
		month = "Nov";
	}else {
		day = daysCurrentYear - 334 - leapyear;
		month = "Dec";
	}


	strcat(string, month);
	strcat(string, " ");
	convert(temp, day);
	strcat(string, temp);
	strcat(string, " ");
	convert(temp, year);
	strcat(string, temp);
	strcat(string, " ");

}



















