/* @file logger.c
*
*
*
*
*
*/
/*********************************************************
* INCLUDES
*********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <stdarg.h>

#include "logger.h"

/*********************************************************
* DEFINES
*********************************************************/
#define MAX_TIMESTAMP          sizeof(char)*100
#define ANSI_COLOUR_GREEN      "\033[0;32m"
#define ANSI_COLOUR_ORANGE     "\033[38;2;255;165;0m"
#define ANSI_COLOUR_RED        "\033[0;31m"
#define ANSI_COLOUR_RESET      "\033[0m"

/*********************************************************
* FUNCTION DEFINITIONS
*********************************************************/

/*  Create timestamp to be used in logs
*   return timestamp formatted as string
*/
static char* logg_timestamp(void)
{
    char* timestamp = (char*)malloc(MAX_TIMESTAMP);
    char* no_millis = (char*)malloc(MAX_TIMESTAMP-10);

    /* format time from raw time into formatted string */
    time_t raw_time; 
    time(&raw_time);
    struct tm* info = localtime(&raw_time);
    strftime(no_millis, MAX_TIMESTAMP-10, "[%d-%m-%Y %H:%M:%S", info);

    /* extract miliseconds from epoch time */
    struct timeval epoch;
    gettimeofday(&epoch, NULL);
    unsigned long msec = epoch.tv_usec/1000;

    /* create final timestamp */
    sprintf(timestamp, "%s.%03lu]", no_millis, msec);

    free(no_millis);

    return timestamp;
}

/*  Log a message into the console, formatted as follows:
*   [timestamp][log level] Log message
*   [in] - log level
*   [in] - log message
*/
void logg(log_level log_lvl, const char* msg_in, ...)
{
    char message[1000];
    va_list args;
    va_start(args, msg_in);
    vsprintf(message, msg_in, args);
    va_end(args);

    char* timestamp = logg_timestamp();

    switch(log_lvl)
    {
        case LOGG_VERBOSE:
        {
            printf("%s [VERB] %s\n", timestamp, message);
            break;
        }

        case LOGG_INFO:
        {
            printf("%s %s[INFO]%s %s\n", timestamp, ANSI_COLOUR_GREEN, ANSI_COLOUR_RESET, message);
            break;
        }

        case LOGG_WARN:
        {
            printf("%s %s[WARN]%s %s\n", timestamp, ANSI_COLOUR_ORANGE, ANSI_COLOUR_RESET, message);
            break;
        }

        case LOGG_ERR:
        {
            printf("%s  %s[ERR]%s %s\n", timestamp, ANSI_COLOUR_RED, ANSI_COLOUR_RESET, message);
            break;
        }
        default:
            break;
    }

    free(timestamp);
}