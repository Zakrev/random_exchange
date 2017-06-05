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
        long long wmoney;
        long long lmoney;
        unsigned long long exchanges;
        double percent;
        long long pmoney;
        long long mmoney;
        
        unsigned int insert;
        unsigned int min_group_size;
};

void get_StartData(int argv, char ** args, StartData * sdata);

#endif