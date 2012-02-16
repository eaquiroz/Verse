MESSAGE( STATUS "-------------------------------------------------------------------------------" )
MESSAGE( STATUS "3RD AUXILIAR LIBRARIES" )
MESSAGE( STATUS "-------------------------------------------------------------------------------" )

MESSAGE( STATUS "Assimp Library" )
MESSAGE( STATUS "********************************" )
add_subdirectory(assimp)

MESSAGE( STATUS "QR decode Library" )
MESSAGE( STATUS "********************************" )
add_subdirectory(libdecodeqr)

MESSAGE( STATUS "Aruco" )
MESSAGE( STATUS "********************************" )
add_subdirectory(aruco)

IF (NOT LIBXML2_FOUND AND NOT APPLE)
    MESSAGE( STATUS "Lib XML 2" )
    MESSAGE( STATUS "********************************" )
    add_subdirectory(libxml2)
ENDIF (NOT LIBXML2_FOUND AND NOT APPLE)
