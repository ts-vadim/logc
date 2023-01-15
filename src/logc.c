#include "./logc.h"
#include "./ansi_colors.h"

#include <stdarg.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


static size_t _write_current_time(char* b, size_t bs);
static size_t _write_user_msg(char* b, size_t bs, const char* msg);
static size_t _write_user_fmt_msg(char* b, size_t bs, const char* fmt, va_list args);
static size_t _write_log_pos(char* b, size_t bs, logc_log_pos pos);
static size_t _write_logger_name(char* b, size_t bs, const char* name);
static void   _write_buffer(const char* b);
static bool   _is_pos_valid(logc_log_pos pos);


void logc_log(const char* name, logc_log_pos pos, const char* msg) {
	char b[LOGC_MAX_MESSAGE_LENGTH]; const size_t bs = sizeof(b); memset(b, 0, bs);
	char u[LOGC_USER_FORMAT_LENGTH]; const size_t us = sizeof(u); memset(u, 0, us);
	char t[LOGC_TIME_FORMAT_LENGTH]; const size_t ts = sizeof(t); memset(t, 0, ts);
	char p[LOGC_POS_FORMAT_LENGTH];  const size_t ps = sizeof(p); memset(p, 0, ps);
	char n[LOGC_LOGGER_NAME_LENGTH]; const size_t ns = sizeof(n); memset(n, 0, ns);

	_write_current_time(t, ts);
	_write_log_pos(p, ps, pos);
	_write_logger_name(n, ns, name);
	_write_user_msg(u, us, msg);

	snprintf(b, bs, "%s%s%s%s", t, n, u, p);

	_write_buffer(b);
}

void logc_logf(const char* name, logc_log_pos pos, const char* fmt, ...) {
	char b[LOGC_MAX_MESSAGE_LENGTH]; const size_t bs = sizeof(b); memset(b, 0, bs);
	char u[LOGC_USER_FORMAT_LENGTH]; const size_t us = sizeof(u); memset(u, 0, us);
	char t[LOGC_TIME_FORMAT_LENGTH]; const size_t ts = sizeof(t); memset(t, 0, ts);
	char p[LOGC_POS_FORMAT_LENGTH];  const size_t ps = sizeof(p); memset(p, 0, ps);
	char n[LOGC_LOGGER_NAME_LENGTH]; const size_t ns = sizeof(n); memset(n, 0, ns);

	_write_current_time(t, ts);
	_write_log_pos(p, ps, pos);
	_write_logger_name(n, ns, name);

	va_list args;
	va_start(args, fmt);
	_write_user_fmt_msg(u, us, fmt, args);
	va_end(args);

	snprintf(b, bs, "%s%s%s%s", t, n, u, p);

	_write_buffer(b);
}


static size_t _write_current_time(char* buffer, size_t bufsize) {
	return snprintf(
		buffer, 
		bufsize, 
		"%s[%11.6f]%s ", 
		ANSI_COLOR_GREEN, 
		(double)clock() / CLOCKS_PER_SEC,
		ANSI_RESET
	);
}

static size_t _write_user_msg(char* buffer, size_t bufsize, const char* msg) {
	return snprintf(
		buffer, 
		bufsize, 
		"%s%s%s ", 
		ANSI_RESET, 
		msg, 
		ANSI_RESET
	);
}

static size_t _write_user_fmt_msg(char* buffer, size_t bufsize, const char* fmt, va_list args) {
	size_t n = snprintf(buffer, bufsize, "%s", ANSI_RESET);
	n += vsnprintf(buffer+n, bufsize-n, fmt, args);
	return n + snprintf(buffer+n, bufsize-n, "%s ", ANSI_RESET);
}

static size_t _write_log_pos(char* buffer, size_t bufsize, logc_log_pos pos) {
	if (!_is_pos_valid(pos))
		return 0;

	return snprintf(
		buffer, 
		bufsize, 
		"%sAt %s:%d:%s()%s ", 
		ANSI_COLOR_WHITE, 
		pos.file, pos.line, pos.func,
		ANSI_RESET 
	);
}

static size_t _write_logger_name(char* buffer, size_t bufsize, const char* name) {
	if (name) {
		return snprintf(
			buffer, 
			bufsize, 
			"%s%s%s:%s ", 
			ANSI_COLOR_YELLOW, 
			name,
			ANSI_RESET, 
			ANSI_RESET 
		);
	} else {
		return 0;
	}
}

static void _write_buffer(const char* b) {
	printf("%s\n", b);
}

static bool _is_pos_valid(logc_log_pos pos) {
	return pos.file && pos.func && pos.line;
}
