#include "../src/logc.h"


int main() {
	LOGC_LOG("Hello, World");
	LOGC_LOGF("Hello, %s", "formatting");
	LOGC_LOG_TRACE("Hello, file position and function");
	LOGC_LOGF_TRACE("Hello, %s", "file position and function with formatting");
	return 0;
}