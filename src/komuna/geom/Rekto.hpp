#ifndef KOMUNA_REKTO_HPP
#define KOMUNA_REKTO_HPP


#include "Vektor.hpp"
#include "../cet/Glitkomo.hpp"
#include "../Paro.hpp"

template<class K>
class Rekto2D
{
public:
    Rekto2D(Vektor2D<K> p_punkto, Vektor2D<K> p_direkto) : p(p_punkto), d(p_direkto) { premisu (d != nulvektor2D<K>); }
    Buleo ĉuEnhavasPunkton(Vektor2D<K> punkto) const;
    Vektor2D<K> projekciuSurRekto(Vektor2D<K> punkto) const;
    
    Vektor2D<K> p; // punkto
    Vektor2D<K> d; // vektor de direkto
};

template<class K>
class Rekto
{
public:
    Rekto(Vektor<K> p_punkto, Vektor<K> p_direkto) : p(p_punkto), d(p_direkto) { premisu (d != nulvektor<K>); }
    
    Vektor<K> p; // punkto
    Vektor<K> d; // vektor de direkto
};

template<class K>
Buleo Rekto2D<K>::ĉuEnhavasPunkton(Vektor2D<K> punkto) const
{   //-«
    tuj_premisu (ne ĉu_estas_ℕ<K>); //»-
    eligu (punkto.x - p.x) * d.y == (punkto.y - p.y) * d.x;
}

template<class K>
Vektor2D<K> Rekto2D<K>::projekciuSurRekto(Vektor2D<K> punkto) const
{
    tuj_premisu (ĉu_estas_ℚ_krom_ℤ<K>);
    K m = d.y / d.x;
    K b = p.y - (m * p.x);
    Vektor2D<K> rezulto(m * punkto.y + punkto.x - m * b, m * m * punkto.y + m * punkto.x + b);
    eligu rezulto / (m * m + 1);
}

#endif //KOMUNA_REKTO_HPP
