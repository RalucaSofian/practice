/*! @file input_system.c
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
#include <stdlib.h> // malloc; free
#include <stdint.h> // uint...
#include <string.h> // strcpy...

#include "logger.h"
#include "event_system.h"
#include "input_system.h"

/************************************************************************
* INTERNAL DATA TYPES
************************************************************************/

/*! @brief Structure of the key info handled by the Input System
 */
typedef struct _INSYS_key_info
{
    INTYPES_key_state key_state;
    INTYPES_key_code  key_code;
    char*             key_name;
}INSYS_key_info;

/************************************************************************
* GLOBAL VARIABLES
************************************************************************/
INSYS_key_info key_info[KEY_LAST + 1]; // Key Info array
int kb_handl_id; // Handler ID of the KB event handler

/************************************************************************
* FUNCTION DEFINITIONS
************************************************************************/

/*! @brief Internal function used for initializing the Key Info structure
 */
static void init_key_info(void)
{
    char* temp_str = NULL;

    for (int i = 0; i <= KEY_LAST; i++)
    {
        switch (i)
        {
            case KEY_SPACE:
                temp_str = "KEY_SPACE";
                break;
            case KEY_APOSTROPHE:
                temp_str = "KEY_APOSTROPHE";
                break;
            case KEY_COMMA:
                temp_str = "KEY_COMMA";
                break;
            case KEY_MINUS:
                temp_str = "KEY_MINUS";
                break;
            case KEY_PERIOD:
                temp_str = "KEY_PERIOD";
                break;
            case KEY_SLASH:
                temp_str = "KEY_SLASH";
                break;
            case KEY_0:
                temp_str = "KEY_0";
                break;
            case KEY_1:
                temp_str = "KEY_1";
                break;
            case KEY_2:
                temp_str = "KEY_2";
                break;
            case KEY_3:
                temp_str = "KEY_3";
                break;
            case KEY_4:
                temp_str = "KEY_4";
                break;
            case KEY_5:
                temp_str = "KEY_5";
                break;
            case KEY_6:
                temp_str = "KEY_6";
                break;
            case KEY_7:
                temp_str = "KEY_7";
                break;
            case KEY_8:
                temp_str = "KEY_8";
                break;
            case KEY_9:
                temp_str = "KEY_9";
                break;
            case KEY_SEMICOLON:
                temp_str = "KEY_SEMICOLON";
                break;
            case KEY_EQUAL:
                temp_str = "KEY_EQUAL";
                break;
            case KEY_A:
                temp_str = "KEY_A";
                break;
            case KEY_B:
                temp_str = "KEY_B";
                break;
            case KEY_C:
                temp_str = "KEY_C";
                break;
            case KEY_D:
                temp_str = "KEY_D";
                break;
            case KEY_E:
                temp_str = "KEY_E";
                break;
            case KEY_F:
                temp_str = "KEY_F";
                break;
            case KEY_G:
                temp_str = "KEY_G";
                break;
            case KEY_H:
                temp_str = "KEY_H";
                break;
            case KEY_I:
                temp_str = "KEY_I";
                break;
            case KEY_J:
                temp_str = "KEY_J";
                break;
            case KEY_K:
                temp_str = "KEY_K";
                break;
            case KEY_L:
                temp_str = "KEY_L";
                break;
            case KEY_M:
                temp_str = "KEY_M";
                break;
            case KEY_N:
                temp_str = "KEY_N";
                break;
            case KEY_O:
                temp_str = "KEY_O";
                break;
            case KEY_P:
                temp_str = "KEY_P";
                break;
            case KEY_Q:
                temp_str = "KEY_Q";
                break;
            case KEY_R:
                temp_str = "KEY_R";
                break;
            case KEY_S:
                temp_str = "KEY_S";
                break;
            case KEY_T:
                temp_str = "KEY_T";
                break;
            case KEY_U:
                temp_str = "KEY_U";
                break;
            case KEY_V:
                temp_str = "KEY_V";
                break;
            case KEY_W:
                temp_str = "KEY_W";
                break;
            case KEY_X:
                temp_str = "KEY_X";
                break;
            case KEY_Y:
                temp_str = "KEY_Y";
                break;
            case KEY_Z:
                temp_str = "KEY_Z";
                break;
            case KEY_LEFT_BRACKET:
                temp_str = "KEY_LEFT_BRACKET";
                break;
            case KEY_BACKSLASH:
                temp_str = "KEY_BACKSLASH";
                break;
            case KEY_RIGHT_BRACKET:
                temp_str = "KEY_RIGHT_BRACKET";
                break;
            case KEY_GRAVE_ACCENT:
                temp_str = "KEY_GRAVE_ACCENT";
                break;
            case KEY_WORLD_1:
                temp_str = "KEY_WORLD_1";
                break;
            case KEY_WORLD_2:
                temp_str = "KEY_WORLD_2";
                break;
            case KEY_ESCAPE:
                temp_str = "KEY_ESCAPE";
                break;
            case KEY_ENTER:
                temp_str = "KEY_ENTER";
                break;
            case KEY_TAB:
                temp_str = "KEY_TAB";
                break;
            case KEY_BACKSPACE:
                temp_str = "KEY_BACKSPACE";
                break;
            case KEY_INSERT:
                temp_str = "KEY_INSERT";
                break;
            case KEY_DELETE:
                temp_str = "KEY_DELETE";
                break;
            case KEY_RIGHT:
                temp_str = "KEY_RIGHT";
                break;
            case KEY_LEFT:
                temp_str = "KEY_LEFT";
                break;
            case KEY_DOWN:
                temp_str = "KEY_DOWN";
                break;
            case KEY_UP:
                temp_str = "KEY_UP";
                break;
            case KEY_PAGE_UP:
                temp_str = "KEY_PAGE_UP";
                break;
            case KEY_PAGE_DOWN:
                temp_str = "KEY_PAGE_DOWN";
                break;
            case KEY_HOME:
                temp_str = "KEY_HOME";
                break;
            case KEY_END:
                temp_str = "KEY_END";
                break;
            case KEY_CAPS_LOCK:
                temp_str = "KEY_CAPS_LOCK";
                break;
            case KEY_SCROLL_LOCK:
                temp_str = "KEY_SCROLL_LOCK";
                break;
            case KEY_NUM_LOCK:
                temp_str = "KEY_NUM_LOCK";
                break;
            case KEY_PRINT_SCREEN:
                temp_str = "KEY_PRINT_SCREEN";
                break;
            case KEY_PAUSE:
                temp_str = "KEY_PAUSE";
                break;
            case KEY_F1:
                temp_str = "KEY_F1";
                break;
            case KEY_F2:
                temp_str = "KEY_F2";
                break;
            case KEY_F3:
                temp_str = "KEY_F3";
                break;
            case KEY_F4:
                temp_str = "KEY_F4";
                break;
            case KEY_F5:
                temp_str = "KEY_F5";
                break;
            case KEY_F6:
                temp_str = "KEY_F6";
                break;
            case KEY_F7:
                temp_str = "KEY_F7";
                break;
            case KEY_F8:
                temp_str = "KEY_F8";
                break;
            case KEY_F9:
                temp_str = "KEY_F9";
                break;
            case KEY_F10:
                temp_str = "KEY_F10";
                break;
            case KEY_F11:
                temp_str = "KEY_F11";
                break;
            case KEY_F12:
                temp_str = "KEY_F12";
                break;
            case KEY_F13:
                temp_str = "KEY_F13";
                break;
            case KEY_F14:
                temp_str = "KEY_F14";
                break;
            case KEY_F15:
                temp_str = "KEY_F15";
                break;
            case KEY_F16:
                temp_str = "KEY_F16";
                break;
            case KEY_F17:
                temp_str = "KEY_F17";
                break;
            case KEY_F18:
                temp_str = "KEY_F18";
                break;
            case KEY_F19:
                temp_str = "KEY_F19";
                break;
            case KEY_F20:
                temp_str = "KEY_F20";
                break;
            case KEY_F21:
                temp_str = "KEY_F21";
                break;
            case KEY_F22:
                temp_str = "KEY_F22";
                break;
            case KEY_F23:
                temp_str = "KEY_F23";
                break;
            case KEY_F24:
                temp_str = "KEY_F24";
                break;
            case KEY_F25:
                temp_str = "KEY_F25";
                break;
            case KEY_KP_0:
                temp_str = "KEY_KP_0";
                break;
            case KEY_KP_1:
                temp_str = "KEY_KP_1";
                break;
            case KEY_KP_2:
                temp_str = "KEY_KP_2";
                break;
            case KEY_KP_3:
                temp_str = "KEY_KP_3";
                break;
            case KEY_KP_4:
                temp_str = "KEY_KP_4";
                break;
            case KEY_KP_5:
                temp_str = "KEY_KP_5";
                break;
            case KEY_KP_6:
                temp_str = "KEY_KP_6";
                break;
            case KEY_KP_7:
                temp_str = "KEY_KP_7";
                break;
            case KEY_KP_8:
                temp_str = "KEY_KP_8";
                break;
            case KEY_KP_9:
                temp_str = "KEY_KP_9";
                break;
            case KEY_KP_DECIMAL:
                temp_str = "KEY_KP_DECIMAL";
                break;
            case KEY_KP_DIVIDE:
                temp_str = "KEY_KP_DIVIDE";
                break;
            case KEY_KP_MULTIPLY:
                temp_str = "KEY_KP_MULTIPLY";
                break;
            case KEY_KP_SUBTRACT:
                temp_str = "KEY_KP_SUBTRACT";
                break;
            case KEY_KP_ADD:
                temp_str = "KEY_KP_ADD";
                break;
            case KEY_KP_ENTER:
                temp_str = "KEY_KP_ENTER";
                break;
            case KEY_KP_EQUAL:
                temp_str = "KEY_KP_EQUAL";
                break;
            case KEY_LEFT_SHIFT:
                temp_str = "KEY_LEFT_SHIFT";
                break;
            case KEY_LEFT_CONTROL:
                temp_str = "KEY_LEFT_CONTROL";
                break;
            case KEY_LEFT_ALT:
                temp_str = "KEY_LEFT_ALT";
                break;
            case KEY_LEFT_SUPER:
                temp_str = "KEY_LEFT_SUPER";
                break;
            case KEY_RIGHT_SHIFT:
                temp_str = "KEY_RIGHT_SHIFT";
                break;
            case KEY_RIGHT_CONTROL:
                temp_str = "KEY_RIGHT_CONTROL";
                break;
            case KEY_RIGHT_ALT:
                temp_str = "KEY_RIGHT_ALT";
                break;
            case KEY_RIGHT_SUPER:
                temp_str = "KEY_RIGHT_SUPER";
                break;
            case KEY_MENU:
                temp_str = "KEY_MENU";
                break;
            default:
                temp_str = NULL;
                break;
        }
        if (NULL != temp_str)
        {
            key_info[i].key_state = KEY_STATE_RELEASED;
            key_info[i].key_code  = i;

            key_info[i].key_name = (char*)malloc(strlen(temp_str)+1);
            strcpy(key_info[i].key_name, temp_str);
        }
    }

}

