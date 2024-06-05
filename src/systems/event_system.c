/*! @file event_system.c
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

/************************************************************************
* DEFINES
************************************************************************/
#define MAX_NO_OF_HANDLERS      5000

/************************************************************************
* INTERNAL DATA TYPES
************************************************************************/

/*! @brief Internal data type for the structure of all events in the system
 */
typedef struct _EVSYS_internal_event
{
    EVSYS_ev_type event_type;
    void*         event_data;
}EVSYS_internal_event;

/*! @brief Internal function pointer type for the event handlers in the system
 */
typedef struct _EVSYS_internal_evt_handler
{
    EVSYS_ev_type event_type;
    void*         event_handler;
    int           handler_id;
}EVSYS_internal_evt_handler;

/************************************************************************
* GLOBAL VARIABLES
************************************************************************/
EVSYS_internal_evt_handler all_handlers[MAX_NO_OF_HANDLERS];
int last_handler_id = 0;

/************************************************************************
* FUNCTION DEFINITIONS
************************************************************************/

/*! @brief Internal function used for determining the type of event handler,
 *         generating the handler ID and storing them
 * @param[in] evt_handler - pointer to the event handler function
 * @return ID of the event handler
 */
static int register_event_handler(EVSYS_internal_evt_handler handler)
{
    /* save handler internally */
    for (int i = 0; i < MAX_NO_OF_HANDLERS; i++)
    {
        if (NULL == all_handlers[i].event_handler)
        {
            all_handlers[i] = handler;
            last_handler_id = last_handler_id + 1; // generate next ID
            all_handlers[i].handler_id = last_handler_id;
            break;
        }
        else // in case position is occupied
        {
            if (MAX_NO_OF_HANDLERS-1 == i) // last position is occupied
            {
                LOGG_err("Could not register event handler. Max number of registered handlers reached");
            }
        }
    }

    switch (handler.event_type)
    {
        case EVT_KEYBOARD:
            LOGG_verbose("KB event handler address: 0x%x", handler.event_handler);
            break;
        case EVT_MOUSE_BTN:
            LOGG_verbose("Mouse btn event handler address: 0x%x", handler.event_handler);
            break;
        case EVT_MOUSE_MOVE:
            LOGG_verbose("Mouse move event handler address: 0x%x", handler.event_handler);
            break;
        case EVT_QUIT:
            LOGG_verbose("Quit event handler address: 0x%x", handler.event_handler);
            break;
        default:
            break;
    }

    return last_handler_id;
}

/*! @brief Internal function used for determining the type of event,
 *         and notifying the corresponding handlers
 * @param[in] event - event to be dispatched
*/
static void dispatch_event(EVSYS_internal_event event)
{
    for (int i = 0; i < MAX_NO_OF_HANDLERS; i++)
    {
        if ((NULL != all_handlers[i].event_handler) && (event.event_type == all_handlers[i].event_type))
        {
            switch (event.event_type)
            {
                case EVT_KEYBOARD:
                {
                    EVSYS_kb_event*     out_event   = (EVSYS_kb_event*)(event.event_data);
                    EVSYS_kb_ev_handler out_handler = all_handlers[i].event_handler;
                    out_handler(out_event);
                    break;
                }
                case EVT_MOUSE_BTN:
                {
                    EVSYS_mouse_btn_event*     out_event   = (EVSYS_mouse_btn_event*)(event.event_data);
                    EVSYS_mouse_btn_ev_handler out_handler = all_handlers[i].event_handler;
                    out_handler(out_event);
                    break;
                }
                case EVT_MOUSE_MOVE:
                {
                    EVSYS_mouse_move_event*     out_event   = (EVSYS_mouse_move_event*)(event.event_data);
                    EVSYS_mouse_move_ev_handler out_handler = all_handlers[i].event_handler;
                    out_handler(out_event);
                    break;
                }
                case EVT_QUIT:
                {
                    EVSYS_quit_ev_handler out_handler = all_handlers[i].event_handler;
                    out_handler();
                    break;
                }
                default:
                    break;
            }
        }
    }
}

