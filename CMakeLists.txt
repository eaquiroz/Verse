cmake_minimum_required (VERSION 2.6) 

PROJECT(VERSE_CORE)

# Opencv Package
FIND_PACKAGE( OpenCV REQUIRED )
IF (${OpenCV_VERSION} VERSION_LESS 2.3.0)
	MESSAGE(FATAL_ERROR "OpenCV version is not compatible : ${OpenCV_VERSION}")
ENDIF()

# OpenGL Package
FIND_PACKAGE( OpenGL REQUIRED )

# FreeType Package
FIND_PACKAGE( Freetype REQUIRED )

# LibXML Package
FIND_PACKAGE( LIBXML2 )

#Libdecodeqr variables
set(QR_LIBRARY libqrdecode)
set(QR_INCLUDE ${VERSE_CORE_SOURCE_DIR}/3rdparty/libdecodeqr/include)

include_directories( 
	${OpenGL_INCLUDE_DIR}
	${OpenCV_INCLUDE_DIR}
	${FREETYPE_INCLUDE_DIR_freetype2}
	${FREETYPE_INCLUDE_DIR_ft2build}
        ${LIBXML2_INCLUDE_DIR}
	${QR_INCLUDE}
)

#Process folders
add_subdirectory(3rdparty)
add_subdirectory(modules)
add_subdirectory(samples)
