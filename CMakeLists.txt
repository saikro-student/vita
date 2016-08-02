cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project("VITA")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/tools/cmake_modules)


enable_testing()

if (NOT CONFIGURED_ONCE)
    if (CMAKE_COMPILER_IS_GNUCXX)
        set(warnings "-Wall -Wextra -Werror")
    elseif (MSVC)
        set(warnings "/W4 /WX /EHsc")
    endif()
    set(CMAKE_CXX_FLAGS "${warnings}"
        CACHE STRING "Flags used by the compiler during all build types." FORCE)
    set(CMAKE_C_FLAGS   "${warnings}"
        CACHE STRING "Flags used by the compiler during all build types." FORCE)

    set(TOOLS_DIR ${CMAKE_SOURCE_DIR}/tools
        CACHE PATH
        "It's a path where all tools of a project are located.")

    set(${CMAKE_PROJECT_NAME}_3RD_PARTY_DIR ${CMAKE_SOURCE_DIR}/impl/third_party
        CACHE PATH
        "It's a path where 3rd party libs are located.")

    include(github)
    fetch_3rd_party_from_github("google" "googletest")
endif()

include(gmock)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(impl)

set(CONFIGURED_ONCE TRUE CACHE INTERNAL
    "A flag showing that CMake has configured at least once.")
