add_subdirectory(libdecodeqr)
IF (NOT LIBXML2_FOUND AND NOT APPLE)
    add_subdirectory(libxml2)
ENDIF (NOT LIBXML2_FOUND AND NOT APPLE)
