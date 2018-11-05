#ifndef KOMUNA_SPECOJ_HPP
#define KOMUNA_SPECOJ_HPP

#include <type_traits>
#include "../konstantoj.hpp"
#include "../esperanta_traduko.hpp"

template<class K> constexpr ℕ bajtojDen = sizeof(K);
template<class K> constexpr ℕ bitojDen = grando_de_bajto * bajtojDen<K>;
template<class K, class L> constexpr Buleo ĉu_specoj_samas = std::is_same<K, L>::value; //-«
template<class K, class L> K ŝanĝu_al(const L x) { eligu static_cast<K>(x); } //»-
template<Buleo B, class K> using uzu_se_ = typename std::enable_if<B, K>::type;
template<class K, class L> constexpr Buleo ĉu_povas_ŝanĝi_al = std::is_convertible<L, K>::value;
template<class K, class L> constexpr Buleo ĉu_estas_subklason_de = std::is_base_of<L, K>::value; //-«
template<class K> typename std::add_rvalue_reference<K>::type malveraEkzemploDe() { eligu std::declval<K>(); } //»-
template<Buleo b, class K, class L> using unua_speco_se_ = typename std::conditional<b, K, L>::type;

#define UZU_SE_(K, x...) template <class P1 = K, class _Z = typename std::enable_if<x>::type>

template<class, template<class...> class> constexpr Buleo ĉu_estas_specialigiton = malveran;
template<template<class...> class K, class... Ks> constexpr Buleo ĉu_estas_specialigiton<K<Ks...>, K> = veran;

namespace ________specoj_test__________ { //-«
template <class K> struct __Test { K k; };
tuj_premisu(ĉu_estas_specialigiton<__Test<ℕ>, __Test>);
tuj_premisu(ne ĉu_estas_specialigiton<ℕ, __Test>);
} //»-

#endif //KOMUNA_SPECOJ_HPP
