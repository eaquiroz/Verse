#Other libraries to use into samples
find_package(GLUT)

# Make sure the compiler can find include files from our Hello library. 
include_directories (${VERSE_CORE_SOURCE_DIR}/modules)

# Make sure the linker can find the Hello library once it is built. 
link_directories (${VERSE_CORE_BINARY_DIR}/modules/Core) 
link_directories (${VERSE_CORE_BINARY_DIR}/modules/Events) 
link_directories (${VERSE_CORE_BINARY_DIR}/modules/UI) 
link_directories (${VERSE_CORE_BINARY_DIR}/modules/Devices) 

# Add executable called "xxxDemo" that is built from the source files 
add_executable (eventDemo eventDemo.cpp) 
add_executable (appDemo appDemo.cpp) 

# Link the executable to the Hello library. 
target_link_libraries (eventDemo VerseCore VerseEvents) 
target_link_libraries (appDemo  ${FREETYPE_LIBRARY} ${GLUT_LIBRARY} ${OPENGL_LIBRARY} ${OpenCV_LIBS} VerseCore VerseEvents VerseUI VerseDevices) 
