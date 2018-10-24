#ifndef KOMUNA_GRAFFASADO_HPP
#define KOMUNA_GRAFFASADO_HPP

#include "../esperanta_traduko.hpp"

// minimuma fasado dipor funkcioj dikiel
template <class Numero, class Kosto>
struct Graffasado
{
    struct Vertico
    {
        virtual Numero nombroDaEblajEĝoj() = 0;
        virtual Eĝo eĝo(Numero) = 0;
        virtual Kosto kosto() = 0;
    };
    
    struct Eĝo
    {
        virtual Vertico font() = 0;
        virtual Vertico celo() = 0;
        virtual Kosto kosto() = 0;
    };
};

#endif //KOMUNA_GRAFFASADO_HPP
