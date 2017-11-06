#include"minix.h"

//declare showsuper function

void showsuper(){

  if(mounted ==1) {

    char *buffer = (char *)calloc(1024,1);

    int fd = open(image, O_RDONLY);

    lseek(fd, 1024, SEEK_SET);
   
    read(fd, buffer, 1024);

    struct super_block *super = (struct super_block *) buffer;

    char* temp=(char *) calloc(4,1);

    write(1, "number of inodes:  ",19);

    itoa(temp, super->s_ninodes);
    write(1, temp, 4);
    write(1, "\n",1);

    temp = (char *)calloc(4,1);

    write(1, "number of zones:  ",18);
    itoa(temp,super->s_nzones);

    write(1, temp,4);
    write(1, "\n",1);

    temp = (char *)calloc(4, 1);

    write(1, "number of imap_blocks:  ",24);
    itoa(temp, super->s_imap_blocks);
    write(1, temp, 4);
    write(1, "\n", 1);

    temp = (char *)calloc(4, 1);

    write(1, "number of zmap_blocks:  ", 24);
    itoa(temp, super->s_zmap_blocks);
    write(1, temp, 4);
    write(1, "\n",1);

    temp = (char *)calloc(4, 1);

    write(1, "first data zone:  ", 18);
    itoa(temp, super->s_firstdatazone);
    write(1, temp, 4);
    write(1, "\n", 1);

    temp = (char *)calloc(4, 1);

    write(1, "log zone size:  ", 24);
    itoa(temp, super->s_log_zone_size);
    write(1, temp, 4);
    write(1, "\n", 1);

    temp = (char *)calloc(4, 1);

    write(1, "max size: ", 19);
    itoa(temp, super->s_maxsize);
    write(1, temp, 4);
    write(1, "\n", 1);

    temp = (char *)calloc(4, 1);

    write(1, "magic:  ", 24);
    itoa(temp, super->s_magic);
    write(1, temp, 4);
    write(1, "\n", 1);

    temp = (char *)calloc(4, 1);

    write(1, "state:  ", 24);
    itoa(temp, super->s_state);
    write(1, temp, 4);
    write(1, "\n", 1);

    temp = (char *)calloc(4, 1);

    write(1, "zones:  ", 24);
    itoa(temp, super->s_zones);
    write(1, temp, 4);
    write(1, "\n", 1);

    close(fd);
  }
  //if not mounted
  else {
    char *message = "The minix image file is not mounted. Please mount and try again.";
    write(1, message, strlen(message));
  }
}
void traverse(int showMore) {
	if (mounted == 1) {

		char* buf = (char *) calloc(32, 1);
		char* buf2 = (char *) calloc(32, 1);

		struct minix_dir_entry* dir;
		int fd = open(image, O_RDONLY);

		lseek(fd, 1024 * 5, SEEK_SET); //set pointer to the first inode block (i.e 5th block, i.e root inode)
		read(fd, buf, 32); 		   //read root inode
		struct minix_inode* rootInode = (struct minix_inode *) buf;
		free(buf);

		buf = (char *) calloc(16, 1);
		int i, j;

		for (i = 0; i < 7; i++) { //loop through every zone
			for (j = 0; j < 1024; j = j + 16) { //loop through every two byte in each block
				if (rootInode->i_zone[i] == '\0')
					break;
				else
					lseek(fd, (rootInode->i_zone[i] * 1024) + j,
					SEEK_SET); //set pointer to the begining of data block

				read(fd, buf, 16);
				if (strlen(buf) > 0) {
					dir = (struct minix_dir_entry *) buf;
					if (strcmp(dir->name, ".") != 0
							&& strcmp(dir->name, "..") != 0) {

						char* name = (char *) calloc(100, 1);
						name = dir->name;

						if (showMore == 1) {
							int pointer = (1024 * 5)
									+ (dir->inode - 1) * 32;
							lseek(fd, pointer, SEEK_SET);
							read(fd, buf2, 32);
							struct minix_inode* inode =
									(struct minix_inode *) buf2;

							char* stringToPrint = (char *) calloc(100, 1);
							char* temp = (char *) calloc(8, 1);

							processImode(inode->i_mode, stringToPrint); //permission bytes and file type

							strcat(stringToPrint, " ");

							itoa(temp, inode->i_uid);
							strcat(stringToPrint, temp); //user id
							strcat(stringToPrint, " ");

							temp = (char *) calloc(4, 1);
							itoa(temp, inode->i_size);
							strcat(stringToPrint, temp); //file size
							strcat(stringToPrint, " ");

							temp = (char *) calloc(12, 1);
							convertTime(inode->i_time, temp);
							strcat(stringToPrint, temp);
							strcat(stringToPrint, " ");
							strcat(stringToPrint, name);

							write(1, stringToPrint, strlen(stringToPrint));
							write(1, "\n", 1);
						} else {
							write(1, name, strlen(name));
							write(1, "\n", 1);
						}
					}
				}
			}
		}

		close(fd);
	} else
		write(1,
				"Please mount minix image file before executing this command.\n",
				61);
}
/*
void showzone(char* zoneNumber) {

	if (mounted == 1) {
		char* buf = (char *) calloc(1024, 1);

		int fd = open(imagePath, O_RDONLY);
		lseek(fd, 1024 * atoi(zoneNumber), SEEK_SET); //set pointer to the input zone block

		read(fd, buf, 1024);
		
		hexDump(buf, 1024);
	} else
		write(1,
				"Please mount minix image file before executing this command.\n",
				61);
}

void showfile(char* fileName) {

	if (mounted == 1) {
		char* buf = (char *) calloc(32, 1);
		int inodeNum;
		int isFound = 0;

		struct minix_dir_entry* dir;
		int fd = open(imagePath, O_RDONLY);

		lseek(fd, 1024 * 5, SEEK_SET); //set pointer to the first inode block (i.e 5th block, i.e root inode)
		read(fd, buf, 32); 		   //read root inode
		struct minix_inode* rootInode = (struct minix_inode *) buf;

		free(buf);
		buf = (char *) calloc(16, 1);
		int i, j;

		for (i = 0; i < 7; i++) { //loop through every zone
			for (j = 0; j < 1024; j = j + 16) { //loop through every two byte in each block
				if (rootInode->i_zone[i] == '\0')
					break;
				else
					lseek(fd, (rootInode->i_zone[i] * 1024) + j,
					SEEK_SET); //set pointer to the begining of data block

				read(fd, buf, 16);
				if (strlen(buf) > 0) {
					dir = (struct minix_dir_entry *) buf;

					char* name = (char *) calloc(100, 1);
					name = dir->name;

					if (strcmp(fileName, name) == 0) {
						inodeNum = dir->inode;
						isFound = 1;
					}
				}
			}
		}

		free(buf);
		buf = (char *) calloc(1024, 1);
		char* buf2 = (char *) calloc(1, 1);

		if (isFound == 1) {
			lseek(fd, (1024 * 5) + ((inodeNum - 1) * 32), SEEK_SET); //set pointer to the first inode block (i.e 5th block, i.e root inode)
			read(fd, buf, 32); 		   //read inode
			struct minix_inode* inode = (struct minix_inode *) buf;

			for (i = 0; i < 7; i++) { //loop through every zone
				if (inode->i_zone[i] == '\0')
					break;

				lseek(fd, (inode->i_zone[i] * 1024), SEEK_SET); //set pointer to the begining of data block
				//read(fd, buf, 1024);

				for (j = 0; j < 1024; j++) { 
					read(fd, buf2, 1);
					printf("%02x ", (unsigned int) (unsigned char) buf2[0]);

					if (((j + 1) % 16) == 0)
						printf("\n");
				}
			}
		} else {
			printf("File does not exist\n");
		}

		fflush(stdout);
		free(buf);
		buf = NULL;
	} else
		write(1,
				"Please mount minix image file before executing this command.\n",
				61);

}

//helper functions

void processImode(int a, char* returnString) {

	char* binaryString = (char *) calloc(17, 1);
	char* permissionBytes = (char *) calloc(10, 1);

	binaryString = binaryString + 15;

	int i = 0;
	for (i = 15; i >= 0; i--) {
		*binaryString-- = (a & 1) + '0';

		a >>= 1;
	}
	binaryString += 1;
	permissionBytes = binaryString + 7;
	if (binaryString[0] == '1')
		strcat(returnString, "-"); //regular File
	else if (binaryString[1] == '1')
		strcat(returnString, "d"); //directory

	processPermissionBytes(permissionBytes, returnString);
}

void processPermissionBytes(char* permissionBytes, char* returnString) {
	int i, j = 0;

	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			if ((j == 0) && (permissionBytes[(i * 3) + j] == '1'))
				strcat(returnString, "r");
			else if ((j == 1) && (permissionBytes[(i * 3) + j] == '1'))
				strcat(returnString, "w");
			else if ((j == 2) && (permissionBytes[(i * 3) + j] == '1'))
				strcat(returnString, "x");
			else
				strcat(returnString, "-");
		}
	}
}

void convertTime(int seconds, char* returnString) {
	int elpasedDays = seconds / SECONDS_IN_A_DAY;
	int elpasedYears = ((elpasedDays / DAYS_IN_FOUR_YEARS) * 4)
			+ ((elpasedDays % DAYS_IN_FOUR_YEARS) / 365);
	int year = 1970 + elpasedYears;

	int daysInCurrentYear = ((elpasedDays % DAYS_IN_FOUR_YEARS) % 365) + 1;
	char* month = (char *) calloc(4, 1);
	char* temp = (char *) calloc(8, 1);

	int leap = 0;
	if (year % 4 == 0)
		leap = 1;

	int day = 0;
	if (daysInCurrentYear <= 31) {
		day = daysInCurrentYear;
		month = "Jan";
	} else if (daysInCurrentYear <= 59 + leap) {
		day = daysInCurrentYear - 31;
		month = "Feb";
	} else if (daysInCurrentYear <= 90 + leap) {
		day = daysInCurrentYear - 59 - leap;
		month = "Mar";
	} else if (daysInCurrentYear <= 120 + leap) {
		day = daysInCurrentYear - 90 - leap;
		month = "Apr";
	} else if (daysInCurrentYear <= 151 + leap) {
		day = daysInCurrentYear - 120 - leap;
		month = "May";
	} else if (daysInCurrentYear <= 181 + leap) {
		day = daysInCurrentYear - 151 - leap;
		month = "Jun";
	} else if (daysInCurrentYear <= 212 + leap) {
		day = daysInCurrentYear - 181 - leap;
		month = "Jul";
	} else if (daysInCurrentYear <= 243 + leap) {
		day = daysInCurrentYear - 212 - leap;
		month = "Aug";
	} else if (daysInCurrentYear <= 273 + leap) {
		day = daysInCurrentYear - 243 - leap;
		month = "Sep";
	} else if (daysInCurrentYear <= 304 + leap) {
		day = daysInCurrentYear - 273 - leap;
		month = "Oct";
	} else if (daysInCurrentYear <= 334 + leap) {
		day = daysInCurrentYear - 304 - leap;
		month = "Nov";
	} else {
		day = daysInCurrentYear - 334 - leap;
		month = "Dec";
	}
	strcat(returnString, month);
	strcat(returnString, " ");
	itoa(temp, day);
	strcat(returnString, temp);
	strcat(returnString, " ");
	itoa(temp, year);
	strcat(returnString, temp);
	strcat(returnString, " ");

}

void hexDump(void *addr, int len) {
	int i;
	char* temp = (char *) calloc(1, 1);
	char* c = (char *) calloc(1, 1);

	write(1, "    ", 4);

	for (i = 0; i < 10; i++) {
		itoa(temp, i);
		write(1, " ", 1);
		write(1, temp, 1);
		write(1, " ", 1);
	}

	for (*c = 'a'; *c != 'g'; (*c)++) {
		write(1, " ", 1);
		write(1, c, 1);
		write(1, " ", 1);
	}

	write(1, "\n", 1);
	write(1, " 0  ", 4);

	int h = 0x00;

	unsigned char *pc = (unsigned char*) addr;

	for (i = 0; i < len - 1; i++) {

		if (isprint(pc[i]) == 0) {
			write(1, " ", 1);
			write(1, " ", 1);
			write(1, " ", 1);
		} else {
			char* c = (char *) calloc(1, 1);
			*c = pc[i];
			write(1, " ", 1);
			write(1, c, 1);
			write(1, " ", 1);
		}

		temp = (char *) calloc(40, 1);

		if ((i != 0) && ((i + 1) % 16) == 0) {
			write(1, "\n", 1);

			h = h + 0x10;
			dtoh(temp, h);
			write(1, temp, strlen(temp));
			if (strlen(temp) == 2)
				write(1, "  ", 2);
			else
				write(1, " ", 1);
		}
	}

	write(1, "\n", 1);
}

void dtoh(char* returnString, int d) {

	int negate = 0;
	if (d < 0) {
		d = -d;
		negate = 1;
	}

	int r, i = 0;
	char hexDigits[] = "0123456789abcdef";

	// Convert Decimal Number to Hexadecimal Numbers 
	while (d != 0) {
		r = d % 16;
		*(returnString + i) = hexDigits[r];
		d /= 16;
		i++;
	}
	*(returnString + i) = '\0';
	returnString = strrev(returnString);

	if (negate == 1)
		returnString = negateHex(returnString);
}

void itoa(char *s, int x) {
	char *p = s;

	unsigned t = x;

	do {
		*p++ = '0' + t % 10;
		t /= 10;
	} while (t);

	while (s < --p) {
		char t = *s;
		*s++ = *p;
		*p = t;
	}
}

char* strrev(char* str) {
	char *p1, *p2;

	if (!str || !*str)
		return str;
	for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2) {
		*p1 ^= *p2;
		*p2 ^= *p1;
		*p1 ^= *p2;
	}
	return str;
}

char* negateHex(char* hex) {
	int i;
	char* returnString = (char *) calloc(strlen(hex), 1);

	char* hexs = "0123456789abcdef";

	for (i = 0; i < strlen(hex); i++) {
		char c = *(hex + i);
		int index = (int) (strchr(hexs, c) - hexs);

		if (index == 0)
			*(returnString + i) = '0';
		else
			*(returnString + i) = *(hexs + (16 - index));
	}

	return returnString;

}

*/

//construct help function
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


