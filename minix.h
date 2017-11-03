#ifndef MINIX_H_
#define MINIX_H_


//structure

struct super_block{
    unsigned short s_ninodes;
    unsigned short s_nzones;
    unsigned short s_imap_blocks;
    unsigned short s_zmap_blocks;
    unsigned short s_firstdatazone;
    unsigned short s_log_zone_size;
    unsigned int s_maxsize;
    unsigned short s_magic;
    unsigned short s_state;
    unsigned int s_zones;
};

struct inode{
  unsigned short i_mode;
  unsigned short i_uid;
  unsigned int i_size;
  unsigned int i_time;
  unsigned char i_gid;
  unsigned char i_nlinks;
  unsigned short i_zone[9];
};

struct dir_entry {
    unsigned short inode;
    char name[0];

};


void showsuper();
void help();
void quit();
void traverse(int fd, int detailPrint);
void showzone(int fd, int zone);
void minimount();
void miniumount();


#endif
