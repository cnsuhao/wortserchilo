#ifndef KOMUNA_ĈU_ENHAVAS_IUN_FUNKCION_HPP
#define KOMUNA_ĈU_ENHAVAS_IUN_FUNKCION_HPP

#include "../esperanta_traduko.hpp"

#define __KREU_SJABLONA_ĉu_enhavas_(nomo, sjablona_param, param...) \
struct ĈuEnhavas_##nomo { \
template<class __K> static constexpr decltype(std::declval<__K>().template nomo<sjablona_param>(param), Buleo()) \
                                         ĉu_enhavas_##nomo(ℕ)   { eligu veran;    } \
template<class __K> static constexpr Buleo ĉu_enhavas_##nomo(...) { eligu malveran; } \
};

#define KREU_SJABLONA_ĉu_enhavas_(nomo, sjablona_param, param...) \
__KREU_SJABLONA_ĉu_enhavas_(nomo, sjablona_param, param) \
template<class __K> static constexpr Buleo ĉu_enhavas_##nomo = ĈuEnhavas_##nomo::ĉu_enhavas_##nomo<__K>(0)



#define __KREU_KRAMPAJ_ĉu_enhavas_(nomo, param...) \
struct ĈuEnhavas_##nomo { \
template<class __K> static constexpr decltype(std::declval<__K>()(param), Buleo()) \
                                         ĉu_enhavas_(ℕ)   { eligu veran;    } \
template<class __K> static constexpr Buleo ĉu_enhavas_(...) { eligu malveran; } \
};

#define KREU_KRAMPAJ_ĉu_enhavas_(nomo, param...) \
__KREU_KRAMPAJ_ĉu_enhavas_(nomo, param) \
template<class __K> static constexpr Buleo ĉu_enhavas_##nomo = ĈuEnhavas_##nomo::template ĉu_enhavas_<__K>(0)

#endif //KOMUNA_ĈU_ENHAVAS_IUN_FUNKCION_HPP
