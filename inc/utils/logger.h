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
#define LOGG_verbose(message, ...)
#else
#define LOGG_verbose(message, ...)  LOGG(LOGG_VERBOSE, message, __FILE__, ##__VA_ARGS__)
#endif
#define LOGG_info(message, ...)     LOGG(LOGG_INFO, message, __FILE__, ##__VA_ARGS__)
#define LOGG_warn(message, ...)     LOGG(LOGG_WARN, message, __FILE__, ##__VA_ARGS__)
#define LOGG_err(message, ...)      LOGG(LOGG_ERR, message, __FILE__, ##__VA_ARGS__)

/************************************************************************
* DATA TYPES
************************************************************************/

typedef enum _LOGG_log_level
{
    LOGG_VERBOSE = 0,
    LOGG_INFO,
    LOGG_WARN,
    LOGG_ERR,
    LOGG_LAST
}LOGG_log_level;

/************************************************************************
* FUNCTION DECLARATIONS
************************************************************************/

/*! @brief Function used to log a message into the console,
 *  formatted as follows: [timestamp][log level] Log message
 *  @param[in] log_lvl - log level
 *  @param[in] msg_in - log message
*/
void LOGG(LOGG_log_level log_lvl, const char* msg_in, const char* file_name, ...);

#endif // LOGGER_H
