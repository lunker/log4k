cmake_minimum_required(VERSION 3.8)
project(log4k)

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
set(CMAKE_CXX_STANDARD 11)

# Set Dependencies
## Boost
find_package(Boost REQUIRED)
find_package(Boost 1.64.0 COMPONENTS system log log_setup)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

set (GLIBMM_REQUIRED ^2.37)

#find_package(GLib REQUIRED)


if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_definitions (-DBOOST_ALL_DYN_LINK) # fuck
endif()
## End Boost
# End Set Dependencies

#set(SOURCE_FILES src/Logger.cpp src/Logger.hpp test_main.cpp)

if (DEBUG)
    message("Build log4k as debug mode")
#
#    set(HEADER_FILES src/Logger.hpp interface/logger_interface.h)
#    set(SOURCE_FILES src/Logger.cpp interface/logger_interface.c test_main.cpp)

    set(SOURCE_FILES src/Logger.cpp src/Logger.hpp interface/logger_interface.c interface/logger_interface.h test_main.cpp)
        SET_SOURCE_FILES_PROPERTIES(${SOURCE_FILES} PROPERTIES LANGUAGE CXX)
    # create runnable binary for test lib
#    add_executable(log4k ${HEADER_FILES} ${SOURCE_FILES})
    add_executable(log4k ${SOURCE_FILES})
    target_link_libraries(log4k ${Boost_LIBRARIES})
else()
    message("Build log4k as release mode")

#    set(HEADER_FILES src/Logger.hpp interface/logger_interface.h)
#    set(SOURCE_FILES src/Logger.cpp interface/logger_interface.c)
    set(SOURCE_FILES src/Logger.cpp src/Logger.hpp interface/logger_interface.c interface/logger_interface.h)
    SET_SOURCE_FILES_PROPERTIES(${SOURCE_FILES} PROPERTIES LANGUAGE CXX)
    set(LOG4K_INSTALL_DIR /Users/voiceloco/work/cppworkspace/log4k/build)

#    add_library(log4k SHARED ${HEADER_FILES} ${SOURCE_FILES}) # create log4k as shared library
        add_library(log4k SHARED ${SOURCE_FILES}) # create log4k as shared library
    add_definitions(log4k ${Boost_LIBRARIES})

    target_link_libraries(log4k
            ${Boost_LIBRARIES}
            )
    install(
            TARGETS log4k
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
            LIBRARY DESTINATION ${LOG4K_INSTALL_DIR}
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )
endif()


