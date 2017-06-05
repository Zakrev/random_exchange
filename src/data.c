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