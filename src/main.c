/* @file main.c
*
*
*
*
*
*/

/******************
* INCLUDES
******************/
#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>

#include "renderer.h"

int main(int argc, char* argv[])
{   
    char* win_title  = NULL;
    int   win_width  = 0;
    int   win_height = 0;
    
    rend_init_glfw();

    if (1 == argc) /* default -> no args*/
    {
        printf("Window with default options \n");
        win_title  = "Window One";
        win_width  = 640;
        win_height = 480;
        if (0 != rend_create_window(win_title, win_width, win_height))
        {
            printf("Error when creating window \n");
            return 1;
        }
    }
    else if (2 == argc) /* only title + default dimensions */
    {
        printf("Window with custom title \n");
        win_title  = argv[1];
        win_width  = 640;
        win_height = 480;
        if (0 != rend_create_window(win_title, win_width, win_height))
        {
            printf("Error when creating window \n");
            return 1;
        }
    }
    else if (3 == argc) /* error -> title + 1 dimension*/
    {
        printf("Error: unexpected number of arguments \n");
        return 1;
    }
    else if (4 == argc) /* custom -> title + 2 dimensions */
    {
        printf("Window with custom title and dimensions \n");
        win_title  = argv[1];
        win_width  = atoi(argv[2]);
        win_height = atoi(argv[3]);
        if (0 != rend_create_window(win_title, win_width, win_height))
        {
            printf("Error when creating window \n");
            return 1;
        }
    }
    else
    {
        printf("Error: unexpected number of arguments \n");
        return 1;
    }

    rend_window_render();

    rend_deinit_glfw();

    printf("End of main \n");

    return 0;
}
