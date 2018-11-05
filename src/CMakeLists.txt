cmake_minimum_required(VERSION 3.9)
project(Wortserchilo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")

# Mi ne scias kiel oni faras bonan CMake dosieron do ĉi-tio verŝajne estas iom aĉan.

#set(Tesseract_DIR "" CACHE PATH "La CMake dosierujo de Tesseract.")
set(Tesseract_INCLUDE_DIRS "" CACHE PATH "La dosierujo de la kapoj de Tesseract.")
set(Tesseract_LIBRARIES "tesseract" CACHE FILEPATH "La binara funkciaro de Tesseract.")
set(Leptonica_INCLUDE_DIRS "/usr/include/leptonica" CACHE PATH "La dosierujo de la kapoj de Leptonica.")
set(Leptonica_LIBRARIES "lept" CACHE FILEPATH "La binara funkciaro de Leptonica.")
set(UGlobalHotkey_INCLUDE_DIRS "" CACHE PATH "La dosierujo de la kapoj de UGlobalHotkey.")
set(UGlobalHotkey_LIBRARIES "UGlobalHotkey" CACHE FILEPATH "La binara funkciaro de UGlobalHotkey.")
set(zipios++_INCLUDE_DIRS "" CACHE PATH "La dosierujo de la kapoj de ZipIOS++.")
set(zipios++_LIBRARIES "zipios" CACHE FILEPATH "La binara funkciaro de ZipIOS++.")
set(curl++_INCLUDE_DIRS "" CACHE PATH "La dosierujo de la kapoj de curl++.")
set(curl++_LIBRARIES "curlpp" CACHE FILEPATH "La binara funkciaro de curl++.")

set(CMAKE_AUTOMOC ON)

find_package(Boost 1.62 COMPONENTS serialization iostreams system unit_test_framework REQUIRED)
#find_package(Tesseract 4.0 REQUIRED)
find_package(yaml-cpp 0.5 REQUIRED)
#find_package(leptonica REQUIRED)
find_package(Qt5Widgets REQUIRED)
#find_package(zipios++ REQUIRED)
find_package(ICU 60 COMPONENTS uc i18n)
find_package(CURL)
find_package(Threads)

set(FUNKCIAROJ ${Boost_LIBRARIES} ${YAML_CPP_LIBRARIES} ${Tesseract_LIBRARIES} ${Leptonica_LIBRARIES}
        ${Qt5Widgets_LIBRARIES} ${zipios++_LIBRARIES} ${UGlobalHotkey_LIBRARIES} ${ICU_LIBRARIES}
        ${curl++_LIBRARIES} ${CURL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT}
        stdc++fs) # Ĉi-tio verŝajne tute ne funkcios sur Windows komputiloj sed alie mi ne scias kiel mi devas fari ĝin.
include_directories(${Boost_INCLUDE_DIRS} ${YAML_CPP_INCLUDE_DIR} ${Tesseract_INCLUDE_DIRS} ${Leptonica_INCLUDE_DIRS}
        ${Qt5Widgets_INCLUDE_DIRS} ${zipios++_INCLUDE_DIRS} ${UGlobalHotkey_INCLUDE_DIRS} ${ICU_INCLUDE_DIRS}
        ${curl++_INCLUDE_DIRS} ${CURL_INCLUDE_DIRS})

set(ĈU_VOLAS_TRADUKANTON true)
add_compile_definitions(ĈU_UZAS_QT)
add_subdirectory(komuna)

if (ICU_FOUND)
    add_compile_definitions(ĈU_UZAS_ICU_UNICODE)
endif ()

# Ni devas meti datumdosierojn en la meza binara dosiero se ni volas ke la programo bone funkcias kun CLion.
configure_file(stilo.qss ${CMAKE_BINARY_DIR}/stilo.qss COPYONLY)
configure_file(linguoj.png ${CMAKE_BINARY_DIR}/linguoj.png COPYONLY)
configure_file(agordoj.png ${CMAKE_BINARY_DIR}/agordoj.png COPYONLY)
configure_file("linguoj magra.png" "${CMAKE_BINARY_DIR}/linguoj magra.png" COPYONLY)
configure_file("agordoj magra.png" "${CMAKE_BINARY_DIR}/agordoj magra.png" COPYONLY)
configure_file(tradukoj/nld.qm ${CMAKE_BINARY_DIR}/tradukoj/nld.qm COPYONLY)
configure_file(tradukoj/epo.qm ${CMAKE_BINARY_DIR}/tradukoj/epo.qm COPYONLY)
configure_file(tradukoj/eng.qm ${CMAKE_BINARY_DIR}/tradukoj/eng.qm COPYONLY)

install (FILES stilo.qss linguoj.png agordoj.png ../guide_en.md ../guide_eo.md 
         "linguoj magra.png" "agordoj magra.png" DESTINATION .)
install (FILES tradukoj/nld.qm tradukoj/epo.qm tradukoj/eng.qm DESTINATION ./tradukoj)

set(FONTDOSIEROJ
        ${FONTDOSIEROJ}
        Parsoid.cpp
        Parsoid.hpp
        symspell/symspell.h
        Cheffenestro.hpp
        Cheffenestro.cpp
        Wortarestro.hpp
        Wortarestro.cpp
        Wortaro_wikitext1.cpp
        Wortaro_wikitext1.hpp
        Wortserchilo.cpp
        Wortserchilo.hpp
        Wortaro.hpp
        Difino.hpp
        PrenantoDeDifinoj.cpp
        PrenantoDeDifinoj.hpp
        TesseractLeganto.cpp
        TesseractLeganto.hpp
        Ekranbildo.hpp
        LegitaWorto.hpp
        Bildleganto.cpp
        Bildleganto.hpp
        fasado/Difinujo.cpp
        fasado/Difinujo.hpp
        fasado/Rezultujo.cpp
        fasado/Rezultujo.hpp
        fasado/Desegnejo.cpp
        fasado/Desegnejo.hpp
        fasado/Kolorelektejo.cpp
        fasado/Kolorelektejo.hpp
        Kolorfiltrilo.hpp
        Kolorfiltrilo.cpp
        fasado/Kolorlisto.cpp
        fasado/Kolorlisto.hpp
        fasado/SequencoDeAnimacioj.hpp
        fasado/MenuoDeWortaresLinguoj.cpp
        fasado/MenuoDeWortaresLinguoj.hpp
        InformoDeWortaro.hpp
        fasado/MenuoDeAgordoj.cpp
        fasado/MenuoDeAgordoj.hpp
        fasado/MenuoDeBildlegantesLinguoj.cpp
        fasado/MenuoDeBildlegantesLinguoj.hpp
        fasado/AranĝantoKunAnimacioj.cpp
        fasado/AranĝantoKunAnimacioj.hpp
        fasado/komencuAnimacion.hpp)

add_executable(Wortserchilo main.cpp ${FONTDOSIEROJ} montruEraron.hpp)
target_link_libraries(Wortserchilo ${FUNKCIAROJ})

add_executable(Wortserchilo_test test.cpp ${FONTDOSIEROJ} ${TESTDOSIEROJ})
target_link_libraries(Wortserchilo_test ${FUNKCIAROJ})

install(TARGETS Wortserchilo DESTINATION ./)


# CPack
#include(InstallRequiredSystemLibraries)
#
#set(CPACK_PACKAGE_NAME "La Iom Rapida Wortserĉilo")
#set(CPACK_PACKAGE_DESCRIPTION "Bildleganta wortaro.")
#set(CPACK_PACKAGE_VENDOR "Zowie van Dillen")
#set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/guide_en.md")
#set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/license.txt")
#set(CPACK_PACKAGE_VERSION_MAJOR "1")
#set(CPACK_PACKAGE_VERSION_MINOR "0")
#set(CPACK_PACKAGE_VERSION_PATCH "0")
#
# todo RPM, DEB
#set(CPACK_GENERATOR "TGZ;TZ;")
#
#include(CPack)

