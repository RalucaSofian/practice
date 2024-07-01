/*! @file event_system.h
 *
 *
 *
 *
 *
 */
#ifndef EVENT_SYSTEM_H
#define EVENT_SYSTEM_H

/************************************************************************
* INCLUDES
************************************************************************/
#include "input_types.h"

/************************************************************************
* DATA TYPES
************************************************************************/

/*! @brief Possible types of events to be handled by the system
 */
typedef enum _EVSYS_ev_type
{
    EVT_KEYBOARD = 0,
    EVT_MOUSE_BTN,
    EVT_MOUSE_MOVE,
    EVT_WINDOW_RESIZE,
    EVT_PAUSE,
    EVT_QUIT,
    EVT_LAST
}EVSYS_ev_type;

/*! @brief Structure of the keyboard events to be handled by the system
 */
typedef struct _EVSYS_kb_event
{
    INTYPES_key_state key_state;
    INTYPES_key_code  key;
}EVSYS_kb_event;

/*! @brief Structure of the mouse buttons events to be handled by the system
 */
typedef struct _EVSYS_mouse_btn_event
{
    INTYPES_key_state  button_state;
    INTYPES_mouse_btns button;
}EVSYS_mouse_btn_event;

/*! @brief Structure of the mouse move events to be handled by the system
 */
typedef struct _EVSYS_mouse_move_event
{
    float x_pos;
    float y_pos;
}EVSYS_mouse_move_event;


/*! @brief Function pointer type for keyboard event handlers
 */
typedef void (* EVSYS_kb_ev_handler)(EVSYS_kb_event* kb_event);

/*! @brief Function pointer type for mouse buttons event handlers
 */
typedef void (* EVSYS_mouse_btn_ev_handler)(EVSYS_mouse_btn_event* mouse_btn_event);

/*! @brief Function pointer type for mouse move event handlers
 */
typedef void (* EVSYS_mouse_move_ev_handler)(EVSYS_mouse_move_event* mouse_move_event);

/*! @brief Function pointer type for quit event handlers
 */
typedef void (* EVSYS_quit_ev_handler)(void);

/************************************************************************
* FUNCTION DECLARATIONS
************************************************************************/

/*! @brief Initialize the Event System
 */
void EVSYS_Init(void);

/*! @brief Subscribe to a keyboard event
 *  @param[out] event_handler - handler function for kb events
 *  @return ID of the subscribed event handler
 */
int EVSYS_SubscribeKbEvent(EVSYS_kb_ev_handler event_handler);

/*! @brief Subscribe to a mouse button event
 *  @param[out] event_handler - handler function for mouse button events
 *  @return ID of the subscribed event handler
 */
int EVSYS_SubscribeMouseBtnEvent(EVSYS_mouse_btn_ev_handler event_handler);

/*! @brief Subscribe to a mouse move event
 *  @param[out] event_handler - handler function for mouse move events
 *  @return ID of the subscribed event handler
 */
int EVSYS_SubscribeMouseMoveEvent(EVSYS_mouse_move_ev_handler event_handler);

// /*! @brief Subscribe to a window resize event
//  *  @param[out] event_handler - handler function for window resize events
//  *  @return ID of the subscribed event handler
// */
// int es_subscribe_window_resize_event(void* event_handler);

// /*! @brief Subscribe to a Pause event
//  *  @param[out] event_handler - handler function for Pause events
//  *  @return ID of the subscribed event handler
// */
// int es_subscribe_pause_event(void* event_handler);

/*! @brief Subscribe to a Quit event
 *  @param[out] event_handler - handler function for Quit events
 *  @return ID of the subscribed event handler
*/
int EVSYS_SubscribeQuitEvent(EVSYS_quit_ev_handler event_handler);

/*! @brief Unsubscribe from an event
 *  @param[in] event_handler_id - ID of event handler to unsubscribe
 */
void EVSYS_UnsubscribeEvent(int event_handler_id);

/*! @brief Dispatch a keyboard event
 *  @param[in] kb_event - event to be dispatched
*/
void EVSYS_DispatchKbEvent(EVSYS_kb_event kb_event);

/*! @brief Dispatch a mouse button event
 *  @param[in] mouse_btn_event - event to be dispatched
 */
void EVSYS_DispatchMouseBtnEvent(EVSYS_mouse_btn_event mouse_btn_event);

/*! @brief Dispatch a mouse move event
 *  @param[in] mouse_move_event - event to be dispatched
 */
void EVSYS_DispatchMouseMoveEvent(EVSYS_mouse_move_event mouse_move_event);

/*! @brief Dispatch a quit event
 */
void EVSYS_DispatchQuitEvent(void);

#endif // EVENT_SYSTEM_H
