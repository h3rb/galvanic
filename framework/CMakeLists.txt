cmake_minimum_required(VERSION 3.10)

#PROJECT
project(galvanic_framework)
set(EXEC "Galvanic")
set(CMAKE_CXX_STANDARD 11)

#NLOHMANN JSONHPP
#find_package(nlohmann_json 3.2.0 REQUIRED)

#AWS
find_package(AWSSDK REQUIRED COMPONENTS s3)
Message(STATUS "AWSSDK_LIB_DIR ${AWSSDK_LIB_DIR}")
Message(STATUS "AWSSDK_BIN_DIR $(AWSSDK_BIN_DIR}")
set(SERVICE "s3")
AWSSDK_DETERMINE_LIBS_TO_LINK(SERVICE OUTPUT)
Message(STATUS "All linked libs: ${OUTPUT}")
Message(STATUS "AWSSDK_PLATFORM_DEPS ${AWSSDK_PLATFORM_DEPS}")

#INCLUDES
include_directories(include)

#SOURCES
file(GLOB SOURCES sources/*.cpp)

#EXECUTABLE
link_directories("${AWSSDK_LIB_DIR}")
add_executable(${EXEC} ${SOURCES})

#COMPILER
target_compile_features(${EXEC} PUBLIC cxx_std_11)

#LINKING
link_libraries(stdc++fs)
target_link_libraries(Galvanic PUBLIC mysqlcppconn ${OUTPUT})
#target_link_libraries(Galvanic PRIVATE nlohmann_json::nlohmann_json)
target_include_directories(Galvanic PRIVATE ${AWSSDK_INCLUDE_DIR})

