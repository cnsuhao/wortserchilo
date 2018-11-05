#ifndef VORTSERCXILO_LINGUO_HPP
#define VORTSERCXILO_LINGUO_HPP

#include "../Texto.hpp"

struct Linguo
{
    Linguo() = default;
    Linguo(Texto kodo) : iso639_3(kodo) {}
    Buleo operator==(const Linguo& alia) const { eligu iso639_3 == alia.iso639_3; }
    Buleo operator!=(const Linguo& alia) const { eligu iso639_3 != alia.iso639_3; }
    // Eligas la anglan worton se ni ne havas la nomon en la volata linguo.
    // Eligas iso639_3 se ni ne konas la linguokodon.
    Texto donuNomon(const Linguo& linguoDeNomo) const;
    Texto provuDoniIso639_2() const; // malplenan se malsukcesas
    Buleo ĉuNiKonasLinguon() const;
    static Linguo provuDoniLinguonDeIso639_2(const Texto& iso639_2); // iso639_3 estas malplenan se ĉi-tio malsukcesas
    Texto iso639_3;
};

const inline Linguo neniu_linguo = Linguo();
const inline Linguo esperanta_linguo = Linguo("epo");
const inline Linguo angla_linguo = Linguo("eng");

#endif //VORTSERCXILO_LINGUO_HPP
