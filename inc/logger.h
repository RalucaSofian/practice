/*! @file logger.h
 *
 *
 *
 *
 *
 */
#ifndef LOGGER_H
#define LOGGER_H

/************************************************************************
* MACROS
************************************************************************/
#ifdef PROD
#define logg_verbose(message, ...)
#else
#define logg_verbose(message, ...)  logg(LOGG_VERBOSE, message, __FILE__, ##__VA_ARGS__)
#endif
#define logg_info(message, ...)     logg(LOGG_INFO, message, __FILE__, ##__VA_ARGS__)
#define logg_warn(message, ...)     logg(LOGG_WARN, message, __FILE__, ##__VA_ARGS__)
#define logg_err(message, ...)      logg(LOGG_ERR, message, __FILE__, ##__VA_ARGS__)

/************************************************************************
* DATA TYPES
************************************************************************/

typedef enum _log_level
{
    LOGG_VERBOSE = 0,
    LOGG_INFO,
    LOGG_WARN,
    LOGG_ERR,
    LOGG_LAST
}log_level;

/************************************************************************
* FUNCTION DECLARATIONS
************************************************************************/

/*! @brief Function used to log a message into the console,
 *  formatted as follows: [timestamp][log level] Log message
 *  @param[in] log_lvl - log level
 *  @param[in] msg_in - log message
*/
void logg(log_level log_lvl, const char* msg_in, const char* file_name, ...);

#endif // LOGGER_H
