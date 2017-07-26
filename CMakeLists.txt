cmake_minimum_required(VERSION 2.8)
project(log4k)

set(PROJECT_VERSION 1.0)
set(PROJECT_NAME log4k)

set(haha hahaaaaaa CACHE INTERNAL "test for variable")
set(CUSTOM_HINTS ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME})
#add_subdirectory(src)

# Debug message for cmake
message("cmake_source_dir : ${CMAKE_SOURCE_DIR}")
#find_path(test_find_path NAME src/Logger.h HINTS /usr/local/include/log4k)

#message("test find path : ${test_find_path}")

set(CUSTOM_PREFIX "${CMAKE_INSTALL_PREFIX}/include/log4k")
#set(INCLUDE_PREFIX "${CMAKE_INSTALL_INCLUDEDIR}/${CUSTOM_PREFIX}/modules/${VALUE_NAME}")


SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")
SET(CMAKE_CXX_STANDARD 11)

# Set Dependencies
## Boost
find_package(Boost REQUIRED)
find_package(Boost 1.54.0 COMPONENTS system log log_setup)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

## GLib
FIND_PACKAGE(PkgConfig)
PKG_CHECK_MODULES(GLIB2 REQUIRED glib-2.0>=2.36.0)
#include_directories(${GLIB2_INCLUDE_DIRS})

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_definitions (-DBOOST_ALL_DYN_LINK) # fuck
endif()

# Set Platform
if(APPLE)
    set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++0x")
    set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
endif()

if (DEBUG)
    message("Build log4k as debug mode")

    set(LOG4K_HEADER_FILES src/Logger.h src/logger_interface.h)
    set(LOG4K_SOURCE_FILES src/Logger.cpp src/logger_interface.c test_main.cpp)
    add_executable(log4k ${LOG4K_HEADER_FILES} ${LOG4K_SOURCE_FILES})

    set(SOURCE_FILES src/Logger.cpp src/Logger.h src/logger_interface.c src/logger_interface.h test_main.cpp)
    SET_SOURCE_FILES_PROPERTIES(${SOURCE_FILES} PROPERTIES LANGUAGE CXX)

    # create runnable binary for test lib
    set_target_properties(log4k PROPERTIES COMPILE_FLAGS "-m64" LINK_FLAGS "-m64")
    target_link_libraries(log4k
            ${Boost_LIBRARIES}
#            ${GLIB2_LIBRARIES}
            )
else()
    message("Build log4k as release mode")

    set(LOG4K_HEADER_FILES src/Logger.h src/logger_interface.h)
    set(LOG4K_SOURCE_FILES src/Logger.cpp src/logger_interface.c)

    foreach (HEADER ${LOG4K_HEADER_FILES})
        list (APPEND FIND_HEADERS ${HEADER})
    endforeach ()
        message(${FIND_HEADERS})

    SET_SOURCE_FILES_PROPERTIES(${LOG4K_HEADER_FILES} PROPERTIES LANGUAGE CXX)
    SET_SOURCE_FILES_PROPERTIES(${LOG4K_SOURCE_FILES} PROPERTIES LANGUAGE CXX)

#        TODO:: change hardcoding install path to platform configurable
    set(LOG4K_INSTALL_DIR /Users/voiceloco/work/cppworkspace/log4k/build)

    add_library(log4k SHARED ${LOG4K_HEADER_FILES} ${LOG4K_SOURCE_FILES}) # create log4k as shared library
        if(APPLE)
            message("Platform : 'osx' (i386)")
            set_target_properties(log4k PROPERTIES
                    COMPILE_FLAGS "-i386"
                    LINK_FLAGS "-i386")
        else()
            message("Platform : Others")
            set_target_properties(log4k PROPERTIES
                    COMPILE_FLAGS "-m64"
                    LINK_FLAGS "-m64")
        endif()

    target_link_libraries(log4k
            ${Boost_LIBRARIES}
#            ${GLIB2_LIBRARIES}
            )

    message("### CMAKE_INSTALL_INCLUDEDIR : ${CMAKE_INSTALL_INCLUDEDIR}")
    message("### CMAKE_INSTALL_PREFIX : ${CMAKE_INSTALL_PREFIX}")

    set(CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")
    set (CMAKE_MODULES_INSTALL_DIR
            ${CMAKE_INSTALL_DATAROOTDIR}/cmake-${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}/Modules
            CACHE STRING
            "Destination (relative to CMAKE_INSTALL_PREFIX) for cmake modules files"
            )

    install(
            TARGETS log4k
#            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
            RUNTIME DESTINATION bin
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib
            PUBLIC_HEADER DESTINATION dkdkdk
    )

    FILE(
            MAKE_DIRECTORY
            ${CMAKE_INSTALL_PREFIX}/log4k
    )

    FILE(
            MAKE_DIRECTORY
            ${CMAKE_INSTALL_PREFIX}/log4k/src
    )

    # Install library headers
    file(GLOB HEADERS src/*.h src/*.hpp)
    message("glob headers result : ${HEADERS}")
    install(FILES ${HEADERS} DESTINATION log4k/src)

    # Generate find_package cmake file
    configure_file(
            Findlog4k.cmake.in ${CMAKE_BINARY_DIR}/Findlog4k.cmake @ONLY
    )

    install(FILES
            ${CMAKE_BINARY_DIR}/Findlog4k.cmake
            DESTINATION ${CMAKE_MODULES_INSTALL_DIR}
    )
# end release mode
endif()



