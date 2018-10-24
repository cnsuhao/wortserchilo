#ifndef KOMUNA_ALDONAĴOJALYAML_HPP
#define KOMUNA_ALDONAĴOJALYAML_HPP

#include <yaml-cpp/yaml.h>

#include <fstream>
#include "../trajtoj/numero.hpp"
#include "../geom/Vektor.hpp"
#include "../geom/Ortangelo.hpp"
#include "../Eraro.hpp"

inline Ortangelo<ℤ> kreuOrtangelon(const YAML::Node& nodo)
{
    premisu (nodo.IsSequence());
    premisu(nodo.size() == 4);
    eligu Ortangelo<ℤ>(nodo[0].as<ℤ>(), nodo[1].as<ℤ>(), nodo[2].as<ℤ>(), nodo[3].as<ℤ>());
}

template<ℕ n>
inline std::array<Ortangelo<ℤ>, n> kreuOrtangelojn(const YAML::Node& nodo)
{
    premisu (nodo.IsSequence());
    premisu (nodo.size() == n);
    
    std::array<Ortangelo<ℤ>, n> eligo;
    
    for (ℕ i = 0; i < n; i++)
        eligo[i] = kreuOrtangelon(nodo[i]);
    
    eligu eligo;
};

inline Vektor2D<ℤ> kreuKoordinaton(const YAML::Node& nodo)
{
    premisu(nodo.IsSequence());
    premisu(nodo.size() == 2);
    eligu Vektor2D<ℤ>(nodo[0].as<ℤ>(), nodo[1].as<ℤ>());
}

template<class K>
K kreuZononKunDelokiĝo(const YAML::Node& nodo)
{
    K t;
    
    if (nodo.IsMap())
    {
        premisu(nodo["zono"].IsDefined());
        premisu(nodo["delokiĝo"].IsDefined());
        t.zono = kreuOrtangelon(nodo["zono"]);
        t.delokiĝo = kreuKoordinaton(nodo["delokiĝo"]);
    }
    else
    {
        t.zono = kreuOrtangelon(nodo);
        t.delokiĝo = Vektor2D<ℤ>(0, 0);
    }
    
    eligu t;
}

inline Nenio konservu(const YAML::Node& ĉefnodo, const Texto dosier)
{
    try
    {
        std::ofstream eligo;
        eligo.exceptions(eligo.badbit | eligo.failbit);
        eligo.open(dosier.STL(), eligo.out | eligo.binary);
        eligo << ĉefnodo;
    }
    catch (std::ofstream::failure& eraro)
    {
        throw Eraro("ne povis konservi YAML-dosieron «" + dosier + "»", // -«
                    "Verŝajne la dosier simple ne ekzistas. "
                    "Bedaŭrinde ni nur ricevas ĉi-tiun nehelpeman informon: " + Texto(eraro.what())); //»-
    }
    catch (YAML::Exception& eraro)
    {
        throw Eraro("ne povis konservi YAML-dosieron «" + dosier + "»", "YAML plendas: " + Texto(eraro.what()));
    }
}

#endif //KOMUNA_ALDONAĴOJALYAML_HPP
