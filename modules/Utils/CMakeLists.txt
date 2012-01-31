cmake_minimum_required (VERSION 2.6) 

include_directories (${VERSE_CORE_SOURCE_DIR}/modules)

IF (NOT LIBXML2_FOUND)
	include_directories (${VERSE_CORE_SOURCE_DIR}/3rdparty/libxml2/include)
ENDIF (NOT LIBXML2_FOUND)

file(GLOB lib_srcs *.cpp)
file(GLOB lib_hdrs *.h)

add_library(VerseUtils  STATIC ${lib_srcs} ${lib_hdrs})
