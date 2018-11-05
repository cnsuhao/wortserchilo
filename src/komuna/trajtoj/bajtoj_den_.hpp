#ifndef KOMUNA_SPECO_NORME_HAVAS_GRANDON_HPP
#define KOMUNA_SPECO_NORME_HAVAS_GRANDON_HPP

#include "numero.hpp"

#define bajtoj_den_(Speco, grando) \
tuj_premisu(bajtojDen<Speco> == (grando) aŭ ne ĉuNaturajSpecojHavasNormajnValorojn, \
            "La grando de "#Speco" malĝustas, ĝi devas esti "#grando" bajtojn.")

#endif //KOMUNA_SPECO_NORME_HAVAS_GRANDON_HPP
