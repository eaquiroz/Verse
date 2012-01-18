cmake_minimum_required (VERSION 2.6) 

include_directories (${VERSE_CORE_SOURCE_DIR}/modules)

file(GLOB lib_srcs *.cpp)
file(GLOB lib_hdrs *.h)

add_library(VerseEvents  STATIC ${lib_srcs} ${lib_hdrs})