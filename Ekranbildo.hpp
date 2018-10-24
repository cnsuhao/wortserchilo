#ifndef WORTSERCXILO_EKRANBILDO_HPP
#define WORTSERCXILO_EKRANBILDO_HPP

#include <filesystem>
#include "komuna/Texto.hpp"
#include "komuna/Eraro.hpp"
#include "komuna/alTexto.hpp"
#include "komuna/geom/Ortangelo.hpp"

inline Buleo provuKreiBildonDeEkrano(const Texto& celdosiero, Ortangelo<ℤ> ortangelo)
{
    if (celdosiero.ĉuEnhavas('"'))
        throw Eraro("«" + celdosiero + "» ne estas permesitan dosiernomon.");
    if (std::filesystem::exists(celdosiero.STL()))
        throw Eraro("Dosiero «" + celdosiero + "» jam existas.");
#ifdef __linux__
    Texto komando = "import -silent -window root -crop " + alTexto(ortangelo.l) + "x" + alTexto(ortangelo.a) + "+" +
                    alTexto(ortangelo.x) + "+" + alTexto(ortangelo.y) + " png:\"" + celdosiero + "\"";
    system(komando.c_str());
#else
#error Mi ne realigis provuKreiBildonDeEkrano por via platformo.
#endif
    eligu std::filesystem::exists(celdosiero.STL());
}

#endif //WORTSERCXILO_EKRANBILDO_HPP
