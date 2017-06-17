#ifndef _DATA_H_
#define _DATA_H_

#include <stdlib.h>
#include <stdio.h>

#define C_NEW 1
#define C_CON 2

#define StartData struct start_data
StartData {
	unsigned int users;
	unsigned int days;
	unsigned char cmd;
	unsigned char con_id;	
};

#define ExpGroup struct group_data
ExpGroup {
        unsigned int size;
        unsigned int wusers;
        unsigned char percent_off;
};

#define ExpData struct experiment_data
ExpData {
        unsigned int id;
        unsigned long long days;
        unsigned long long users;
        long long money;
        
        unsigned int register_intens;
        
        unsigned int groups;
};

#define UsrData struct user_data
UsrData {
        unsigned int id;
        unsigned long long reg_days;
        unsigned long long w_exchanges;
        unsigned long long l_exchanges;
        unsigned long long exchanges;
        double percent;
        long long pmoney;
        long long mmoney;
        
        unsigned int insert_p;
        unsigned int min_group_size;
};

void get_StartData(int argv, char ** args, StartData * sdata);
void print_ExpData(FILE * stream, ExpData * data);
void save_ExpData(int fd, ExpData * data);
void load_ExpData(int fd, ExpData * data);
void print_ExpData(FILE * stream, ExpData * data);
ssize_t save_ExpData(int fd, ExpData * data);
ssize_t load_ExpData(int fd, ExpData * data);
void print_UsrData(FILE * stream, UsrData * data);
ssize_t save_UsrData(int fd, UsrData * data);
ssize_t load_UsrData(int fd, UsrData * data);
ssize_t save_ExpGroup(int fd, ExpGroup * data);
ssize_t load_ExpGroup(int fd, ExpGroup * data);
#endif