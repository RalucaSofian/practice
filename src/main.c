/*! @file main.c
 *
 *
 *
 *
 *
 */

/************************************************************************
* INCLUDES
************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#include "logger.h"
#include "platform.h"
#include "event_system.h"
#include "input_system.h"
#include "game_controller.h"
#include "renderer.h"

/************************************************************************
* DEFINES
************************************************************************/
#define DEFAULT_WIN_NAME    "Window One"
#define DEFAULT_WIN_WIDTH   640
#define DEFAULT_WIN_HEIGHT  480

/************************************************************************
* FUNCTION DEFINITIONS
************************************************************************/

int main(int argc, char* argv[])
{
    char* win_title  = NULL;
    int   win_width  = 0;
    int   win_height = 0;
    char* end_ptr    = NULL; // to be used by strtol func

    LOGG_info("EVT Sys Init");
    EVSYS_Init();
    LOGG_info("EVT Sys Init -- Done");

    LOGG_info("Input Sys Init");
    INSYS_Init();
    LOGG_info("Input Sys Init -- Done");

    LOGG_info("Game Controller Init");
    GAMECTRL_Init();
    LOGG_info("Game Controller Init -- Done");

    LOGG_info("Platform Init");
    PLATF_Init();
    LOGG_info("Platform Init -- Done");

    if (1 == argc) // default == no args
    {
        LOGG_verbose("Window with default options");
        win_title  = DEFAULT_WIN_NAME;
        win_width  = DEFAULT_WIN_WIDTH;
        win_height = DEFAULT_WIN_HEIGHT;
    }
    else if (2 == argc) // only title + default dimensions
    {
        LOGG_verbose("Window with custom title");
        win_title  = argv[1];
        win_width  = DEFAULT_WIN_WIDTH;
        win_height = DEFAULT_WIN_HEIGHT;
    }
    else if (3 == argc) // error: title + 1 dimension
    {
        LOGG_err("Unexpected number of arguments");
        return 1;
    }
    else if (4 == argc) // custom == title + 2 dimensions
    {
        LOGG_verbose("Window with custom title and dimensions");
        win_title  = argv[1];
        win_width  = strtol(argv[2], &end_ptr, 10);
        win_height = strtol(argv[3], &end_ptr, 10);
    }
    else
    {
        LOGG_err("Unexpected number of arguments");
        return 1;
    }

    LOGG_info("Creating Window");
    if (0 != PLATF_CreateWindow(win_title, win_width, win_height))
    {
        LOGG_err("Error when creating window");
        return 1;
    }
    LOGG_info("Creating Window -- Done");

    LOGG_info("Renderer Init");
    REND_Init();
    LOGG_info("Renderer Init -- Done");

    LOGG_info("Setting up Platform");
    PLATF_glfw_hooks pltf_hooks = {0};
    pltf_hooks.update_hook = GAMECTRL_Update;
    pltf_hooks.render_hook = GAMECTRL_Render;
    LOGG_info("Setting up Platform -- Done");

    LOGG_info("Starting main loop");
    PLATF_MainLoop(pltf_hooks);

    LOGG_info("Exited main loop");


    LOGG_info("Platform De-init");
    PLATF_Deinit();
    LOGG_info("Platform De-init -- Done");

    LOGG_info("Game Controller De-init");
    GAMECTRL_Deinit();
    LOGG_info("Game Controller De-init -- Done");

    LOGG_info("Input Sys De-init");
    INSYS_Deinit();
    LOGG_info("Input Sys De-init -- Done");

    LOGG_info("Exiting");

    return 0;
}
