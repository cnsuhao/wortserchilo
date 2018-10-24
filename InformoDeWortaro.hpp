#ifndef WORTSERCXILO_INFORMODELINGUO_HPP
#define WORTSERCXILO_INFORMODELINGUO_HPP

#include "komuna/traduko/Linguo.hpp"

struct InformoDeWortaro
{
    Linguo linguo;
    Linguo linguoDeDifinoj;
    Texto fonto;
    Texto leĝaInformo;
    ℕ nombroDaWortoj;
};

struct InformoDeWortaroj
{
    struct Wortaro
    {
        Linguo linguo;
        ℕ nombroDaWortoj;
    };
    
    struct Grupo
    {
        Texto fonto;
        Texto mallongaNomo;
        Texto leĝaInformo;
        Linguo linguoDeDifinoj;
        Listo<Wortaro> wortaroj;
    
        Wortaro* provuTrovi(const Linguo& linguo);
        const Wortaro* provuTrovi(const Linguo& linguo) const;
    };
    
    Listo<Grupo> grupoj;
    
    Grupo* provuTrovi(const Texto& fonto);
    const Grupo* provuTrovi(const Texto& fonto) const;
    Wortaro* provuTrovi(const Texto& fonto, const Linguo& linguo);
    const Wortaro* provuTrovi(const Texto& fonto, const Linguo& linguo) const;
};

inline InformoDeWortaroj::Wortaro* InformoDeWortaroj::Grupo::provuTrovi(const Linguo& linguo)
{
    auto r = wortaroj.provuTrovi(linguo, [](const Wortaro& w, const Linguo& linguo) { eligu w.linguo == linguo; });
    eligu r.ĉuValidas() ? &*r : nullptr;
}

inline const InformoDeWortaroj::Wortaro* InformoDeWortaroj::Grupo::provuTrovi(const Linguo& linguo) const
{
    auto r = wortaroj.provuTrovi(linguo, [](const Wortaro& w, const Linguo& linguo) { eligu w.linguo == linguo; });
    eligu r.ĉuValidas() ? &*r : nullptr;
}

inline InformoDeWortaroj::Grupo* InformoDeWortaroj::provuTrovi(const Texto& fonto)
{
    auto r = grupoj.provuTrovi(fonto, [](const Grupo& grupo, const Texto& fonto) { eligu grupo.fonto == fonto; });
    eligu r.ĉuValidas() ? &*r : nullptr;
}

inline const InformoDeWortaroj::Grupo* InformoDeWortaroj::provuTrovi(const Texto& fonto) const
{
    auto r = grupoj.provuTrovi(fonto, [](const Grupo& grupo, const Texto& fonto) { eligu grupo.fonto == fonto; });
    eligu r.ĉuValidas() ? &*r : nullptr;
}

inline InformoDeWortaroj::Wortaro* InformoDeWortaroj::provuTrovi(const Texto& fonto, const Linguo& linguo)
{
    Grupo* grupo = provuTrovi(fonto);
    eligu grupo == nullptr ? nullptr : grupo->provuTrovi(linguo);
}

inline const InformoDeWortaroj::Wortaro* InformoDeWortaroj::provuTrovi(const Texto& fonto, const Linguo& linguo) const
{
    const Grupo* grupo = provuTrovi(fonto);
    eligu grupo == nullptr ? nullptr : grupo->provuTrovi(linguo);
}

#endif //WORTSERCXILO_INFORMODELINGUO_HPP
