#Other libraries to use into samples
find_package(GLUT)

# Make sure the compiler can find include files from our Hello library. 
include_directories (${VERSE_CORE_SOURCE_DIR}/modules)
IF (NOT LIBXML2_FOUND)
	include_directories (${VERSE_CORE_SOURCE_DIR}/3rdparty/libxml2/include)
	link_directories (${VERSE_CORE_SOURCE_DIR}/3rdparty/libxml2)
        set (LIBXML2_LIBRARIES xml2)
ENDIF (NOT LIBXML2_FOUND)

# Make sure the linker can find the Hello library once it is built. 
link_directories (${VERSE_CORE_BINARY_DIR}/modules/Core) 
link_directories (${VERSE_CORE_BINARY_DIR}/modules/Events) 
link_directories (${VERSE_CORE_BINARY_DIR}/modules/UI) 
link_directories (${VERSE_CORE_BINARY_DIR}/modules/Devices) 
link_directories (${VERSE_CORE_BINARY_DIR}/modules/Utils) 

# Add executable called "xxxDemo" that is built from the source files 
add_executable (eventDemo eventDemo.cpp) 
add_executable (appDemo appDemo.cpp) 
add_executable (menuDemo menuDemo.cpp) 

# Link the executable to the Hello library. 
target_link_libraries (eventDemo VerseCore VerseEvents) 
target_link_libraries (appDemo  ${FREETYPE_LIBRARY} ${GLUT_LIBRARY} ${OPENGL_LIBRARY} ${OpenCV_LIBS} VerseCore VerseEvents VerseUI VerseDevices) 
target_link_libraries (menuDemo  ${FREETYPE_LIBRARY} ${GLUT_LIBRARY} ${OPENGL_LIBRARY} ${OpenCV_LIBS} VerseCore VerseEvents VerseUI VerseDevices VerseUtils ${LIBXML2_LIBRARIES}) 
