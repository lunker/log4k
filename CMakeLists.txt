cmake_minimum_required(VERSION 3.8)
project(log4k)

set(CMAKE_CXX_STANDARD 11)

# Set Dependencies
## Boost
find_package(Boost REQUIRED)
find_package(Boost 1.64.0 COMPONENTS system log log_setup)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_definitions (-DBOOST_ALL_DYN_LINK) # fuck
endif()
## End Boost
# End Set Dependencies

set(SOURCE_FILES library.cpp library.h src/logger.cpp src/logger.hpp test_main.cpp)

if (DEBUG)
    message("Build log4k as debug mode")
    # create runnable binary for test lib
    add_executable(log4k ${SOURCE_FILES})
    target_link_libraries(log4k ${Boost_LIBRARIES})
else()
    message("Build log4k as release mode")
    set(LOG4K_INSTALL_DIR /Users/voiceloco/work/cppworkspace/log4k/build)
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


