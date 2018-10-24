#ifndef KOMUNA_NUMERO_HPP
#define KOMUNA_NUMERO_HPP

#include "../esperanta_traduko.hpp"
#include "../konstantoj.hpp"
#include "specoj.hpp"

//-«
template<class K> constexpr Buleo ĉu_estas_ℚ_krom_ℤ = std::is_floating_point<K>::value;
template<class K> constexpr Buleo ĉu_estas_ℤ = std::is_integral<K>::value;
template<class K> constexpr Buleo ĉu_estas_ℕ = ĉu_estas_ℤ<K> kaj std::is_unsigned<K>::value;
template <class K> constexpr K maximumDe = std::numeric_limits<K>::max();
template <class K> constexpr K minimumDe = std::numeric_limits<K>::lowest();
//»-

typedef unsigned long long ℕ64b;
typedef unsigned int ℕ32b;
typedef unsigned short ℕ16b;
typedef unsigned char ℕ8b;
typedef signed long long ℤ64b;
typedef signed int ℤ32b;
typedef signed short ℤ16b;
typedef signed char ℤ8b;

tuj_premisu(bitojDen<ℕ64b> == 64);
tuj_premisu(bitojDen<ℕ32b> == 32);
tuj_premisu(bitojDen<ℕ16b> == 16);
tuj_premisu(bitojDen<ℕ8b> == 8);
tuj_premisu(bitojDen<ℤ64b> == 64);
tuj_premisu(bitojDen<ℤ32b> == 32);
tuj_premisu(bitojDen<ℤ16b> == 16);
tuj_premisu(bitojDen<ℤ8b> == 8);

typedef ℕ64b ℕ8;
typedef ℕ32b ℕ4;
typedef ℕ16b ℕ2;
typedef ℕ8b ℕ1;

tuj_premisu(bajtojDen<ℕ8> == 8);
tuj_premisu(bajtojDen<ℕ4> == 4);
tuj_premisu(bajtojDen<ℕ2> == 2);
tuj_premisu(bajtojDen<ℕ1> == 1);

typedef long long ℤ8;

tuj_premisu(bajtojDen<ℤ8> == 8);

typedef double ℚ8;
typedef float ℚ4;

tuj_premisu(bajtojDen<ℚ8> == 8);
tuj_premisu(bajtojDen<ℚ4> == 4);

#endif //KOMUNA_NUMERO_HPP
