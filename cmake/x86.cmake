if(CMAKE_SYSTEM_PROCESSOR STREQUAL "i686")
  set(APPEND_CXX_FLAGS "${APPEND_CXX_FLAGS} -m32")
elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
  set(APPEND_CXX_FLAGS "${APPEND_CXX_FLAGS} -m64")
endif()

if(ENABLE_YUZU_SSE)
  if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(APPEND_CXX_FLAGS
        "${APPEND_CXX_FLAGS}  -msse -msse2 -msse3 -mssse3 -msse4.1 -msse4.2")
  elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # maybe sse/sse2 is used by default in x64 builds.
    set(APPEND_CXX_FLAGS "${APPEND_CXX_FLAGS} /arch:SSE2")
  endif()
endif()

if(ENABLE_YUZU_AVX2)
  if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(APPEND_CXX_FLAGS
        "${APPEND_CXX_FLAGS} -mavx2 -mfma -mf16c -mbmi -mbmi2 -mlzcnt")
  elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(APPEND_CXX_FLAGS "${APPEND_CXX_FLAGS} /arch:AVX2")
  endif()

  # if(CMAKE_CXX_COMPILER_ID MATCHES "GNU") set(APPEND_CXX_FLAGS
  # "${APPEND_CXX_FLAGS} -mno-avx256-split-unaligned-load
  # -mno-avx256-split-unaligned-store" ) endif()
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  # For GCC and Clang
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  # For MSVC
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${APPEND_CXX_FLAGS}")
