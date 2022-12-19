cmake_minimum_required(VERSION 3.16)


# ===== Project ===== #
project(logc VERSION 0.1.0 LANGUAGES C)
# add_definitions("-DLOGC_VERSION ${PROJECT_VERSION}")


# ===== Source files ===== #
set(
	SOURCES
	"${CMAKE_CURRENT_SOURCE_DIR}/src/logc.c"
)


# ===== Library ===== #
add_library(${PROJECT_NAME} STATIC ${SOURCES})


# ===== Include directories ===== #
set(
	INCLUDE_DIRECTORIES
	"${CMAKE_CURRENT_SOURCE_DIR}/src"
)
target_include_directories(
	${PROJECT_NAME}
	PUBLIC "$<BUILD_INTERFACE:${INCLUDE_DIRECTORIES}>"
)


# ===== Link libraries ===== #
# target_link_libraries(
# 	${PROJECT_NAME}
# )


# ===== Tests ===== #
option(LOGC_BUILD_TESTS "Build tests" OFF)
if (LOGC_BUILD_TESTS)
	add_subdirectory("tests/")
endif()