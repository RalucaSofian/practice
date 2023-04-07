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

#include "renderer.h"

/******************
* DEFINES
******************/
#define DEFAULT_WIN_NAME    "Window One"
#define DEFAULT_WIN_WIDTH   640
#define DEFAULT_WIN_HEIGHT  480


int main(int argc, char* argv[])
{   
    char* win_title  = NULL;
    int   win_width  = 0;
    int   win_height = 0;
    
    rend_init();

    if (1 == argc) /* default -> no args*/
    {
        printf("Window with default options \n");
        win_title  = DEFAULT_WIN_NAME;
        win_width  = DEFAULT_WIN_WIDTH;
        win_height = DEFAULT_WIN_HEIGHT;
    }
    else if (2 == argc) /* only title + default dimensions */
    {
        printf("Window with custom title \n");
        win_title  = argv[1];
        win_width  = DEFAULT_WIN_WIDTH;
        win_height = DEFAULT_WIN_HEIGHT;
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
    }
    else
    {
        printf("Error: unexpected number of arguments \n");
        return 1;
    }

    if (0 != rend_create_window(win_title, win_width, win_height))
    {
        printf("Error when creating window \n");
        return 1;
    }

    rend_window_render();

    rend_deinit();

    printf("End of main \n");

    return 0;
}
