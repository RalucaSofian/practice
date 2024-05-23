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
typedef struct _es_internal_event
{
    es_ev_type event_type;
    void*      event_data;
}_es_internal_event;

/*! @brief Internal function pointer type for the event handlers in the system
 */
typedef struct _es_internal_event_handler
{
    es_ev_type event_type;
    void*      event_handler;
    int        handler_id;
}_es_internal_event_handler;

/************************************************************************
* GLOBAL VARIABLES
************************************************************************/
_es_internal_event_handler all_handlers[MAX_NO_OF_HANDLERS];
int last_handler_id = 0;

/************************************************************************
* FUNCTION DEFINITIONS
************************************************************************/

/*! @brief Internal function used for determining the type of event handler,
 *         generating the handler ID and storing them
 * @param[in] evt_handler - pointer to the event handler function
 * @return ID of the event handler
 */
static int _register_event_handler(_es_internal_event_handler handler)
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
        else /* in case position is occupied */
        {
            if (MAX_NO_OF_HANDLERS - 1 == i) /* last position is occupied */
            {
                logg_err("Could not register event handler. Max number of registered handlers reached");
            }
        }
    }

    switch (handler.event_type)
    {
    case ES_KEYBOARD_EV:
        logg_verbose("KB event handler address: 0x%x", handler.event_handler);
        break;
    case ES_MOUSE_BTN_EV:
        logg_verbose("Mouse btn event handler address: 0x%x", handler.event_handler);
        break;
    case ES_MOUSE_MOVE_EV:
        logg_verbose("Mouse move event handler address: 0x%x", handler.event_handler);
        break;
    case ES_QUIT_EV:
        logg_verbose("Quit event handler address: 0x%x", handler.event_handler);
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
static void _dispatch_event(_es_internal_event event)
{
    for (int i = 0; i < MAX_NO_OF_HANDLERS; i++)
    {
        if ((NULL != all_handlers[i].event_handler) && (event.event_type == all_handlers[i].event_type))
        {
            switch (event.event_type)
            {
                case ES_KEYBOARD_EV:
                {
                    es_kb_event *out_event = (es_kb_event*)(event.event_data);
                    es_kb_ev_handler out_handler = all_handlers[i].event_handler;
                    out_handler(out_event);
                    break;
                }
                case ES_MOUSE_BTN_EV:
                {
                    es_mouse_btn_event *out_event = (es_mouse_btn_event*)(event.event_data);
                    es_mouse_btn_ev_handler out_handler = all_handlers[i].event_handler;
                    out_handler(out_event);
                    break;
                }
                case ES_MOUSE_MOVE_EV:
                {
                    es_mouse_move_event *out_event = (es_mouse_move_event*)(event.event_data);
                    es_mouse_move_ev_handler out_handler = all_handlers[i].event_handler;
                    out_handler(out_event);
                    break;
                }
                case ES_QUIT_EV:
                {
                    es_quit_ev_handler out_handler = all_handlers[i].event_handler;
                    out_handler();
                    break;
                }
                default:
                    break;
            }
        }
    }
}


void es_init(void)
{
    for (int i = 0; i < MAX_NO_OF_HANDLERS; i++)
    {
        all_handlers[i].event_handler = NULL;
    }
}

int es_subscribe_kb_event(es_kb_ev_handler event_handler)
{
    _es_internal_event_handler tmp_handler = {0};

    /* prepare internal handler */
    tmp_handler.event_type    = ES_KEYBOARD_EV;
    tmp_handler.event_handler = event_handler;

    /* register handler and return ID to user */
    int handler_id = _register_event_handler(tmp_handler);

    return handler_id;
}

int es_subscribe_mouse_btn_event(es_mouse_btn_ev_handler event_handler)
{
    _es_internal_event_handler tmp_handler = {0};

    /* prepare internal handler */
    tmp_handler.event_type    = ES_MOUSE_BTN_EV;
    tmp_handler.event_handler = event_handler;

    /* register handler and return ID to user */
    int handler_id = _register_event_handler(tmp_handler);

    return handler_id;
}

int es_subscribe_mouse_move_event(es_mouse_move_ev_handler event_handler)
{
    _es_internal_event_handler tmp_handler = {0};

    /* prepare internal handler */
    tmp_handler.event_type    = ES_MOUSE_MOVE_EV;
    tmp_handler.event_handler = event_handler;

    /* register handler and return ID to user */
    int handler_id = _register_event_handler(tmp_handler);

    return handler_id;
}

int es_subscribe_quit_event(es_quit_ev_handler event_handler)
{
    _es_internal_event_handler tmp_handler = {0};

    /* prepare internal handler */
    tmp_handler.event_type    = ES_QUIT_EV;
    tmp_handler.event_handler = event_handler;

    /* register handler and return ID to user */
    int handler_id = _register_event_handler(tmp_handler);

    return handler_id;
}

void es_unsubscribe_event(int event_handler_id)
{
    for (int i = 0; i < MAX_NO_OF_HANDLERS; i++)
    {
        if (event_handler_id == all_handlers[i].handler_id)
        {
            all_handlers[i].event_handler = NULL;
            logg_verbose("Unsubscribed handler ID %d", event_handler_id);
            break;
        }
    }
}

void es_dispatch_kb_event(es_kb_event kb_event)
{
    _es_internal_event tmp_event = {0};

    /* prepare internal event */
    tmp_event.event_type = ES_KEYBOARD_EV;
    tmp_event.event_data = &kb_event; // this will explode

    _dispatch_event(tmp_event);
}

void es_dispatch_mouse_btn_event(es_mouse_btn_event mouse_btn_event)
{
    _es_internal_event tmp_event = {0};

    /* prepare internal event */
    tmp_event.event_type = ES_MOUSE_BTN_EV;
    tmp_event.event_data = &mouse_btn_event; // this will explode

    _dispatch_event(tmp_event);
}

void es_dispatch_mouse_move_event(es_mouse_move_event mouse_move_event)
{
    _es_internal_event tmp_event = {0};

    /* prepare internal event */
    tmp_event.event_type = ES_MOUSE_MOVE_EV;
    tmp_event.event_data = &mouse_move_event; // this will explode

    _dispatch_event(tmp_event);
}

void es_dispatch_quit_event(void)
{
    _es_internal_event tmp_event = {0};

    /* prepare internal event */
    tmp_event.event_type = ES_QUIT_EV;

    _dispatch_event(tmp_event);
}
