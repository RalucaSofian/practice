/* @file main.c
*
*
*
*
*
*/

/************************************************
* INCLUDES
************************************************/
#include <stdio.h>
#include <stdlib.h>

#include "logger.h"
#include "platform.h"
#include "event_system.h"
#include "input_system.h"
#include "game_controller.h"

/************************************************
* DEFINES
************************************************/
#define DEFAULT_WIN_NAME    "Window One"
#define DEFAULT_WIN_WIDTH   640
#define DEFAULT_WIN_HEIGHT  480

/************************************************
* FUNCTION DEFINITIONS
************************************************/

int main(int argc, char* argv[])
{
    char* win_title  = NULL;
    int   win_width  = 0;
    int   win_height = 0;
    char* end_ptr    = NULL; /* to be used by strtol func*/

    logg_info("ES Init");
    es_init();
    logg_info("ES Init - Done");

    logg_info("Input Sys Init");
    input_sys_init();
    logg_info("Input Sys Init - Done");

    logg_info("Game Controller Init");
    game_ctrl_init();
    logg_info("Game Controller Init - Done");

    logg_info("Platform Init");
    platform_init();
    logg_info("Platform Init - Done");

    if (1 == argc) /* default -> no args*/
    {
        logg_verbose("Window with default options");
        win_title  = DEFAULT_WIN_NAME;
        win_width  = DEFAULT_WIN_WIDTH;
        win_height = DEFAULT_WIN_HEIGHT;
    }
    else if (2 == argc) /* only title + default dimensions */
    {
        logg_verbose("Window with custom title");
        win_title  = argv[1];
        win_width  = DEFAULT_WIN_WIDTH;
        win_height = DEFAULT_WIN_HEIGHT;
    }
    else if (3 == argc) /* error -> title + 1 dimension*/
    {
        logg_err("Unexpected number of arguments");
        return 1;
    }
    else if (4 == argc) /* custom -> title + 2 dimensions */
    {
        logg_verbose("Window with custom title and dimensions");
        win_title  = argv[1];
        win_width  = strtol(argv[2], &end_ptr, 10);
        win_height = strtol(argv[3], &end_ptr, 10);
    }
    else
    {
        logg_err("Unexpected number of arguments");
        return 1;
    }

    logg_info("Creating Window");
    if (0 != platform_create_window(win_title, win_width, win_height))
    {
        logg_err("Error when creating window");
        return 1;
    }
    logg_info("Creating Window - Done");

    logg_info("Setting up Platform");
    pltf_glfw_hooks pltf_hooks = {0};
    pltf_hooks.update_hook = game_ctrl_update;
    pltf_hooks.render_hook = game_ctrl_render;
    logg_info("Setting up Platform - Done");

    logg_info("Starting main loop");
    platform_main_loop(pltf_hooks);

    logg_info("Exited main loop");


    logg_info("Platform Deinit");
    platform_deinit();
    logg_info("Platform Deinit - Done");

    logg_info("Game Controller Deinit");
    game_ctrl_deinit();
    logg_info("Game Controller Deinit - Done");

    logg_info("Input Sys Deinit");
    input_sys_deinit();
    logg_info("Input Sys Deinit - Done");

    logg_info("Exiting");

    return 0;
}
