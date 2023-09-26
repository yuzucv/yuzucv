# cmake minimum required version
cmake_minimum_required(VERSION 3.19)

# project name
project(yuzucv LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ARTICRAFT_OUT "out")
set(CMAKE_INSTALL_PREFIX "install")

option(ENABLE_YUZU_SSE "SSE4_2 Instruction" ON)
option(ENABLE_YUZU_AVX2 "AVX2 Instruction" ON)
option(ENABLE_YUZU_NEON "NEON Instruction" ON)

if(CMAKE_GENERATOR MATCHES "Visual Studio")
  if((CMAKE_GENERATOR_PLATFORM STREQUAL "x64") OR (CMAKE_GENERATOR_PLATFORM
                                                   STREQUAL "x86"))
    include(cmake/x86.cmake)
  elseif((CMAKE_GENERATOR_PLATFORM STREQUAL "ARM") OR (CMAKE_GENERATOR_PLATFORM
                                                       STREQUAL "ARM64"))
    include(cmake/arm.cmake)
  else()
    message(FATAL_ERROR "Unknown value of CMAKE_GENERATOR_PLATFORM!")
  endif()
else()
  if((CMAKE_SYSTEM_PROCESSOR STREQUAL "i686") OR (CMAKE_SYSTEM_PROCESSOR
                                                  STREQUAL "x86_64"))
    include(cmake/x86.cmake)
  elseif((CMAKE_SYSTEM_PROCESSOR MATCHES "arm") OR (CMAKE_SYSTEM_PROCESSOR
                                                    STREQUAL "aarch64"))
    include(cmake/arm.cmake)
  else()
    message(FATAL_ERROR "Unknown value of CMAKE_SYSTEM_PROCESSOR!")
  endif()
endif()

if(ENABLE_YUZU_SSE)
  add_compile_definitions(ENABLE_YUZU_SSE)
endif()
if(ENABLE_YUZU_AVX2)
  add_compile_definitions(ENABLE_YUZU_AVX2)
endif()
if(ENABLE_YUZU_NEON)
  add_compile_definitions(ENABLE_YUZU_NEON)
endif()

# -----------------------------------------------------
# Compile condition
# -----------------------------------------------------
if(NOT DEFINED ENABLE_YUZUCV_TESTS)
  if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    if(NOT ANDROID)
      set(ENABLE_YUZUCV_TESTS ON)
    else()
      set(ENABLE_YUZUCV_TESTS OFF)
    endif()
  else()
    set(ENABLE_YUZUCV_TESTS OFF)
  endif()
endif()
message(STATUS "BUILD yuzucv TESTS: ${ENABLE_YUZUCV_TESTS}")

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  set(INTERNAL_YUZUCV OFF)
else()
  set(INTERNAL_YUZUCV ON)
endif()

# build type
if(CMAKE_BUILD_TYPE AND (CMAKE_BUILD_TYPE STREQUAL "Debug"))
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O0")
  add_definitions(-DDEBUG -D_DEBUG -DDEBUG_MODE)
  message("Debug mode:${CMAKE_C_FLAGS_DEBUG}")
elseif(CMAKE_BUILD_TYPE AND (CMAKE_BUILD_TYPE STREQUAL "Release"))
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3 -g")
  add_definitions(-DNDEBUG -DRELEASE_MODE -DNDEBUG_MODE)
  message("Release mode:${CMAKE_C_FLAGS_RELEASE}")
endif()

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
  message("This is Windows.")
  if(MSVC)
    add_compile_options(/utf-8)
    if(ENABLE_YUZU_SSE)
      add_compile_options(/arch:SSE)
    endif()
    if(ENABLE_YUZU_AVX2)
      add_compile_options(/arch:AVX2)
    endif()
    add_definitions(-D_CRT_SECURE_NO_WARNINGS -DUNICODE -D_UNICODE)
  endif()
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
  message("This is Linux.")
  add_compile_options(-fPIC)
elseif(CMAKE_SYSTEM_NAME MATCHES "Darwin")
  message("This is Mac OS X.")
endif()

file(GLOB_RECURSE SRC_NESTED src/*.cc)
add_library(yuzucv OBJECT ${SRC_NESTED})
add_library(yuzu::yuzucv ALIAS yuzucv)
target_include_directories(yuzucv PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)

if(ENABLE_YUZUCV_TESTS)
  add_subdirectory(tests)
endif()
