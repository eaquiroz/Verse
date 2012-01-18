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


include_directories( 
	${OpenGL_INCLUDE_DIR}
	${OpenCV_INCLUDE_DIR}
	${FREETYPE_INCLUDE_DIR_freetype2}
	${FREETYPE_INCLUDE_DIR_ft2build}
)

#Process folders
add_subdirectory(modules)

add_subdirectory(samples)
