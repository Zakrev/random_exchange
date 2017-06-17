#ifndef _EXP_H_
#define _EXP_H_

#include "../include/data.h"

#include <stdlib.h>
#include <stdio.h>

#define Usr struct experiment_user
Usr {
        UsrData * data;
        
        Usr * next;
        Usr * prev;
};

#define Grp struct experiment_group
Grp {
        ExpGroup * data;
        unsigned int users;
        Usr * user;
        
        Grp * next;
        Grp * prev;
};

#define Exp struct experiment
Exp {
        ExpData data;
        ExpGroup * group;
        Usr * user;
        
        int data_experiment;
        int data_users;
};

#endif