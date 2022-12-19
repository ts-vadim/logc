# logc
A simple logging library written in C.

## Example
```c
int main() {
	LOGC_LOG("Hello, World");
	LOGC_LOGF("Hello, ", "formatting");
	LOGC_LOG_TRACE("Hello, file position and function");
	LOGC_LOGF_TRACE("Hello, ", "file position and function with formatting");
	return 0;
}
```
Output
```
Hello, World
Hello, formatting
Hello, file position and function At main.c:7:main()
Hello, file position and function with formatting At main.c:8:main()
```
