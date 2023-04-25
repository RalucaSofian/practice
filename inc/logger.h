#ifndef LOGGER_H
#define LOGGER_H
/* @file logger.h
*
*
*
*
*
*/
/*********************************************************
* MACROS
*********************************************************/
#ifdef PROD
#define logg_verbose(message, ...)
#else
#define logg_verbose(message, ...)  logg(LOGG_VERBOSE, message, ##__VA_ARGS__)
#endif
#define logg_info(message, ...)     logg(LOGG_INFO, message, ##__VA_ARGS__)
#define logg_warn(message, ...)     logg(LOGG_WARN, message, ##__VA_ARGS__)
#define logg_err(message, ...)      logg(LOGG_ERR, message, ##__VA_ARGS__)

/*********************************************************
* DATA TYPES
*********************************************************/
typedef enum log_level_
{
    LOGG_VERBOSE = 0,
    LOGG_INFO,
    LOGG_WARN,
    LOGG_ERR,
    LOGG_LAST
}log_level;

/*  Log a message into the console, formatted as follows:
*   [timestamp][log level] Log message
*   [in] - log level
*   [in] - log message
*/
void logg(log_level log_lvl, const char* msg_in, ...);

#endif /* LOGGER_H */
