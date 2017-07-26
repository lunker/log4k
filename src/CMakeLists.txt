# CMakeLists in haha

message("cmakelists in 'src'")
message(${haha})

set(PRIVATE_PREFFIX src)
set(SOURCE_FILES
        Logger.cpp
        logger_interface.c
        )
set(HEADER_FILES
        Logger.h
        logger_interface.h
        )

message("cmake source dir : ${CMAKE_SOURCE_DIR}/build}")
message(${CMAKE_INCLUDE_PATH})

FILE(
        MAKE_DIRECTORY
        /usr/local/include/log4k
)
message("Create '/usr/local/include/log4k/src'")

install(

)

FILE(
        COPY
        ${SOURCE_FILES}
#        DESTINATION ${CMAKE_SOURCE_DIR}/build/${PRIVATE_PREFFIX}
        DESTINATION /usr/local/include/log4k/${PRIVATE_PREFIX}
        FILE_PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
        DIRECTORY_PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
        USE_SOURCE_PERMISSIONS
        FILES_MATCHING
            PATTERN "*.cpp"
            PATTERN "*.c"
)


#add_custom_command(TARGET log4k PRE_BUILD
#        COMMAND ${CMAKE_COMMAND} -E make_directory
#        ${CMAKE_SOURCE_DIR}/build/src)
#
#add_custom_command(TARGET log4k PRE_BUILD
#        COMMAND ${CMAKE_COMMAND} -E make_directory
#        /usr/local/include/log4k/src
#        )
#
#file(COPY "src/" DESTINATION "dst" FILES_MATCHING PATTERN "*.bat")
#
#
#add_custom_command(TARGET log4k PRE_BUILD
#        COMMAND ${CMAKE_COMMAND} -E COPY ${CMAKE_SOURCE_DIR} /usr/local/include/log4k/src FILES_MATCHING PATTERN *.h
#        )
#
#add_custom_command(TARGET log4k PRE_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_directory
#        ${CMAKE_SOURCE_DIR}/src $<TARGET_FILE_DIR:log4k>/src)

