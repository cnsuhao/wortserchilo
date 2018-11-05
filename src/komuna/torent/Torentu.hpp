#ifndef KOMUNA_TORENTU_HPP
#define KOMUNA_TORENTU_HPP

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/unique_ptr.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/export.hpp>
#include "../esperanta_traduko.hpp"

using KonvertantoDelTexto = boost::archive::text_iarchive;
using KonvertantoDalTexto = boost::archive::text_oarchive;

#ifdef BOOST_NO_IS_ABSTRACT
#error "Vi devos alvoki BOOST_SERIALIZATION_ASSUME_ABSTRACT por ĉiu abstrakta bazklaso, \
mi mem ne faris ĝin ĉar mi estas iome-pigran. Forprenu ĉi-mesaĝon post kiam vi finis fari ĝin."
#endif

// uzu TORENTU aŭ ambaŭ TORENTU_AL kaj TORENTU_EL

// por uzi en klaso
#define TORENTU \
friend class boost::serialization::access; \
template<class __Torento> inline Nenio serialize(__Torento& torento, ℕ legataVersio)

// por uzi exter klaso, ekzemple TORENTU_(Io& io) { torento & io.larĝo; }
#define TORENTU_(x...) \
friend class boost::serialization::access; \
template<class __Torento> Nenio serialize(__Torento& torento, x, ℕ legataVersio)


#define AL_TORENTO \
friend class boost::serialization::access; \
BOOST_SERIALIZATION_SPLIT_MEMBER() \
template<class __Torento> inline Nenio save(__Torento& torento, ℕ) const

#define EL_TORENTO template<class __Torento> inline Nenio load(__Torento& torento, ℕ legataVersio)


// Por malsimile trakti malsimilajn versiojn de klasoj. Versio devas esti ℕ8b.
#define AGORDU_VERSION_DE(Klaso, versio) BOOST_CLASS_VERSION(Klaso, versio)

#define REGISTRU_SUBKLASON(Klaso) BOOST_CLASS_EXPORT(Klaso)

#endif //KOMUNA_TORENTU_HPP
