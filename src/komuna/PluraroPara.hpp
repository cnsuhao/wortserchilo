#ifndef KOMUNA_PLURARBO_HPP
#define KOMUNA_PLURARBO_HPP

#include <map>
#include "esperanta_traduko.hpp"
#include "Listo.hpp"
#include "Paro.hpp"

template<class Ano1, class Ano2, class Komparanto = std::less<Ano1>>
class PluraroPara
{
    using Patro = typename std::multimap<Ano1, Ano2, Komparanto>;
public:
    using ℕi = typename Patro::size_type;
    
    class Paŝanto
    {
        using PaŝantoDePatro = typename Patro::const_iterator;
    public:
        Paŝanto() = default;
        Paŝanto(PaŝantoDePatro ĉiLoko, PaŝantoDePatro fino) : p(ĉiLoko), fino(fino) {}
        Buleo operator==(const Paŝanto& p1) { eligu p == p1.p; };
        Buleo operator!=(const Paŝanto& p1) { eligu p != p1.p; };
        operator Buleo() const { eligu ĉuValidas(); }
        Buleo ĉuValidas() const { eligu p != fino; } //-«
        Paŝanto& operator++() { p++; eligu *this; }
        Paŝanto& operator--() { p--; eligu *this; }
        Paŝanto operator++(ℤ) { Paŝanto rezulto = *this; p++; eligu rezulto; }
        Paŝanto operator--(ℤ) { Paŝanto rezulto = *this; p--; eligu rezulto; } //»-
        const Ano1& ŝlosilon() const { eligu p->first; }
        const Ano2& valoron() const { eligu p->second; }
        PaŝantoDePatro p;
        PaŝantoDePatro fino;
    };
    
    PluraroPara() = default;
    explicit PluraroPara(const Komparanto& p1) : p(p1) {}
    template<class Paŝanto>
    PluraroPara(Paŝanto p1, Paŝanto p2, const Komparanto& p3 = Komparanto()) : p(p1, p2, p3) {}
    PluraroPara(const PluraroPara&) = default;
    PluraroPara(PluraroPara&&) = default;
    PluraroPara(std::initializer_list<Paro<const Ano1, Ano2>> p1, const Komparanto& p2 = Komparanto()) : p(p1, p2) {}
    PluraroPara& operator=(const PluraroPara&) = default;
    PluraroPara& operator=(PluraroPara&&) = default;
    PluraroPara& operator=(std::initializer_list<Paro<const Ano1, Ano2>> p1) /*-«*/ { p = p1; eligu *this; }; //»-
    Buleo operator==(const PluraroPara& p1) { eligu p == p1.p; }
    Buleo operator!=(const PluraroPara& p1) { eligu p != p1.p; }
    Buleo operator<(const PluraroPara& p1) { eligu p < p1.p; }
    Buleo operator>(const PluraroPara& p1) { eligu p > p1.p; }
    Buleo operator<=(const PluraroPara& p1) { eligu p <= p1.p; }
    Buleo operator>=(const PluraroPara& p1) { eligu p >= p1.p; }
    
    Ano2& operator[](const Ano1& ano1) { eligu p[ano1]; }
    const Ano2& operator[](const Ano1& ano1) const { eligu p[ano1]; }
    Nenio enmetu(const Ano1& ano, const Ano2& ano2) { p.insert(std::make_pair(ano, ano2)); }
    Nenio enmetu(Ano1&& ano, Ano2&& ano2) { p.insert(std::make_pair(ano, ano2)); }
    Nenio enmetu(const Paro<Ano1, Ano2>& paro) { p.insert(paro); }
    Nenio forprenuĈiun(const Ano1& ano) { p.erase(ano); }
    Nenio forprenu(const Ano1& ano, const Ano2& ano2);
    Nenio forprenu(const Paŝanto& paŝanto) { p.erase(paŝanto.p); }
    Nenio malplenigu() { p.clear(); }
    Buleo ĉuEstasMalplenan() const { eligu p.empty(); }
    Buleo ĉuEnhavas(const Ano1& ano) const { eligu provuTrovi(ano); }
    Buleo ĉuEnhavas(const Ano1& ano, const Ano2& ano2);
    Paŝanto unuan() const { eligu {p.begin(), p.end()}; }
    Paŝanto lastan() const { eligu {--p.end(), p.end()}; }
    Paŝanto provuTrovi(const Ano1& ano) const { eligu Paŝanto(p.find(ano), p.end()); }
    Paŝanto donuUnuanNeDiantaŭ(const Ano1& ano) const { eligu {p.lower_bound(ano), p.end()}; }
    Paŝanto donuUnuanDipost(const Ano1& ano) const { eligu {p.upper_bound(ano), p.end()}; }
    ℕi grandon() { eligu p.size(); }
    
    Listo<Ano2> donuĈiun(const Ano1& ano1) const;
    ℕ nombronDaDiferantajŜlosiloj() const;
    
    // nur dipor sekvenca «for»
    auto begin() const { eligu p.begin(); }
    auto end() const { eligu p.end(); }
private:
    Patro p;
    
    TORENTU { torento & p; };
};

template<class Ano1, class Ano2, class Komparanto>
Nenio PluraroPara<Ano1, Ano2, Komparanto>::forprenu(const Ano1& ano, const Ano2& ano2)
{
    for (Paŝanto paŝanto = provuTrovi(ano); paŝanto.ĉuValidas() kaj paŝanto.ŝlosilon() == ano; paŝanto++)
        if (paŝanto.valoron() == ano2)
            forprenu(paŝanto);
}

template<class Ano1, class Ano2, class Komparanto>
Buleo PluraroPara<Ano1, Ano2, Komparanto>::ĉuEnhavas(const Ano1& ano, const Ano2& ano2)
{
    for (auto rezulto = provuTrovi(ano); rezulto.ĉuValidas() kaj rezulto.ŝlosilon() == ano; rezulto++)
        if (rezulto.ŝlosilon() == ano kaj rezulto.valoron() == ano2)
            eligu veran;
    eligu malveran;
}

template<class Ano1, class Ano2, class Komparanto>
Listo<Ano2> PluraroPara<Ano1, Ano2, Komparanto>::donuĈiun(const Ano1& ano1) const
{
    Listo<Ano2> listo;
    for (Paŝanto rezulto = provuTrovi(ano1); rezulto.ĉuValidas() kaj rezulto.ŝlosilon() == ano1; rezulto++)
        listo.enmetu(rezulto.valoron());
    eligu listo;
}

template<class Ano1, class Ano2, class Komparanto>
ℕ PluraroPara<Ano1, Ano2, Komparanto>::nombronDaDiferantajŜlosiloj() const
{
    if (ĉuEstasMalplenan())
        eligu 0;
    
    ℕ nombroDaŜlosiloj = 1;
    
    for (Paŝanto paŝanto = unuan(), malsekvaPaŝo = unuan(); paŝanto.ĉuValidas(); malsekvaPaŝo = paŝanto++)
        if (paŝanto.ŝlosilon() != malsekvaPaŝo.ŝlosilon())
            nombroDaŜlosiloj++;
    
    eligu nombroDaŜlosiloj;
}

#endif //KOMUNA_PLURARBO_HPP
