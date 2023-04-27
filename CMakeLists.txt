cmake_minimum_required(VERSION 3.21 FATAL_ERROR)

project(Necs C CXX)

set (NECS_SOURCE_FILES
    "src/Archetype.h"
    "src/Component.h"
    "src/Core.h"
    "src/Entity.h"
    "src/Registry.h"
)

add_library(${PROJECT_NAME} INTERFACE ${NECS_SOURCE_FILES})
# target_include_directories(${PROJECT_NAME} INTERFACE "/src")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
# set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

# Definitions
target_compile_definitions(${PROJECT_NAME} INTERFACE 
    "$<$<CONFIG:Debug>:"
        "_DEBUG"
    ">"
)




