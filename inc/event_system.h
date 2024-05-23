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
typedef enum _es_ev_type
{
    ES_KEYBOARD_EV = 0,
    ES_MOUSE_BTN_EV,
    ES_MOUSE_MOVE_EV,
    ES_WINDOW_RESIZE_EV,
    ES_PAUSE_EV,
    ES_QUIT_EV,
    ES_LAST_EV
}es_ev_type;

/*! @brief Possible states for a button
 */
typedef enum _es_btn_state
{
    ES_BUTTON_RELEASED = 0,
    ES_BUTTON_PRESSED,
    ES_BUTTON_LAST
}es_btn_state;

/*! @brief Structure of the keyboard events to be handled by the system
 */
typedef struct _es_kb_event
{
    es_btn_state key_state;
    key_code     key;
}es_kb_event;

/*! @brief Structure of the mouse buttons events to be handled by the system
 */
typedef struct _es_mouse_btn_event
{
    es_btn_state button_state;
    //! TODO: create translation from GLFW keycodes
    int          button;
}es_mouse_btn_event;

/*! @brief Structure of the mouse move events to be handled by the system
 */
typedef struct _es_mouse_move_event
{
    float x_pos;
    float y_pos;
}es_mouse_move_event;


/*! @brief Function pointer type for keyboard event handlers
 */
typedef void (* es_kb_ev_handler)(es_kb_event* kb_event);

/*! @brief Function pointer type for mouse buttons event handlers
 */
typedef void (* es_mouse_btn_ev_handler)(es_mouse_btn_event* mouse_btn_event);

/*! @brief Function pointer type for mouse move event handlers
 */
typedef void (* es_mouse_move_ev_handler)(es_mouse_move_event* mouse_move_event);

/*! @brief Function pointer type for quit event handlers
 */
typedef void (* es_quit_ev_handler)(void);

/************************************************************************
* FUNCTION DECLARATIONS
************************************************************************/

/*! @brief Initialize the Event System
 */
void es_init(void);

/*! @brief Subscribe to a keyboard event
 *  @param[out] event_handler - handler function for kb events
 *  @return ID of the subscribed event handler
 */
int es_subscribe_kb_event(es_kb_ev_handler event_handler);

/*! @brief Subscribe to a mouse button event
 *  @param[out] event_handler - handler function for mouse button events
 *  @return ID of the subscribed event handler
 */
int es_subscribe_mouse_btn_event(es_mouse_btn_ev_handler event_handler);

/*! @brief Subscribe to a mouse move event
 *  @param[out] event_handler - handler function for mouse move events
 *  @return ID of the subscribed event handler
 */
int es_subscribe_mouse_move_event(es_mouse_move_ev_handler event_handler);

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
int es_subscribe_quit_event(es_quit_ev_handler event_handler);

/*! @brief Unsubscribe from an event
 *  @param[in] event_handler_id - ID of event handler to unsubscribe
 */
void es_unsubscribe_event(int event_handler_id);

/*! @brief Dispatch a keyboard event
 *  @param[in] kb_event - event to be dispatched
*/
void es_dispatch_kb_event(es_kb_event kb_event);

/*! @brief Dispatch a mouse button event
 *  @param[in] mouse_btn_event - event to be dispatched
 */
void es_dispatch_mouse_btn_event(es_mouse_btn_event mouse_btn_event);

/*! @brief Dispatch a mouse move event
 *  @param[in] mouse_move_event - event to be dispatched
 */
void es_dispatch_mouse_move_event(es_mouse_move_event mouse_move_event);

/*! @brief Dispatch a quit event
 */
void es_dispatch_quit_event(void);

#endif // EVENT_SYSTEM_H
