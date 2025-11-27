cmake_minimum_required(VERSION 3.22)
project(cpp-stms-lang)

include(CTest)

option(CPP_STMS_SANITIZER "Enable the sanitizer for testing and debug" OFF)


set(CMAKE_CXX_STANDARD 23)
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

list(APPEND CPP_SSTM_SRC_LIST "src/transactional.cpp")

add_library(cpp-sstm)
target_include_directories(cpp-sstm PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> # for consumers
    $<INSTALL_INTERFACE:include> # for installation
)

target_sources(cpp-sstm 
    PUBLIC
        # Public headers
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/cpp-sstm/sstm.hpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/cpp-sstm/tvar.hpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/cpp-sstm/transaction.hpp>
    PRIVATE
        # Implementation files
        ${CPP_SSTM_SRC_LIST}
)

## test executable
add_executable(cpp-sstm-tests ${CPP_SSTM_SRC_LIST})
target_compile_definitions(cpp-sstm-tests
    PRIVATE
        CPP_SSTM_TESTS
)

target_include_directories(cpp-sstm-tests PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> 
)
target_link_libraries(cpp-sstm-tests PRIVATE doctest::doctest)
add_test(NAME cpp-sstm-tests COMMAND cpp-sstm-tests)


add_subdirectory(external)