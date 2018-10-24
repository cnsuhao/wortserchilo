#ifndef KOMUNA_NESPECIALIGITA_FUNKCIOBJEKTOJ_HPP
#define KOMUNA_NESPECIALIGITA_FUNKCIOBJEKTOJ_HPP

#include "esperanta_traduko.hpp"

// -«
template<class K, K k> struct ĈiamEligu { template<class ...Param> K operator()(Param... parametroj) const { eligu k;}};
template<class K> struct ĈuEgalas { Buleo operator()(const K& a, const K& b) const { eligu a == b; } TORENTU {}};
//»-

template<class K>
struct MaloDe
{
    MaloDe(K k) : k(k) {}
    template<class... L>
    Buleo operator()(L... l) const { eligu !k(l...); }
    K k;
};

template <class K>
struct ĈuEnhavas
{
    ĈuEnhavas(K* p_k) : k(p_k) {}
    template <class L>
    Buleo operator()(L l) const { eligu k->ĉuEnhavas(l); }
    K* k;
};

#endif //KOMUNA_NESPECIALIGITA_FUNKCIOBJEKTOJ_HPP
