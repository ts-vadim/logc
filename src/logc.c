#include "./logc.h"
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define ANSI_RESET					"\033[00m"
#define ANSI_BOLD					"\033[1m"
#define ANSI_DARK					"\033[2m"
#define ANSI_UNDERLINE				"\033[4m"
#define ANSI_BLINK					"\033[5m"
#define ANSI_REVERSE				"\033[7m"
#define ANSI_CONCEALED				"\033[8m"

#define ANSI_COLOR_BLACK			"\033[30m"
#define ANSI_COLOR_RED				"\033[31m"
#define ANSI_COLOR_GREEN			"\033[32m"
#define ANSI_COLOR_YELLOW			"\033[33m"
#define ANSI_COLOR_BLUE				"\033[34m"
#define ANSI_COLOR_MAGENTA			"\033[35m"
#define ANSI_COLOR_CYAN				"\033[36m"
#define ANSI_COLOR_WHITE			"\033[37m"

#define ANSI_COLOR_RED_BRIGHT		"\033[31;1m"
#define ANSI_COLOR_GREEN_BRIGHT		"\033[32;1m"
#define ANSI_COLOR_YELLOW_BRIGHT	"\033[33;1m"
#define ANSI_COLOR_BLUE_BRIGHT		"\033[34;1m"
#define ANSI_COLOR_MAGENTA_BRIGHT	"\033[35;1m"
#define ANSI_COLOR_CYAN_BRIGHT		"\033[36;1m"
#define ANSI_COLOR_WHITE_BRIGHT		"\033[37;1m"

#define ANSI_COLOR_BG_BLACK			"\033[40m"
#define ANSI_COLOR_BG_RED			"\033[41m"
#define ANSI_COLOR_BG_GREEN			"\033[42m"
#define ANSI_COLOR_BG_YELLOW		"\033[43m"
#define ANSI_COLOR_BG_BLUE			"\033[44m"
#define ANSI_COLOR_BG_MAGENTA		"\033[45m"
#define ANSI_COLOR_BG_CYAN			"\033[46m"
#define ANSI_COLOR_BG_WHITE			"\033[47m"

#define ANSI_COLOR_BG_BLACK_BRIGHT	"\033[40;1m"
#define ANSI_COLOR_BG_RED_BRIGHT	"\033[41;1m"
#define ANSI_COLOR_BG_GREEN_BRIGHT	"\033[42;1m"
#define ANSI_COLOR_BG_YELLOW_BRIGHT	"\033[43;1m"
#define ANSI_COLOR_BG_BLUE_BRIGHT	"\033[44;1m"
#define ANSI_COLOR_BG_MAGENTA_BRIGHT "\033[45;1m"
#define ANSI_COLOR_BG_CYAN_BRIGHT	"\033[46;1m"
#define ANSI_COLOR_BG_WHITE_BRIGHT	"\033[47;1m"


static char* s_level_names[] = {
};

static char s_msg_buffer[LOGC_MAX_MESSAGE_LENGTH];

void logc_log(logc_log_level level, const char* msg) {
	printf("%s%s%s\n", ANSI_COLOR_WHITE_BRIGHT, msg, ANSI_RESET);
}

void logc_logf(logc_log_level level, const char* fmt, ...) {
	memset(s_msg_buffer, 0, sizeof(s_msg_buffer));

	va_list args;
	va_start(args, fmt);
	vsnprintf(s_msg_buffer, sizeof(s_msg_buffer), fmt, args);
	va_end(args);

	logc_log(level, s_msg_buffer);
}

void logc_log_trace(logc_log_level level, logc_log_pos pos, const char* msg) {
	printf(
		"%s%s%s %sAt %s:%d:%s()%s\n", 
		ANSI_COLOR_WHITE_BRIGHT,
		msg,
		ANSI_RESET,
		ANSI_COLOR_WHITE, 
		pos.file, pos.line, pos.func,
		ANSI_RESET 
	);
}

void logc_logf_trace(logc_log_level level, logc_log_pos pos, const char* fmt, ...) {
	memset(s_msg_buffer, 0, sizeof(s_msg_buffer));

	va_list args;
	va_start(args, fmt);
	vsnprintf(s_msg_buffer, sizeof(s_msg_buffer), fmt, args);
	va_end(args);

	logc_log_trace(level, pos, s_msg_buffer);
}
