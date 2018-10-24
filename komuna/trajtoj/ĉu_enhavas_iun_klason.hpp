#ifndef KOMUNA_ĈU_ENHAVAS_IUN_KLASON_HPP
#define KOMUNA_ĈU_ENHAVAS_IUN_KLASON_HPP

#include "../esperanta_traduko.hpp"

#define __KREU_ĉu_enhavas_klason_(nomo) \
struct ĈuEnhavasKlason_##nomo { \
template<class __K> static constexpr decltype(__K::##nomo(), Buleo()) ĉu_enhavas_##nomo(ℕ) { eligu veran; } \
template<class __K> static constexpr Buleo ĉu_enhavas_##nomo(...) { eligu malveran; } \
};

#define KREU_ĉu_enhavas_klason_(nomo) \
__KREU_ĉu_enhavas_klason_(nomo) \
template<class __K> constexpr Buleo ĉu_enhavas_klason_##nomo = ĈuEnhavasKlason_##nomo::ĉu_enhavas_##nomo<__K>(0)


#endif //KOMUNA_ĈU_ENHAVAS_IUN_KLASON_HPP
