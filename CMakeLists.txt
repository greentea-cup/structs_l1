cmake_minimum_required(VERSION 3.5.0)

get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${ProjectId} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CLANG_FLAGS -Wall -Wextra -Wpedantic -O3 $<$<CONFIG:Debug>:-pg>)
set(GNU_FLAGS -Wall -Wextra -Wpedantic -O3 $<$<CONFIG:Debug>:-pg>)
set(MSVC_FLAGS /utf-8 /J /W4 /Oi $<$<CONFIG:Release>:/O2>)

foreach(TARGET_N 1 2 3 4 5 6)
	add_executable(app${TARGET_N} "src/main${TARGET_N}.cpp" "src/process_str.cpp")
endforeach()
add_executable(app_laba3_one "laba3/main_one.cpp")
add_executable(app_laba3_double "laba3/main_double.cpp")
target_include_directories(app_laba3_one PRIVATE "laba3")
target_include_directories(app_laba3_double PRIVATE "laba3")

foreach(TARGET_N 1 2 3 4 5 6 laba3_one laba3_double)
	if (CMAKE_C_COMPILER_ID STREQUAL "Clang")
		target_compile_options(app${TARGET_N} PRIVATE ${CLANG_FLAGS})
	elseif (CMAKE_C_COMPILER_ID STREQUAL "GNU")
		target_compile_options(app${TARGET_N} PRIVATE ${GNU_FLAGS})
	elseif (CMAKE_C_COMPILER_ID STREQUAL "MSVC")
		target_compile_options(app${TARGET_N} PRIVATE ${MSVC_FLAGS})
		target_compile_definitions(app${TARGET_N} PRIVATE _CRT_SECURE_NO_WARNINGS)
	endif()
endforeach()

