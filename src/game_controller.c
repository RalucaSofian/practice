/*! @file game_controller.c
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

#include "logger.h"
#include "event_system.h"
#include "input_system.h"
#include "game_controller.h"

/************************************************************************
* GLOBAL VARIABLES
************************************************************************/
int kb_quit_handler_id; // handler ID for the KB Quit Event

/************************************************************************
* FUNCTION DEFINITIONS
************************************************************************/

/*! @brief Handler used for reacting to the ESC or CTRL+Q
 * keys being pressed
 */
static void kb_quit_handler(es_kb_event* kb_event)
{
    // QUIT == ESC or CTRL+Q was pressed
    switch (kb_event->key_state)
    {
        case ES_BUTTON_PRESSED:
        {
            if (KEY_ESCAPE == kb_event->key)
            {
                logg_info("ESC Pressed. Quitting");
                es_dispatch_quit_event();
            }
            else if (KEY_Q == kb_event->key)
            {
                if (ES_BUTTON_PRESSED == input_sys_get_key_state(KEY_LEFT_CONTROL))
                {
                    logg_info("CTRL+Q Pressed. Quitting");
                    es_dispatch_quit_event();
                }
            }
            break;
        }
        default:
            break;
    }
}


void game_ctrl_init(void)
{
    kb_quit_handler_id = es_subscribe_kb_event(kb_quit_handler);
}


void game_ctrl_update(double time_delta)
{
    logg_info("Game Ctrl update func; time delta = %f sec", time_delta);
}

void game_ctrl_render(void)
{

}

void game_ctrl_deinit(void)
{
    es_unsubscribe_event(kb_quit_handler_id);
}
