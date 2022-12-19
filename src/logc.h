#ifndef LOGC_LOG_H
#define LOGC_LOG_H

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <time.h>



#define LOGC_FUNC __FUNCTION__
#define LOGC_FILE ((strrchr(__FILE__, '/') != NULL) \
	? strrchr(__FILE__, '/') + 1 \
	: (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__))
#define LOGC_LINE __LINE__

#ifndef LOGC_VERSION
#define LOGC_VERSION "0.1.0"
#endif
#ifndef LOGC_MAX_MESSAGE_LENGTH
#define LOGC_MAX_MESSAGE_LENGTH 256
#endif


typedef enum {
	LOGC_LOGLEVEL_DEFAULT		= 0x01,
	LOGC_LOGLEVEL_INFO			= 0x02,
	LOGC_LOGLEVEL_WARNING		= 0x04,
	LOGC_LOGLEVEL_SUCCESS		= 0x08,
	LOGC_LOGLEVEL_FAIL			= 0x10,
	LOGC_LOGLEVEL_FATAL			= 0x20
} logc_log_level;

typedef struct {
	const char* func;
	const char* file;
	uint32_t line;
} logc_log_pos;


void logc_log(logc_log_level level, const char* msg);
void logc_logf(logc_log_level level, const char* fmt, ...);
void logc_log_trace(logc_log_level level, logc_log_pos pos, const char* msg);
void logc_logf_trace(logc_log_level level, logc_log_pos pos, const char* fmt, ...);

#define LOGC_GET_CURRENT_POS() 		((logc_log_pos) { .func = LOGC_FUNC, .file = LOGC_FILE, .line = LOGC_LINE })

#define LOGC_LOG(msg)				logc_log(LOGC_LOGLEVEL_DEFAULT, msg)
#define LOGC_LOGF(fmt, ...)			logc_logf(LOGC_LOGLEVEL_DEFAULT, fmt, __VA_ARGS__)
#define LOGC_LOG_TRACE(msg)			logc_log_trace(LOGC_LOGLEVEL_DEFAULT, LOGC_GET_CURRENT_POS(), msg)
#define LOGC_LOGF_TRACE(fmt, ...)	logc_logf_trace(LOGC_LOGLEVEL_DEFAULT, LOGC_GET_CURRENT_POS(), fmt, __VA_ARGS__)

#endif
