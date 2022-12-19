
project("test" C)
add_executable("test" "./main.c")
target_link_libraries("test" PUBLIC "logc")