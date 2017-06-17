#include "../include/data.h"

void get_StartData(int argv, char ** args, StartData * sdata)
{
        switch(argv){
                case 4:
                        /*
                                -con id -days n
                        */
                        if(strcmp("-con", args[1]) == 0 && strcmp("-days", args[3])){
                                sscanf(args[2], "%u", &sdata->con_id);
                                sscanf(args[4], "%u", &sdata->days);
                                
                                sdata->cmd = C_CON;
                        }
                        break;
                case 5:
                        /*
                                -new -users n -days n
                        */
                        if(strcmp("-new", args[1]) == 0 && strcmp("-users", args[2]) && strcmp("-days", args[4])){
                                sscanf(args[3], "%u", &sdata->users);
                                sscanf(args[5], "%u", &sdata->days);
                                
                                sdata->cmd = C_NEW;
                        }
                        break;
                case 6:
                        /*
                                -con id -users n -days n
                        */
                        if(strcmp("-con", args[1]) == 0 && strcmp("-users", args[3]) && strcmp("-days", args[5])){
                                sscanf(args[2], "%u", &sdata->con_id);
                                sscanf(args[4], "%u", &sdata->users);
                                sscanf(args[6], "%u", &sdata->days);
                                
                                sdata->cmd = C_CON;
                        }
                        break;
                default:
                        goto need_arg;
        }

        return;

        need_arg:
        sdata->cmd = 0;
        printf("Need arguments: <-new | -con id> <-users n> <-days n>\n");
}

void print_ExpData(FILE * stream, ExpData * data)
{
        if(data == NULL || stream == NULL)
                return;
        
        fprintf(stream, 
                "Experiment"
                "\nID\t%u"
                "\nDAYS\t%llu"
                "\nUSERS\t%llu"
                "\nMONEY\tlld"
                "\nREG_INTENS\t%u"
                "\nGROUPS\t%u", data->id, data->days, data->users, data->money, data->register_intens, data->groups);
}

void save_ExpData(int fd, ExpData * data)
{
        if(data == NULL)
                return;
        write(fd, data, sizeof(ExpData));
}

void load_ExpData(int fd, ExpData * data)
{
        if(data == NULL)
                return;
        read(fd, data, sizeof(ExpData));
}

void print_ExpData(FILE * stream, ExpData * data)
{
        if(data == NULL || stream == NULL)
                return;
        
        fprintf(stream, 
                "Experiment"
                "\nID\t%u"
                "\nDAYS\t%llu"
                "\nUSERS\t%llu"
                "\nMONEY\tlld"
                "\nREG_INTENS\t%u"
                "\nGROUPS\t%u", data->id, data->days, data->users, data->money, data->register_intens, data->groups);
}

ssize_t save_ExpData(int fd, ExpData * data)
{
        if(data == NULL)
                return -1;
        return write(fd, data, sizeof(ExpData));
}

ssize_t load_ExpData(int fd, ExpData * data)
{
        if(data == NULL)
                return -1;
        return read(fd, data, sizeof(ExpData));
}

void print_UsrData(FILE * stream, UsrData * data)
{
        if(data == NULL || stream == NULL)
                return;
        fprintf(stream, 
                "Client"
                "\nID\t%u"
                "\nDAYS\t%llu"
                "\nW_EXCHANGES\t%llu"
                "\nL_EXCHANGES\tllu"
                "\nEXCHANGES\t%llu"
                "\nPERCENT\t%lf"
                "\nP_MONEY\t%lld"
                "\nM_MONEY\t%lld", data->id, data->reg_days, data->w_exchanges, data->l_exchanges, data->exchanges, data->percent, data->pmoney, data->mmoney);
}

ssize_t save_UsrData(int fd, UsrData * data)
{
        if(data == NULL)
                return -1;
        return write(fd, data, sizeof(UsrData));
}

ssize_t load_UsrData(int fd, UsrData * data)
{
        if(data == NULL)
                return -1;
        return read(fd, data, sizeof(UsrData));
}

ssize_t save_ExpGroup(int fd, ExpGroup * data)
{
        if(data == NULL)
                return -1;
        return write(fd, data, sizeof(ExpGroup));
}

ssize_t load_ExpGroup(int fd, ExpGroup * data)
{
        if(data == NULL)
                return -1;
        return read(fd, data, sizeof(ExpGroup));
}