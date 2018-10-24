#ifndef KOMUNA_DETRUANTO_HPP
#define KOMUNA_DETRUANTO_HPP

template<class FaruIon>
class Detruanto
{
public:
    Detruanto(FaruIon faruIon) : ĉuNuligis(malveran), faruIon(faruIon) {};
    ~Detruanto() { if (ne ĉuNuligis) faruIon(); }
    Nenio nuligu() { ĉuNuligis = veran; }
    FaruIon faruIon;
    Buleo ĉuNuligis;
};

#endif //KOMUNA_DETRUANTO_HPP
