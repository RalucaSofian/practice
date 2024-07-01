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
#include <stdlib.h>

#include "logger.h"
#include "event_system.h"

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

/*! @brief Internal data type for the structure of all event handlers
 *         to be stored in the handlers list
 */
typedef struct _EVSYS_event_handler_node
{
    EVSYS_internal_evt_handler        evt_handler;
    struct _EVSYS_event_handler_node* next_node;
}EVSYS_event_handler_node;

/************************************************************************
* GLOBAL VARIABLES
************************************************************************/
EVSYS_event_handler_node* list_head = NULL; // Handlers List head
int last_handler_id = 0; // Last Handler ID

/************************************************************************
* FUNCTION DEFINITIONS
************************************************************************/

/*! @brief Internal function used for determining the type of event handler,
 *         generating the handler ID and storing them
 * @param[in] handler - pointer to the event handler node
 * @return ID of the event handler
 */
static int register_event_handler(EVSYS_event_handler_node* handler)
{
    last_handler_id = last_handler_id + 1; // generate next ID

    if (NULL == list_head) // if list is empty
    {
        handler->evt_handler.handler_id = last_handler_id;
        handler->next_node = NULL;
        list_head = handler; // node to add becomes the head
    }
    else
    {
        EVSYS_event_handler_node* crt_node = list_head; // starting from list head
        while (NULL != crt_node->next_node) // while we have not reached the end of the list
        {
            crt_node = crt_node->next_node; // go to next list node
        }

        handler->evt_handler.handler_id = last_handler_id;
        handler->next_node = NULL;
        crt_node->next_node = handler;
    }

    switch (handler->evt_handler.event_type)
    {
        case EVT_KEYBOARD:
            LOGG_verbose("KB event handler address: 0x%x", handler->evt_handler.event_handler);
            break;
        case EVT_MOUSE_BTN:
            LOGG_verbose("Mouse btn event handler address: 0x%x", handler->evt_handler.event_handler);
            break;
        case EVT_MOUSE_MOVE:
            LOGG_verbose("Mouse move event handler address: 0x%x", handler->evt_handler.event_handler);
            break;
        case EVT_QUIT:
            LOGG_verbose("Quit event handler address: 0x%x", handler->evt_handler.event_handler);
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
    EVSYS_event_handler_node* crt_node = list_head; // starting from list head
    while (NULL != crt_node)
    {
        if (event.event_type == crt_node->evt_handler.event_type)
        {
            switch (event.event_type)
            {
                case EVT_KEYBOARD:
                {
                    EVSYS_kb_event*     out_event   = (EVSYS_kb_event*)(event.event_data);
                    EVSYS_kb_ev_handler out_handler = crt_node->evt_handler.event_handler;
                    out_handler(out_event);
                    break;
                }
                case EVT_MOUSE_BTN:
                {
                    EVSYS_mouse_btn_event*     out_event   = (EVSYS_mouse_btn_event*)(event.event_data);
                    EVSYS_mouse_btn_ev_handler out_handler = crt_node->evt_handler.event_handler;
                    out_handler(out_event);
                    break;
                }
                case EVT_MOUSE_MOVE:
                {
                    EVSYS_mouse_move_event*     out_event   = (EVSYS_mouse_move_event*)(event.event_data);
                    EVSYS_mouse_move_ev_handler out_handler = crt_node->evt_handler.event_handler;
                    out_handler(out_event);
                    break;
                }
                case EVT_QUIT:
                {
                    EVSYS_quit_ev_handler out_handler = crt_node->evt_handler.event_handler;
                    out_handler();
                    break;
                }
                default:
                    break;
            }
        }
        crt_node = crt_node->next_node; // go to next list node
    }
}


/************************************************************************
************************************************************************/

void EVSYS_Init(void)
{

}

int EVSYS_SubscribeKbEvent(EVSYS_kb_ev_handler event_handler)
{
    EVSYS_event_handler_node* kb_ev_handler = NULL;

    // Prepare internal handler
    kb_ev_handler = (EVSYS_event_handler_node*)malloc(sizeof(EVSYS_event_handler_node));
    kb_ev_handler->evt_handler.event_type    = EVT_KEYBOARD;
    kb_ev_handler->evt_handler.event_handler = event_handler;

    // Register handler and return ID to user (insert node at list start)
    int handler_id = register_event_handler(kb_ev_handler);

    return handler_id;
}

int EVSYS_SubscribeMouseBtnEvent(EVSYS_mouse_btn_ev_handler event_handler)
{
    EVSYS_event_handler_node* mouse_ev_handler = NULL;

    // Prepare internal handler
    mouse_ev_handler = (EVSYS_event_handler_node*)malloc(sizeof(EVSYS_event_handler_node));
    mouse_ev_handler->evt_handler.event_type    = EVT_MOUSE_BTN;
    mouse_ev_handler->evt_handler.event_handler = event_handler;

    // Register handler and return ID to user
    int handler_id = register_event_handler(mouse_ev_handler);

    return handler_id;
}

int EVSYS_SubscribeMouseMoveEvent(EVSYS_mouse_move_ev_handler event_handler)
{
    EVSYS_event_handler_node* mouse_move_handler = NULL;

    // Prepare internal handler
    mouse_move_handler = (EVSYS_event_handler_node*)malloc(sizeof(EVSYS_event_handler_node));
    mouse_move_handler->evt_handler.event_type    = EVT_MOUSE_MOVE;
    mouse_move_handler->evt_handler.event_handler = event_handler;

    // Register handler and return ID to user
    int handler_id = register_event_handler(mouse_move_handler);

    return handler_id;
}

int EVSYS_SubscribeQuitEvent(EVSYS_quit_ev_handler event_handler)
{
    EVSYS_event_handler_node* quit_ev_handler = NULL;

    // Prepare internal handler
    quit_ev_handler = (EVSYS_event_handler_node*)malloc(sizeof(EVSYS_event_handler_node));
    quit_ev_handler->evt_handler.event_type    = EVT_QUIT;
    quit_ev_handler->evt_handler.event_handler = event_handler;

    // Register handler and return ID to user
    int handler_id = register_event_handler(quit_ev_handler);

    return handler_id;
}

void EVSYS_UnsubscribeEvent(int event_handler_id)
{
    if (NULL == list_head)
    {
        LOGG_warn("Cannot unsubscribe event. Empty Event Handlers List");
        return;
    }

    // If we need to delete the list head
    if (event_handler_id == list_head->evt_handler.handler_id)
    {
        EVSYS_event_handler_node* new_head = list_head->next_node;
        free(list_head);
        list_head = new_head;
        LOGG_verbose("Unsubscribed handler ID %d", event_handler_id);
        return;
    }

    EVSYS_event_handler_node* crt_node = list_head; // starting from list head
    while (NULL != crt_node)
    {
        // If the next node is the one to delete
        if ((NULL != crt_node->next_node) && (event_handler_id == crt_node->next_node->evt_handler.handler_id))
        {
            // Skip over next node
            EVSYS_event_handler_node* node_to_delete = crt_node->next_node;
            crt_node->next_node = crt_node->next_node->next_node;
            free(node_to_delete);
            LOGG_verbose("Unsubscribed handler ID %d", event_handler_id);
            break;
        }
        crt_node = crt_node->next_node; // go to next list node
    }
}

void EVSYS_DispatchKbEvent(EVSYS_kb_event kb_event)
{
    EVSYS_internal_event tmp_event = {0};

    // Prepare internal event
    tmp_event.event_type = EVT_KEYBOARD;
    tmp_event.event_data = &kb_event;

    dispatch_event(tmp_event);
}

void EVSYS_DispatchMouseBtnEvent(EVSYS_mouse_btn_event mouse_btn_event)
{
    EVSYS_internal_event tmp_event = {0};

    // Prepare internal event
    tmp_event.event_type = EVT_MOUSE_BTN;
    tmp_event.event_data = &mouse_btn_event;

    dispatch_event(tmp_event);
}

void EVSYS_DispatchMouseMoveEvent(EVSYS_mouse_move_event mouse_move_event)
{
    EVSYS_internal_event tmp_event = {0};

    // Prepare internal event
    tmp_event.event_type = EVT_MOUSE_MOVE;
    tmp_event.event_data = &mouse_move_event;

    dispatch_event(tmp_event);
}

void EVSYS_DispatchQuitEvent(void)
{
    EVSYS_internal_event tmp_event = {0};

    // Prepare internal event
    tmp_event.event_type = EVT_QUIT;

    dispatch_event(tmp_event);
}
