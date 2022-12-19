#include "../src/logc.h"


int main(void) {
	LOGC_LOG("Hello, World");
	LOGC_LOGF("Hello, %s", "Formatting");
	LOGC_LOG_TRACE("Hello, Trace logging");
	LOGC_LOGF_TRACE("Hello, Trace logging with %s", "formatting");

	return 0;
}