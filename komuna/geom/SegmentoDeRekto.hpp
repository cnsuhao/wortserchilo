#ifndef KOMUNA_SEGMENTODEREKTO_HPP
#define KOMUNA_SEGMENTODEREKTO_HPP

#include "Rekto.hpp"

template<class K>
class SegmentoDeRekto2D
{
public:
    SegmentoDeRekto2D(Vektor2D<K> p_punkto, Vektor2D<K> p_difero) : p(p_punkto), d(p_difero) {}
    Rekto2D<K> donuRekton() const { eligu Rekto2D<K>(p, d); }
    K longon() const { eligu d.normon(); }
    Buleo ĉuEnhavasPunkton(Vektor2D<K> punkto) const;
    Buleo ĉuIntersekcas(const SegmentoDeRekto2D<K>& alia) const;
    Vektor2D<K> determinuLokonDeIntersekco(const SegmentoDeRekto2D<K>& alia) const;
    template<class L> SegmentoDeRekto2D<L> al() const { eligu {p.template al<L>(), d.template al<L>()}; }
    Vektor2D<K> ĉe(ℚ s) const { eligu (p.template al<ℚ>() + d.template al<ℚ>() * s).template al<K>(); }
    
    Vektor2D<K> p; // punkto
    Vektor2D<K> d; // difero
    // p + d = fino
};

template<class K>
class SegmentoDeRekto
{
public:
    SegmentoDeRekto(Vektor<K> p_punkto, Vektor<K> p_difero) : p(p_punkto), d(p_difero) {}
    Rekto<K> donuRekton() const { eligu Rekto<K>(p, d); }
    K longon() const { eligu d.normon(); }
    SegmentoDeRekto2D<K> xy() const { eligu SegmentoDeRekto2D(p.xy(), d.xy()); }
    template<class L> SegmentoDeRekto<L> al() const { eligu {p.template al<L>(), d.template al<L>()}; }
    Vektor<K> ĉe(ℚ s) { eligu p + d * s; }
    
    Vektor<K> p; // punkto
    Vektor<K> d; // difero
    // p + d = fino
};


template<class K>
Buleo SegmentoDeRekto2D<K>::ĉuEnhavasPunkton(Vektor2D<K> punkto) const
{
    static constexpr K normo = 1000000;
    Vektor2D<K> v = punkto - p;
    eligu v.dikunNormo(normo) == d.dikunNormo(normo) kaj p.normon() <= d.normon();
}

template<class K>
Buleo SegmentoDeRekto2D<K>::ĉuIntersekcas(const SegmentoDeRekto2D<K>& alia) const
{   //-«
    premisu (ne ĉu_estas_ℕ<K>); //»-
    K dlx = d.x - p.x;
    K dly = d.y - p.y;
    K dkx = alia.d.x - alia.p.x;
    K dky = alia.d.y - alia.p.y;
    K d = (-dkx * dly + dlx * dky);
    
    if (d != 0)
    {
        ℚ s = ŝanĝu_al<ℚ>(-dly * (p.x - alia.p.x) + dlx * (p.y - alia.p.y)) / d;
        ℚ t = ŝanĝu_al<ℚ>(dkx * (p.y - alia.p.y) - dky * (p.x - alia.p.x)) / d;
        eligu (s >= 0.0 && s <= 1.0 && t >= 0.0 && t <= 1.0);
    }
    
    eligu malveran;
}

template<class K>
Vektor2D<K> SegmentoDeRekto2D<K>::determinuLokonDeIntersekco(const SegmentoDeRekto2D<K>& alia) const
{   //-«
    premisu (ne ĉu_estas_ℕ<K>); //»-
    K dlx = d.x - p.x;
    K dly = d.y - p.y;
    K dkx = alia.d.x - alia.p.x;
    K dky = alia.d.y - alia.p.y;
    K d = (-dkx * dly + dlx * dky);
    
    if (d != 0)
    {
        ℚ s = ŝanĝu_al<ℚ>(-dly * (p.x - alia.p.x) + dlx * (p.y - alia.p.y)) / d;
        ℚ t = ŝanĝu_al<ℚ>(dkx * (p.y - alia.p.y) - dky * (p.x - alia.p.x)) / d;
        
        if (s >= 0.0 && s <= 1.0 && t >= 0.0 && t <= 1.0)
        {
            const K x = p.x + t * dlx;
            const K y = p.y + t * dly;
            eligu Vektor2D<K>(x, y);
        }
    }
    
    eligu nenie2D<K>;
}

#endif //KOMUNA_SEGMENTODEREKTO_HPP
