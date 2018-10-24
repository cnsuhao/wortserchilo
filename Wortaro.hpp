#ifndef WORTSERCXILO_WORTARO_HPP
#define WORTSERCXILO_WORTARO_HPP

#include "komuna/Texto.hpp"
#include "komuna/PropraAdres.hpp"
#include "symspell/symspell.h"

class Wortaro
{
public:
    virtual ~Wortaro() = default;
    virtual SymSpell kreuSugestanton() = 0;
    virtual Texto donuHtmlDifinonDe(const Texto& worto) const = 0;
    virtual Nenio agorduRetejonDeParsoid(const Texto& retejo) {};
};

#endif //WORTSERCXILO_WORTARO_HPP
