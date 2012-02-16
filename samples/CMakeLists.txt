#Other libraries to use into samples
find_package(GLUT)

# Make sure the compiler can find include files from our Hello library. 
include_directories (${VERSE_API_SOURCE_DIR}/modules)

IF (NOT LIBXML2_FOUND AND NOT APPLE)
	include_directories (${VERSE_API_SOURCE_DIR}/3rdparty/libxml2/include)
	link_directories (${VERSE_API_SOURCE_DIR}/3rdparty/libxml2)
        set (LIBXML2_LIBRARIES xml2)
ENDIF (NOT LIBXML2_FOUND AND NOT APPLE)

IF (APPLE)
    set (LIBXML2_LIBRARIES xml2)
ENDIF (APPLE)

# Make sure the linker can find the Hello library once it is built. 
link_directories (
	${VERSE_API_BINARY_DIR}/3rdparty/libdecodeqr
	${VERSE_API_BINARY_DIR}/modules/Core
	${VERSE_API_BINARY_DIR}/modules/Events
	${VERSE_API_BINARY_DIR}/modules/UI
	${VERSE_API_BINARY_DIR}/modules/Devices
	${VERSE_API_BINARY_DIR}/modules/Utils
	${VERSE_API_BINARY_DIR}/modules/AR
        ${VERSE_API_BINARY_DIR}/3rdparty/assimp/code
) 

# Add executable called "xxxDemo" that is built from the source files 
add_executable (eventDemo eventDemo.cpp) 
add_executable (appDemo appDemo.cpp) 
add_executable (menuDemo Menu_and_QR/menuDemo.cpp) 
add_executable (card3dmodelDemo Card_3DModel/card3dmodel.cpp) 

# Link the executable to the Hello library. 
target_link_libraries (eventDemo VerseCore VerseEvents) 
target_link_libraries (appDemo  ${FREETYPE_LIBRARY} ${GLUT_LIBRARY} ${OPENGL_LIBRARY} ${OpenCV_LIBS} VerseCore VerseEvents VerseUI VerseDevices) 
target_link_libraries (menuDemo  ${FREETYPE_LIBRARY} ${GLUT_LIBRARY} ${OPENGL_LIBRARY} ${OpenCV_LIBS} ${QR_LIBRARY} VerseCore VerseUI VerseDevices VerseUtils  VerseAR  VerseEvents ${LIBXML2_LIBRARIES} ) 
target_link_libraries (card3dmodelDemo  ${FREETYPE_LIBRARY} ${GLUT_LIBRARY} ${OPENGL_LIBRARY} ${OpenCV_LIBS} ${QR_LIBRARY} VerseCore VerseUI VerseDevices VerseUtils  VerseAR  VerseEvents ${LIBXML2_LIBRARIES} ${ASSIMP_LIBRARY} ${ARUCO_LIBRARY}) 
