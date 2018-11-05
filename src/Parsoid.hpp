#ifndef VIKIVORTARO_KONVERTANTO_PARSOID_HPP
#define VIKIVORTARO_KONVERTANTO_PARSOID_HPP

#include "komuna/Texto.hpp"
#include "komuna/Paro.hpp"

class Parsoid
{
public:
    Parsoid() { pravalorizuEsprimojn(); }
    Texto konvertuWikitextonAlHtml(Texto servilo, Texto wikitexto,
            Texto nomoDePaĝo, Buleo ĉuDevasNormigi = veran);
private:
    Nenio pravalorizuEsprimojn();
    Listo<Paro<std::regex, Texto>> esprimoj;
};

#endif //VIKIVORTARO_KONVERTANTO_PARSOID_HPP
