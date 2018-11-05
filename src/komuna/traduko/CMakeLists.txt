set(ujo ${CMAKE_CURRENT_SOURCE_DIR})
configure_file(linguokodoj ${CMAKE_BINARY_DIR}/tradukoj/linguokodoj COPYONLY)
configure_file(iso_639-2.mo ${CMAKE_BINARY_DIR}/test/iso_639-2.mo COPYONLY)
install (FILES linguokodoj DESTINATION ./tradukoj)

set(FONTDOSIEROJ
        ${FONTDOSIEROJ}
        ${ujo}/Linguo.cpp
        ${ujo}/Linguo.hpp
        ${ujo}/PunktMO.cpp
        ${ujo}/PunktMO.hpp
        PARENT_SCOPE)
set(TESTDOSIEROJ
        ${TESTDOSIEROJ}
        ${ujo}/Linguo_test.cpp
        ${ujo}/PunktMO_test.cpp
        PARENT_SCOPE)