/*! @brief Internal function used for clearing the Key Info
 *        structure before de-initialization of the Input System
 */
static void clear_key_info(void)
{
    for (int i = 0; i <= KEY_LAST; i++)
    {
        key_info[i].key_state = KEY_STATE_NONE;
        key_info[i].key_code  = KEY_LAST;

        if (NULL != key_info[i].key_name)
        {
            free(key_info[i].key_name);
        }
    }
}

/*! @brief Handler used for reacting to keyboard key changes.
 *  The Key Info structure is updated each time a kb key event
 *  is emitted
 */
static void kb_change_cbk(EVSYS_kb_event* kb_event)
{
    key_info[kb_event->key].key_state = kb_event->key_state;
    key_info[kb_event->key].key_code  = kb_event->key;

    LOGG_info("Updated KB Key. Key State = %d; Key Code = %d; Key Name = %s",
                key_info[kb_event->key].key_state,
                key_info[kb_event->key].key_code,
                key_info[kb_event->key].key_name);
}

/************************************************************************
************************************************************************/

void INSYS_Init(void)
{
    init_key_info();

    kb_handl_id = EVSYS_SubscribeKbEvent(kb_change_cbk);
}

void INSYS_GetKeyName(int key_code, const char** key_name)
{
    *key_name = key_info[key_code].key_name;
}

int INSYS_GetKeyState(INTYPES_key_code key_code)
{
    return key_info[key_code].key_state;
}

void INSYS_Deinit(void)
{
    clear_key_info();

    EVSYS_UnsubscribeEvent(kb_handl_id);
}
