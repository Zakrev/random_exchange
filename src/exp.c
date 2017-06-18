#include "../include/exp.h"

int new_experiment(StartData * data)
{
        /*
        создание эксперимента
        */
        Exp * exp;
        int fd_e, fd_u;
        char fname[256];
        
        /*
        создание файлов
        */
        sprintf(fname, "data/data_%u", data->id);
        
        fd_e = open(fname, O_CREAT | O_RDWR, 0666);
        if(fd == -1){
                PERR("open file %s", fname);
                perror("open file");
                
                return 1;
        }
        
        sprintf(fname, "data/users_%u", data->id);
        
        fd_u = open(fname, O_CREAT | O_RDWR, 0666);
        if(fd == -1){
                PERR("open file %s", fname);
                perror("open file");
                
                return 1;
        }
        
        exp = malloc(sizeof(Exp));
        if(exp == NULL)
                return 1;
        
        exp->data_experiment = fd_e;
        exp->data_users = fd_u;
        
        /*
        генерация и конфигурирование эксперимента
        */
        exp->data.users = data->users;
        exp->data.id = data->id;
        exp->data.days = 0;
        exp->data.money = 0;
        exp->data.register_intens = 5;
        exp->free_users = NULL;
        exp->not_reg_users = NULL;
        exp->groups = NULL;
        exp->exp_days = data->days;
        /*
        генерация и конфигурирование групп
        */
        push_group(&exp->groups, create_group(10, 1, PERC_ON));
        push_group(&exp->groups, create_group(500, 1, PERC_ON));
        push_group(&exp->groups, create_group(1000, 1, PERC_ON));
        push_group(&exp->groups, create_group(5000, 1, PERC_ON));
        push_group(&exp->groups, create_group(10000, 1, PERC_ON));
        push_group(&exp->groups, create_group(100000, 1, PERC_ON));
        push_group(&exp->groups, create_group(500000, 1, PERC_ON));
        push_group(&exp->groups, create_group(1000000, 1, PERC_ON));
        /*
        генерация и конфигурирование пользователей
        */
        
        
        return 0;
}

int load_experiment(StartData data)
{
        /*
        загрузка эксперимента
        */
        
        return 0;
}

void push_group(Grp ** groups, Grp * grp)
{
        if(grp == NULL)
                return;
        grp->next = *groups;
        *groups = grp;
}

void push_user(Usr ** users, Usr * usr)
{
        if(usr == NULL)
                return;
        usr->next = *users;
        *users = usr;
}

Usr * pop_user(Usr ** users)
{
        if(*users == NULL)
                return NULL;
        Usr * usr;
        usr = *users;
        *users = usr->next;
        
        return usr;
}

Grp * create_group(unsigned int size, unsigned int wusers, unsigned char percent_off)
{
        Grp * grp;
        
        grp = malloc(sizeof(Grp));
        if(grp == NULL)
                return NULL;
                
        grp->data.size = size;
        grp->data.wusers = wusers;
        grp->data.percent_off = percent_off;

        grp->users_c = 0;
        grp->money = 0;
        grp->users = NULL;
        grp->next = NULL;

        retuen grp;
}

Usr * create_user(unsigned long long reg_days, unsigned char insert_p, unsigned int min_group_size)
{
        Usr * usr;
        
        usr = malloc(sizeof(Usr));
        if(usr == NULL)
                return NULL;

        

        return usr;
}