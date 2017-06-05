#include "../include/main.h"
#include "../include/data.h"

int main(int argv, char ** args)
{
        StartData sdata;
        
        get_StartData(argv, args, &sdata);
        switch(sdata.cmd){
                case C_NEW:
                        break;
                case C_CON:
                        break;
                default:
                        return 1;
        }

        return 0;
}