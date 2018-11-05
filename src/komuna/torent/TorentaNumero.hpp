#ifndef KOMUNA_KOMPAKTANUMERO_HPP
#define KOMUNA_KOMPAKTANUMERO_HPP

#include "../esperanta_traduko.hpp"
#include "../trajtoj/numero.hpp"
#include "Torentu.hpp"

// ĉi-tio estis pli utilan kiam TabeloTorenta ankoraŭ existis
template<class _Grandaℕ = ℕ4, class _Kompaktaℕ = ℕ8b>
class Kompakta
{
public:
    typedef _Grandaℕ Grandaℕ;
    typedef _Kompaktaℕ Kompaktaℕ;
    tuj_premisu(ĉu_estas_ℕ<Kompaktaℕ>);
    tuj_premisu(ĉu_estas_ℕ<Grandaℕ>);
    tuj_premisu(maximumDe<Kompaktaℕ> < maximumDe<Grandaℕ>);
    
    Kompakta(Grandaℕ p_valoro = 0) : valoro(p_valoro) {}
    operator Grandaℕ() const { eligu valoro; }
    
    AL_TORENTO
    {
        Kompaktaℕ specialaValoro(maximumDe<Kompaktaℕ>);
        Kompaktaℕ kompaktaValoro(valoro);
        Grandaℕ grandaValoro(valoro);
        
        if (valoro < maximumDe<Kompaktaℕ>)
            torento << kompaktaValoro;
        else
            torento << specialaValoro << grandaValoro;
    }
    
    EL_TORENTO
    {
        Kompaktaℕ kompakta;
        torento >> kompakta;
        
        if (kompakta != maximumDe<Kompaktaℕ>)
            valoro = kompakta;
        else
            torento >> valoro;
    }
    
    Grandaℕ valoro;
};

#endif //KOMUNA_KOMPAKTANUMERO_HPP
