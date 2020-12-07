project(mod_galvanic)

cmake_minimum_required (VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I")

# The version number.
set(${CMAKE_PROJECT_NAME}_VERSION_MAJOR 1)
set(${CMAKE_PROJECT_NAME}_VERSION_MINOR 0)
set(${CMAKE_PROJECT_NAME}_VERSION_PATCH 0)
set(${CMAKE_PROJECT_NAME}_VERSION ${${CMAKE_PROJECT_NAME}_VERSION_MAJOR}.${${CMAKE_PROJECT_NAME}_VERSION_MINOR}.${${CMAKE_PROJECT_NAME}_VERSION_PATCH})
set(PROJECT_VERSION ${${CMAKE_PROJECT_NAME}_VERSION})

if(DEBUG)
  add_definitions(-DDEBUG)
endif()

# Deactivates standard main
add_definitions(-DBUILD_APACHE_MODULE)

# add the binary tree to the search path for include files
file(GLOB INCLUDES ../framework/include/*.h*)
file(GLOB SOURCES ../framework/sources/*.cpp)

include_directories("${PROJECT_SOURCE_DIR} ../framework/include")

#Threading, sometimes causes issue with AWS if this isn't here.
set(CMAKE_THREAD_LIBS_INIT "-lpthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)

#AWS
find_package(AWSSDK REQUIRED COMPONENTS s3)
Message(STATUS "AWSSDK_LIB_DIR ${AWSSDK_LIB_DIR}")
Message(STATUS "AWSSDK_BIN_DIR $(AWSSDK_BIN_DIR}")
set(SERVICE "s3")
AWSSDK_DETERMINE_LIBS_TO_LINK(SERVICE OUTPUT)
Message(STATUS "All linked libs: ${OUTPUT}")
Message(STATUS "AWSSDK_PLATFORM_DEPS ${AWSSDK_PLATFORM_DEPS}")

#APACHE
find_path(APACHE_INCLUDE_DIR NAMES httpd.h PATH_SUFFIXES httpd apache apache2)
if(NOT DEFINED APACHE_MODULE_DIR)
   find_program(APXS_BIN NAMES apxs apxs2 PATH_SUFFIXES httpd apache apache2)
   if(APXS_BIN)
      EXEC_PROGRAM(${APXS_BIN}
         ARGS -q LIBEXECDIR
         OUTPUT_VARIABLE APACHE_MODULE_DIR )
   endif(APXS_BIN)
endif(NOT DEFINED APACHE_MODULE_DIR)
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(APACHE DEFAULT_MSG APACHE_INCLUDE_DIR)
mark_as_advanced(APACHE_INCLUDE_DIR)

#APR
FIND_PATH(APR_INCLUDE_DIR apr.h /usr/local/include/apr-1 /usr/local/include/apr-1.0 /usr/include/apr-1 /usr/include/apr-1.0)
SET(APR_NAMES ${APR_NAMES} apr-1)
FIND_LIBRARY(APR_LIBRARY NAMES ${APR_NAMES} PATHS /usr/lib /usr/local/lib)
IF (APR_LIBRARY AND APR_INCLUDE_DIR)
    SET(APR_LIBRARIES ${APR_LIBRARY})
    SET(APR_FOUND "YES")
ELSE (APR_LIBRARY AND APR_INCLUDE_DIR)
    SET(APR_FOUND "NO")
ENDIF (APR_LIBRARY AND APR_INCLUDE_DIR)
IF (APR_FOUND)
    IF (NOT APR_FIND_QUIETLY)
        MESSAGE(STATUS "Found APR: ${APR_LIBRARIES}")
    ENDIF (NOT APR_FIND_QUIETLY)
ELSE (APR_FOUND)
    IF (APR_FIND_REQUIRED)
        MESSAGE(FATAL_ERROR "Could not find APR library")
    ENDIF (APR_FIND_REQUIRED)
ENDIF (APR_FOUND)
MARK_AS_ADVANCED(APR_LIBRARY APR_INCLUDE_DIR)

#APR Util
FIND_PATH(APRUTIL_INCLUDE_DIR apu.h /usr/local/include/apr-1 /usr/local/include/apr-1.0 /usr/include/apr-1 /usr/include/apr-1.0)
SET(APRUTIL_NAMES ${APRUTIL_NAMES} aprutil-1)
FIND_LIBRARY(APRUTIL_LIBRARY NAMES ${APRUTIL_NAMES} PATHS /usr/lib /usr/local/lib)
IF (APRUTIL_LIBRARY AND APRUTIL_INCLUDE_DIR)
    SET(APRUTIL_LIBRARIES ${APRUTIL_LIBRARY})
    SET(APRUTIL_FOUND "YES")
ELSE (APRUTIL_LIBRARY AND APRUTIL_INCLUDE_DIR)
    SET(APRUTIL_FOUND "NO")
ENDIF (APRUTIL_LIBRARY AND APRUTIL_INCLUDE_DIR)
IF (APRUTIL_FOUND)
    IF (NOT APRUTIL_FIND_QUIETLY)
        MESSAGE(STATUS "Found APRUTIL: ${APRUTIL_LIBRARIES}")
    ENDIF (NOT APRUTIL_FIND_QUIETLY)
ELSE (APRUTIL_FOUND)
    IF (APRUTIL_FIND_REQUIRED)
        MESSAGE(FATAL_ERROR "Could not find APRUTIL library")
    ENDIF (APRUTIL_FIND_REQUIRED)
ENDIF (APRUTIL_FOUND)
MARK_AS_ADVANCED(APRUTIL_LIBRARY APRUTIL_INCLUDE_DIR)

# Build Target
add_library(mod_galvanic MODULE ${SOURCES} a2mod_main.cpp)

SET_TARGET_PROPERTIES(mod_galvanic PROPERTIES PREFIX "")
SET_TARGET_PROPERTIES(mod_galvanic PROPERTIES SUFFIX ".so")
IF(WIN32)
    TARGET_LINK_LIBRARIES(mod_galvanic ${PROXY_LIBRARY} ${APR_LIBRARIES} ${APRUTIL_LIBRARIES} ${APACHE_LIBRARY} mysqlcppconn)
ELSE()
    TARGET_LINK_LIBRARIES(mod_galvanic ${APR_LIBRARIES} ${APRUTIL_LIBRARIES} ${APACHE_LIBRARY})
ENDIF()

#EXECUTABLE
#link_directories("${AWSSDK_LIB_DIR}")
#add_executable(${EXEC} ${SOURCES})

#COMPILER
#target_compile_features(${EXEC} PUBLIC cxx_std_11)

#LINKING
link_libraries(stdc++fs mysqlcppcon ${AWSSDK_INCLUDE_DIR})
#target_link_libraries(mod_galvanic PUBLIC mysqlcppconn ${OUTPUT})
target_include_directories(mod_galvanic PRIVATE mysqlcppconn ${AWSSDK_INCLUDE_DIR} ../framework/include)


