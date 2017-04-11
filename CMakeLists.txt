cmake_minimum_required(VERSION 2.6)
project(NSPlist)

add_library(NSPlist src/NSPlist.cpp src/NSPlistLexer.cpp src/NSPlistParser.cpp)

install(TARGETS NSPlist
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
install(DIRECTORY src/ DESTINATION include
        FILES_MATCHING PATTERN "*.h")
