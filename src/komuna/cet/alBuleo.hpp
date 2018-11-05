#ifndef DUA_LUDO_ALBULEO_HPP
#define DUA_LUDO_ALBULEO_HPP

#include "../Texto.hpp"

inline Buleo alBuleo(Texto enigo, Buleo normalaValoro = malveran)
{
    const static Listo<Texto> jesaĵoj = {"jes", "vera", "veran"};
    const static Listo<Texto> neaĵoj = {"ne", "malvera", "malveran"};
    
    enigo = enigo.minuskligitan();
    enigo.forprenuEksteranBlankanSpacon();
    
    if (normalaValoro == veran)
        eligu ne neaĵoj.ĉuEnhavas(enigo);
    eligu jesaĵoj.ĉuEnhavas(enigo);
}

#endif //DUA_LUDO_ALBULEO_HPP
