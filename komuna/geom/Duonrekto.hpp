#ifndef KOMUNA_DUONREKTO_HPP
#define KOMUNA_DUONREKTO_HPP

#include "Vektor.hpp"
#include "../Paro.hpp"

template<class K>
class Duonrekto
{
public:
    Duonrekto() : p(nulvektor<K>), d({1, 0, 0}) {}
    Duonrekto(Vektor<K> p, Vektor<K> d) : p(p), d(d) { premisu (d != nulvektor<K>); }
    
    std::array<Vektor<K>, 2> plejProksimajnPunktojn(const Duonrekto<K>& alia) const
    {
        tuj_premisu(ĉu_estas_ℚ_krom_ℤ<K>);
        // Copyright 2001 softSurfer, 2012 Dan Sunday
        // This code may be freely used, distributed and modified for any purpose
        // providing that this copyright notice is included with it.
        // SoftSurfer makes no warranty for this code, and cannot be held
        // liable for any real or imagined damage resulting from its use.
        // Users of this code must verify correctness for their application.
        
        Vektor<K> u = d;
        Vektor<K> v = alia.d;
        Vektor<K> w = p - alia.p;
        K a = u.skalaranProduton(u);
        K b = u.skalaranProduton(v);
        K c = v.skalaranProduton(v);
        K d = u.skalaranProduton(w);
        K e = v.skalaranProduton(w);
        K D = a * c - b * b;
        K sc, sN, sD = D;
        K tc, tN, tD = D;
        
        if (D == 0)
        {
            sN = 0.0;
            sD = 1.0;
            tN = e;
            tD = c;
        }
        else
        {
            sN = (b * e - c * d);
            tN = (a * e - b * d);
            
            if (sN < 0.0)
            {
                sN = 0.0;
                tN = e;
                tD = c;
            }
        }
        
        if (tN < 0.0)
        {
            tN = 0.0;
            
            if (-d < 0.0)
                sN = 0.0;
            else if (-d > a)
                sN = sD;
            else
            {
                sN = -d;
                sD = a;
            }
        }
        
        sc = (sN == 0) ? 0.0 : (sN / sD);
        tc = (tN == 0) ? 0.0 : (tN / tD);
        
        eligu {p + sc * u, alia.p + tc * v};
    };
    
    Vektor<K> p;
    Vektor<K> d;
};

#endif //KOMUNA_DUONREKTO_HPP
