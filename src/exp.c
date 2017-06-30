#include "../include/exp.h"

void register_users(Exp * exp)
{
        if(exp->not_reg_users == NULL)
                return;
        
        int i = exp->data.register_intens;
        Usr * usr;
        
        while(0 < i--){
                if(random_next_range(0, 1) == 1)
                        continue;
                usr = pop_user(&exp->not_reg_users);
                if(usr == NULL)
                        return;
                push_user(&exp->free_users, usr);
        }
}

void insert_users_to_groups(Exp * exp)
{
        if(exp->free_users == NULL)
                return;
        
        Usr * usr;
        Grp * grp;
        
        grp = exp->groups;
        while(grp != NULL){
                if(exp->free_users == NULL)
                        return;
                usr = exp->free_users;
                while(usr != NULL){
                        //if( exp->free_users->data.min_group_size < grp->data.size && (random_next_range(0, 100) < exp->free_users->data.insert_p) ){
                        if( random_next_range(0, 100) < exp->free_users->data.insert_p ){
                                usr = usr->next;
                                push_user(&grp->users, pop_user(&exp->free_users));
                        } else
                                usr = usr->next;
                }
                grp = grp->next;
        }
}

int new_experiment(StartData * data)
{
        /*Создание эксперимента*/
        Exp * exp;
        int fd_e, fd_u;
        char fname[256];
        Usr * usr;
        
        /*Создание файлов*/
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
        
        /*Генерация и конфигурирование эксперимента*/
        exp->data.users = data->users;
        exp->data.id = data->id;
        exp->data.days = 0;
        exp->data.money = 0;
        exp->data.register_intens = 5;
        exp->free_users = NULL;
        exp->not_reg_users = NULL;
        exp->groups = NULL;
        exp->exp_days = data->days;
        /*Генерация и конфигурирование групп*/
        push_group(&exp->groups, create_group(10, 1, PERC_ON));
        push_group(&exp->groups, create_group(500, 1, PERC_ON));
        push_group(&exp->groups, create_group(1000, 1, PERC_ON));
        push_group(&exp->groups, create_group(5000, 1, PERC_ON));
        push_group(&exp->groups, create_group(10000, 1, PERC_ON));
        push_group(&exp->groups, create_group(100000, 1, PERC_ON));
        push_group(&exp->groups, create_group(500000, 1, PERC_ON));
        push_group(&exp->groups, create_group(1000000, 1, PERC_ON));
        /*Генерация и конфигурирование новых пользователей*/
        while(data->users > 0){
                data->users -= 1;
                usr = create_user(exp->data.days, random_next_range(5, 100), random_next_range(0, 500000));
                if(usr == NULL){
                        PERR("create user");
                        return 1;
                }
                push_user(&exp->not_reg_users, usr);
        }
        
        return 0;
}

int load_experiment(StartData * data)
{
        /*Загрузка эксперимента*/
        Exp * exp;
        int fd_e, fd_u;
        char fname[256];
        ExpGroup grp_data_tmp;
        Grp * grp;
        UsrData usr_data_tmp;
        Usr * usr;
        
        /*Открытие файлов*/
        sprintf(fname, "data/data_%u", data->id);
        
        fd_e = open(fname, O_RDWR);
        if(fd == -1){
                PERR("open file %s", fname);
                perror("open file");
                
                return 1;
        }
        
        sprintf(fname, "data/users_%u", data->id);
        
        fd_u = open(fname, O_RDWR);
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
        
        /*Загрузка данных эксперимента*/
        if( 0 <= load_ExpData(exp->data_experiment, &exp->data)){
                PERR("load ExpData");
                return 1;
        }
        /*Загрузка данных групп*/
        while(load_ExpGroup(exp->data_experiment, &grp_data_tmp) > 0){
                grp = init_group();
                if(grp == NULL){
                        PERR("create group");
                        return 1;
                }
                memcpy(&grp->data, &grp_data_tmp, sizeof(ExpGroup));
                push_group(&exp->groups, grp);
        }
        /*Загрузка данных пользователей*/
        while(load_UsrData(exp->data_users, &usr_data_tmp) > 0){
                usr = init_user();
                if(usr == NULL){
                        PERR("create user");
                        return 1;
                }
                memcpy(&usr->data, &usr_data_tmp, sizeof(UsrData));
                push_usr(&exp->free_users, usr);
        }
        /*Генерация и конфигурирование новых пользователей*/
        while(data->users > 0){
                data->users -= 1;
                usr = create_user(exp->data.days, random_next_range(5, 100), random_next_range(0, 500000));
                if(usr == NULL){
                        PERR("create user");
                        return 1;
                }
                push_user(&exp->not_reg_users, usr);
        }
        
        return 0;
}

static void push_group(Grp ** groups, Grp * grp)
{
        if(grp == NULL)
                return;
        grp->next = *groups;
        *groups = grp;
}

static void push_user(Usr ** users, Usr * usr)
{
        if(usr == NULL)
                return;
        usr->next = *users;
        *users = usr;
}

static Usr * pop_user(Usr ** users)
{
        if(*users == NULL)
                return NULL;
        Usr * usr;
        usr = *users;
        *users = usr->next;
        usr->next = NULL;
        
        return usr;
}

static Grp * init_group()
{
	Grp * grp;
        
        grp = malloc(sizeof(Grp));
        if(grp == NULL)
                return NULL;
                
        grp->data.size = 0;
        grp->data.wusers = 0;
        grp->data.percent_off = 0;
        grp->users_c = 0;
        grp->money = 0;
        grp->users = NULL;
        grp->next = NULL;
        
        return grp;
}

static Grp * create_group(unsigned int size, unsigned int wusers, unsigned char percent_off)
{
        Grp * grp;
        
        grp = init_group();
        if(grp == NULL)
                return NULL;
                
        grp->data.size = size;
        grp->data.wusers = wusers;
        grp->data.percent_off = percent_off;

        retuen grp;
}

static Usr * init_user()
{
	Usr * usr;
        
        usr = malloc(sizeof(Usr));
        if(usr == NULL)
                return NULL;
                
        usr->next = NULL;
        usr->data.reg_days = 0;
        usr->data.insert_p = 0;
        usr->data.min_group_size = 0;
        usr->data.w_exchanges = 0;
        usr->data.l_exchanges = 0;
        usr->data.exchanges = 0;
        usr->data.percent = 0;
        usr->data.pmoney = 0;
        usr->data.mmoney = 0;
        
        return usr;
}

static Usr * create_user(unsigned long long reg_days, unsigned char insert_p, unsigned int min_group_size)
{
        Usr * usr;
        
        usr = init_user();
        if(usr == NULL)
                return NULL;

        usr->data.reg_days = reg_days;
        usr->data.insert_p = insert_p;
        usr->data.min_group_size = min_group_size;
        
        return usr;
}