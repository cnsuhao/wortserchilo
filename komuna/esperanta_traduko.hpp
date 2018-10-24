#ifndef KOMUNA_ESPERANTA_TRADUKO_HPP
#define KOMUNA_ESPERANTA_TRADUKO_HPP

#include <limits>
#include <type_traits>
#include <cassert>

#define ℤ int
#define ℕ unsigned int
#define ℚ double

#define ne not
#define kaj and
#define aŭ or

#define veran true
#define malveran false

#define saltu_al goto
#define saltu_al_sekva continue
#define eksaltu break
#define eligu return

#ifdef ndebug
#define kraŝu {}
#define kraŝu_(msg...) {}
#else
#define kraŝu abort()
#define kraŝu_ĉar(msg...) { std::cerr << msg << std::endl; abort(); }
#endif
#define KlasoDe(x...) decltype(x)
#define KlasoDeRef(x...) std::decay_t<KlasoDe(x)>
#define KlasoDeAdres(x...) KlasoDeRef(*(x))
#define premisu(x...) assert(x)
#define tuj_premisu(x...) static_assert(x)
#define formovu(x...) std::move(x)
#define maximumDe(x...) std::numeric_limits<KlasoDe(x)>::max()
#define minimumDe(x...) std::numeric_limits<KlasoDe(x)>::lowest()
#define kreu new

#define Buleo bool
#define Nenio void

#endif //KOMUNA_ESPERANTA_TRADUKO_HPP
