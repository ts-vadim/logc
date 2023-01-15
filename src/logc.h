#ifndef LOGC_LOG_H
#define LOGC_LOG_H

#include <stdarg.h>
#include <string.h>


#define LOGC_VERSION "0.1.0"

#ifndef LOGC_FUNC
#define LOGC_FUNC __FUNCTION__
#endif

#ifndef LOGC_FILE
#define LOGC_FILE ((strrchr(__FILE__, '/') != NULL) \
	? strrchr(__FILE__, '/') + 1 \
	: (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__))
#endif

#ifndef LOGC_LINE
#define LOGC_LINE __LINE__
#endif

#ifndef LOGC_TIME_FORMAT_LENGTH
#define LOGC_TIME_FORMAT_LENGTH 32
#endif

#ifndef LOGC_USER_FORMAT_LENGTH
#define LOGC_USER_FORMAT_LENGTH 256
#endif

#ifndef LOGC_POS_FORMAT_LENGTH
#define LOGC_POS_FORMAT_LENGTH 64
#endif

#ifndef LOGC_LOGGER_NAME_LENGTH
#define LOGC_LOGGER_NAME_LENGTH 32
#endif

#ifndef LOGC_MAX_MESSAGE_LENGTH
#define LOGC_MAX_MESSAGE_LENGTH (LOGC_TIME_FORMAT_LENGTH + LOGC_USER_FORMAT_LENGTH + LOGC_POS_FORMAT_LENGTH + LOGC_LOGGER_NAME_LENGTH)
#endif

#ifndef LOGC_DEFAULT_LOGGER_NAME
#define LOGC_DEFAULT_LOGGER_NAME NULL
#endif


typedef struct {
	const char* func;
	const char* file;
	int line;
} logc_log_pos;


void logc_log(const char* name, logc_log_pos pos, const char* msg);
void logc_logf(const char* name, logc_log_pos pos, const char* fmt, ...);


#define LOGC_GET_CURRENT_POS() 		((logc_log_pos) { .func = LOGC_FUNC, .file = LOGC_FILE, .line = LOGC_LINE })
#define LOGC_GET_NULL_POS() 		((logc_log_pos) { .func = NULL, .file = NULL, .line = 0 })

#define LOGC_LOG_NAMED(name, msg)				logc_log(name, LOGC_GET_NULL_POS(), msg)
#define LOGC_LOG_NAMED_TRACE(name, msg)			logc_log(name, LOGC_GET_CURRENT_POS(), msg)

#define LOGC_LOGF_NAMED(name, fmt, ...)			logc_logf(name, LOGC_GET_NULL_POS(), fmt, __VA_ARGS__)
#define LOGC_LOGF_NAMED_TRACE(name, fmt, ...)	logc_logf(name, LOGC_GET_CURRENT_POS(), fmt, __VA_ARGS__)

#define LOGC_LOG(msg)							LOGC_LOG_NAMED(LOGC_DEFAULT_LOGGER_NAME, msg)
#define LOGC_LOG_TRACE(msg)						LOGC_LOG_NAMED_TRACE(LOGC_DEFAULT_LOGGER_NAME, msg)

#define LOGC_LOGF(fmt, ...)						LOGC_LOGF_NAMED(LOGC_DEFAULT_LOGGER_NAME, fmt, __VA_ARGS__)
#define LOGC_LOGF_TRACE(fmt, ...)				LOGC_LOGF_NAMED_TRACE(LOGC_DEFAULT_LOGGER_NAME, fmt, __VA_ARGS__)

#endif
