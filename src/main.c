
/**********************************************************************
 *
 * TileLess
 *
 * TileLess is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * TileLess is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with TileLess.  If not, see <http://www.gnu.org/licenses/>.
 *
 **********************************************************************
 *
 * Copyright (C) 2016-2017 Nicklas Avén
 *
 **********************************************************************/


#include "tilelessmap.h"
#include <string.h>



static int button_test(void *ctrl, void *val, tileless_event_func_in_func func_in_func)
{
    log_this(100, "Yes, it works, getting text %s\n", (char*) val);
    return 0;
    
}

int main(int argc, char **argv)
{

    char *projectfile=NULL, *dir=NULL;


    while(--argc>0)
    {
        argv++;
        if(!strcmp(*argv,"-f") || !strcmp(*argv,"--projfile"))
        {
            argc--;
            if(argc > 0)
                projectfile=*++argv;
            else
            {
                log_this(110, "Too few arguments \n");
                return 1;
            }
            continue;
        }

        if(!strcmp(*argv,"-d") || !strcmp(*argv,"--directory"))
        {
            argc--;
            if(argc > 0)
                dir=*++argv;
            else
            {
                log_this(110, "Too few arguments \n");
                return 1;
            }

            continue;
        }
    }

    if (!(projectfile))
    {
        log_this(110, "Too few arguments \n");
        return 1;
    }


    
    TLM_init(projectfile, dir);
    
    CTRL* controls = TLM_init_controls(NATIVE_default);
    
    short box[4] = {500,500,600,600};
    float color[] = {255,0,0,255};
    short margins[2] = {50,40};
    
    add_button(controls, controls,box ,"Test", button_test,"rundgång", color,80,margins,1);
    
    
    TLM_start(controls);
    
    TLM_close();

    
    
    return EXIT_SUCCESS;
}
