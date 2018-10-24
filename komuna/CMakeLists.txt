
if (ĈU_VOLAS_TRADUKANTON)
    add_subdirectory(traduko)
endif ()


set(ujo ${CMAKE_CURRENT_SOURCE_DIR})
set(FONTDOSIEROJ
        ${FONTDOSIEROJ}
        ${ujo}/cet/aldonojDalYaml.hpp
        ${ujo}/cet/Detruanto.hpp
        ${ujo}/cet/Esprimo.cpp
        ${ujo}/cet/Esprimo.hpp
        ${ujo}/cet/Esprimujo.cpp
        ${ujo}/cet/Esprimujo.hpp
        ${ujo}/cet/FiksitaKomo.hpp
        ${ujo}/cet/Glitkomo.hpp
        ${ujo}/cet/Graffasado.hpp
        ${ujo}/cet/Leganto.cpp
        ${ujo}/cet/Leganto.hpp
        ${ujo}/cet/LegantoDeArgumentoj.cpp
        ${ujo}/cet/LegantoDeArgumentoj.hpp
        ${ujo}/cet/Lokaĵaro.hpp
        ${ujo}/geom/Duonrekto.hpp
        ${ujo}/geom/Ortangelo.hpp
        ${ujo}/geom/Rekto.hpp
        ${ujo}/geom/SegmentoDeRekto.hpp
        ${ujo}/geom/Vektor.hpp
        ${ujo}/komunikad/Promeso.hpp
        ${ujo}/komunikad/Semaforo.hpp
        ${ujo}/torent/IoAjn.hpp
        ${ujo}/torent/TorentaNumero.hpp
        ${ujo}/torent/TorentoObjekta.hpp
        ${ujo}/torent/TorentoTexta.cpp
        ${ujo}/torent/TorentoTexta.hpp
        ${ujo}/torent/Torentu.hpp
        ${ujo}/trajtoj/AlvokoDikunForlaseblajArgumentoj.hpp
        ${ujo}/trajtoj/bajtoj_den_.hpp
        ${ujo}/trajtoj/numero.hpp
        ${ujo}/trajtoj/specoj.hpp
        ${ujo}/trajtoj/ĉu_enhavas_iun_funkcion.hpp
        ${ujo}/trajtoj/ĉu_enhavas_iun_klason.hpp
        ${ujo}/alTexto.hpp
        ${ujo}/DividataAdres.hpp
        ${ujo}/Eraro.hpp
        ${ujo}/esperanta_traduko.hpp
        ${ujo}/konstantoj.hpp
        ${ujo}/funkciobjektoj.hpp
        ${ujo}/Listo.hpp
        ${ujo}/Paro.hpp
        ${ujo}/PluraroPara.hpp
        ${ujo}/PropraAdres.hpp
        ${ujo}/Texto.cpp
        ${ujo}/Texto.hpp
        ${ujo}/Unikaro.hpp
        ${ujo}/UnikaroPara.hpp
        ${ujo}/cet/alBuleo.hpp
        PARENT_SCOPE)
set(TESTDOSIEROJ
        ${TESTDOSIEROJ}
        PARENT_SCOPE)
