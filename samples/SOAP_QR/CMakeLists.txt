cmake_minimum_required (VERSION 2.6) 

SET(Gsoap_INCLUDE_DIR ${VERSE_API_SOURCE_DIR}/3rdparty/gsoap )

SET(soapDemo_srcs 
	soapDemo.cpp 
	soapC.cpp 
	soapProductsControllerBindingProxy.cpp 
	${Gsoap_INCLUDE_DIR}/stdsoap2.cpp
)

include_directories( 
    ${Gsoap_INCLUDE_DIR}
)

add_executable( soapDemo ${soapDemo_srcs} ${Gsoap_INCLUDE_DIR}/stdsoap2.cpp )
target_link_libraries (soapDemo curl  ${FREETYPE_LIBRARY} ${GLUT_LIBRARY} ${OPENGL_LIBRARY} ${OpenCV_LIBS} ${QR_LIBRARY} VerseCore VerseUI VerseDevices VerseUtils  VerseAR  VerseEvents ${LIBXML2_LIBRARIES} ) 
