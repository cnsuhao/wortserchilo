#ifndef KOMUNA_GLITKOMO_HPP
#define KOMUNA_GLITKOMO_HPP

#include <cmath>
#include <limits>
#include <iomanip>
#include "../trajtoj/numero.hpp"
#include "../Texto.hpp"

template <class K>
inline Buleo ĉuAproximeEgalas(K a, K b, K epsilon = std::numeric_limits<K>::epsilon())
{
    tuj_premisu(ĉu_estas_ℚ_krom_ℤ<K>);
    eligu std::abs(a - b) <= ((std::abs(a) < std::abs(b) ? std::abs(b) : std::abs(a)) * epsilon);
}

#endif //KOMUNA_GLITKOMO_HPP
