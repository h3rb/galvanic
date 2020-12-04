project(mod_galvanic)

cmake_minimum_required (VERSION 3.10)
# set(CMAKE_CXX_STANDARD 11)

# The version number.
set(${CMAKE_PROJECT_NAME}_VERSION_MAJOR 1)
set(${CMAKE_PROJECT_NAME}_VERSION_MINOR 0)
set(${CMAKE_PROJECT_NAME}_VERSION_PATCH 0)
set(${CMAKE_PROJECT_NAME}_VERSION ${${CMAKE_PROJECT_NAME}_VERSION_MAJOR}.${${CMAKE_PROJECT_NAME}_VERSION_MINOR}.${${CMAKE_PROJECT_NAME}_VERSION_PATCH})
set(PROJECT_VERSION ${${CMAKE_PROJECT_NAME}_VERSION})

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/modules")
set(INPUT_CMAKE_DIR ${PROJECT_SOURCE_DIR}/cmake)
set(OUTPUT_CMAKE_DIR ${CMAKE_BINARY_DIR}/cmake)

if(DEBUG)
  set(CMAKE_CXX_FLAGS "-g -O2 -Wall -std=c++0x -fPIC")
else()
  set(CMAKE_CXX_FLAGS "-O2 -Wall -std=c++0x -fPIC")
endif()

if(DEBUG)
  add_definitions(-DDEBUG)
endif()

# Deactivates standard main
add_definitions(-DBUILD_APACHE_MODULE)

# add the binary tree to the search path for include files
file(GLOB INCLUDES ../framework/include/*.h*)
file(GLOB SOURCES ../framework/sources/*.cpp)

include_directories("${PROJECT_SOURCE_DIR} ${INCLUDES} ${SOURCES} a2mod_main.cpp")

#AWS
find_package(AWSSDK REQUIRED COMPONENTS s3)
Message(STATUS "AWSSDK_LIB_DIR ${AWSSDK_LIB_DIR}")
Message(STATUS "AWSSDK_BIN_DIR $(AWSSDK_BIN_DIR}")
set(SERVICE "s3")
AWSSDK_DETERMINE_LIBS_TO_LINK(SERVICE OUTPUT)
Message(STATUS "All linked libs: ${OUTPUT}")
Message(STATUS "AWSSDK_PLATFORM_DEPS ${AWSSDK_PLATFORM_DEPS}")

#EXECUTABLE
#link_directories("${AWSSDK_LIB_DIR}")
#add_executable(${EXEC} ${SOURCES})

#COMPILER
target_compile_features(${EXEC} PUBLIC cxx_std_11)

#LINKING
link_libraries(stdc++fs)
target_link_libraries(Galvanic PUBLIC mysqlcppconn ${OUTPUT})
target_include_directories(Galvanic PRIVATE ${AWSSDK_INCLUDE_DIR})
