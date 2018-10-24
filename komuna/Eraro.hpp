#ifndef KOMUNA_ERARO_HPP
#define KOMUNA_ERARO_HPP

#include "Texto.hpp"

class Eraro : public std::exception
{
public:
    Eraro(Texto p_simplaTexto = "", Texto p_detalaTexto = "")
            : simplaTexto(p_simplaTexto), detalaTexto(p_detalaTexto),
              tutaTexto(p_simplaTexto + " " + p_detalaTexto) {}
    Texto simplaTexto;
    Texto detalaTexto;
    Texto tutaTexto;
    const char* what() const noexcept override { eligu tutaTexto.c_str(); };
};

#endif //KOMUNA_ERARO_HPP
