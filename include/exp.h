#ifndef _EXP_H_
#define _EXP_H_

#include "../include/data.h"
#include "../include/randomize.h"
#include "main.h"

#define PERC_OFF 0
#define PERC_ON 1

#define Usr struct experiment_user
Usr {
        UsrData data;
        
        Usr * next;
};

#define Grp struct experiment_group
Grp {
        ExpGroup data;
        unsigned int users_c;
        long long money;
        Usr * users;
        
        Grp * next;
};

#define Exp struct experiment
Exp {
        ExpData data;
        ExpGroup * groups;
        Usr * free_users;
        Usr * not_reg_users;
        
        int data_experiment;
        int data_users;
        unsigned long long exp_days;
};

int load_experiment(StartData * data);
int new_experiment(StartData * data);

#endif