/************************************************************************
************************************************************************/

void EVSYS_Init(void)
{
    for (int i = 0; i < MAX_NO_OF_HANDLERS; i++)
    {
        all_handlers[i].event_handler = NULL;
    }
}

int EVSYS_SubscribeKbEvent(EVSYS_kb_ev_handler event_handler)
{
    EVSYS_internal_evt_handler tmp_handler = {0};

    // Prepare internal handler
    tmp_handler.event_type    = EVT_KEYBOARD;
    tmp_handler.event_handler = event_handler;

    // Register handler and return ID to user
    int handler_id = register_event_handler(tmp_handler);

    return handler_id;
}

int EVSYS_SubscribeMouseBtnEvent(EVSYS_mouse_btn_ev_handler event_handler)
{
    EVSYS_internal_evt_handler tmp_handler = {0};

    // Prepare internal handler
    tmp_handler.event_type    = EVT_MOUSE_BTN;
    tmp_handler.event_handler = event_handler;

    // Register handler and return ID to user
    int handler_id = register_event_handler(tmp_handler);

    return handler_id;
}

int EVSYS_SubscribeMouseMoveEvent(EVSYS_mouse_move_ev_handler event_handler)
{
    EVSYS_internal_evt_handler tmp_handler = {0};

    // Prepare internal handler
    tmp_handler.event_type    = EVT_MOUSE_MOVE;
    tmp_handler.event_handler = event_handler;

    // Register handler and return ID to user
    int handler_id = register_event_handler(tmp_handler);

    return handler_id;
}

int EVSYS_SubscribeQuitEvent(EVSYS_quit_ev_handler event_handler)
{
    EVSYS_internal_evt_handler tmp_handler = {0};

    // Prepare internal handler
    tmp_handler.event_type    = EVT_QUIT;
    tmp_handler.event_handler = event_handler;

    // Register handler and return ID to user
    int handler_id = register_event_handler(tmp_handler);

    return handler_id;
}

void EVSYS_UnsubscribeEvent(int event_handler_id)
{
    for (int i = 0; i < MAX_NO_OF_HANDLERS; i++)
    {
        if (event_handler_id == all_handlers[i].handler_id)
        {
            all_handlers[i].event_handler = NULL;
            LOGG_verbose("Unsubscribed handler ID %d", event_handler_id);
            break;
        }
    }
}

void EVSYS_DispatchKbEvent(EVSYS_kb_event kb_event)
{
    EVSYS_internal_event tmp_event = {0};

    // Prepare internal event
    tmp_event.event_type = EVT_KEYBOARD;
    tmp_event.event_data = &kb_event; //! FIX: this will explode

    dispatch_event(tmp_event);
}

void EVSYS_DispatchMouseBtnEvent(EVSYS_mouse_btn_event mouse_btn_event)
{
    EVSYS_internal_event tmp_event = {0};

    // Prepare internal event
    tmp_event.event_type = EVT_MOUSE_BTN;
    tmp_event.event_data = &mouse_btn_event; //! FIX: this will explode

    dispatch_event(tmp_event);
}

void EVSYS_DispatchMouseMoveEvent(EVSYS_mouse_move_event mouse_move_event)
{
    EVSYS_internal_event tmp_event = {0};

    // Prepare internal event
    tmp_event.event_type = EVT_MOUSE_MOVE;
    tmp_event.event_data = &mouse_move_event; //! FIX: this will explode

    dispatch_event(tmp_event);
}

void EVSYS_DispatchQuitEvent(void)
{
    EVSYS_internal_event tmp_event = {0};

    // Prepare internal event
    tmp_event.event_type = EVT_QUIT;

    dispatch_event(tmp_event);
}
