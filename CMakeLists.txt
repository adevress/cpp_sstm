cmake_minimum_required(VERSION 3.22)
project(cpp-stms-lang)

include(CTest)

option(CPP_STMS_SANITIZER "Enable the sanitizer for testing and debug" OFF)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

if(NOT CMAKE_BUILD_TYPE)
set(CMAKE_BUILD_TYPE "RelWithDebInfo")
endif()


list(APPEND CPP_STMS_COMMON_FLAGS 
    "-Wall"
    "-Wextra"
    "-Wno-missing-field-initializers"
    "-Werror=conversion"
    "-Wformat-security"
    "-Wshadow"    
    "-fno-omit-frame-pointer"
    "-fwrapv"
)


if(CPP_STMS_SANITIZER)
list(APPEND CPP_STMS_COMMON_FLAGS 
    "-fsanitize=address"
    "-fsanitize=undefined"
)
list(APPEND CPP_STMS_COMMON_LINK_FLAGS 
    "-fsanitize=address"
    "-fsanitize=undefined"
)
endif()

