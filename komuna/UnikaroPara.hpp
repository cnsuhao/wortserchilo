#ifndef KOMUNA_ARBO_HPP
#define KOMUNA_ARBO_HPP

#include <map>
#include "esperanta_traduko.hpp"
#include "Paro.hpp"
#include "torent/Torentu.hpp"

template<class Ano1, class Ano2, class Komparanto = std::less<Ano1>>
class UnikaroPara
{
    using Patro = typename std::map<Ano1, Ano2, Komparanto>;
public:
    using ℕi = typename Patro::size_type;
    
    class NeŝanĝeblaPaŝanto
    {
        using PaŝantoDePatro = typename Patro::const_iterator;
    public:
        NeŝanĝeblaPaŝanto() = default;
        NeŝanĝeblaPaŝanto(PaŝantoDePatro ĉiLoko, PaŝantoDePatro fino) : p(ĉiLoko), fino(fino) {}
        Buleo operator==(const NeŝanĝeblaPaŝanto& p1) const { eligu p == p1.p; };
        Buleo operator!=(const NeŝanĝeblaPaŝanto& p1) const { eligu p != p1.p; };
        Buleo ĉuValidas() const { eligu p != fino; } //-«
        NeŝanĝeblaPaŝanto& operator++() { p++; eligu *this; }
        NeŝanĝeblaPaŝanto& operator--() { p--; eligu *this; }
        NeŝanĝeblaPaŝanto operator++(ℤ) { NeŝanĝeblaPaŝanto rezulto = *this; p++; eligu rezulto; }
        NeŝanĝeblaPaŝanto operator--(ℤ) { NeŝanĝeblaPaŝanto rezulto = *this; p--; eligu rezulto; } //»-
        const Ano1& ŝlosilon() const { eligu p->first; }
        const Ano2& valoron() const { eligu p->second; }
        //const Paro<Ano1, Ano2>& operator*() const { eligu *p; }
        //const Paro<Ano1, Ano2>* operator->() const { eligu &*p; }
        PaŝantoDePatro p;
        PaŝantoDePatro fino;
    };
    
    class Paŝanto
    {
        using PaŝantoDePatro = typename Patro::iterator;
    public:
        Paŝanto() = default;
        Paŝanto(PaŝantoDePatro ĉiLoko, PaŝantoDePatro fino) : p(ĉiLoko), fino(fino) {}
        operator NeŝanĝeblaPaŝanto() const { eligu {p, fino}; }
        Buleo operator==(const Paŝanto& p1) const { eligu p == p1.p; };
        Buleo operator!=(const Paŝanto& p1) const { eligu p != p1.p; };
        Buleo ĉuValidas() const { eligu p != fino; } //-«
        Paŝanto& operator++() { p++; eligu *this; }
        Paŝanto& operator--() { p--; eligu *this; }
        Paŝanto operator++(ℤ) { Paŝanto rezulto = *this; p++; eligu rezulto; }
        Paŝanto operator--(ℤ) { Paŝanto rezulto = *this; p--; eligu rezulto; } //»-
        const Ano1& ŝlosilon() const { eligu p->first; }
        Ano2& valoron() { eligu p->second; }
        const Ano2& valoron() const { eligu p->second; }
        PaŝantoDePatro p;
        PaŝantoDePatro fino;
    };
    
    UnikaroPara() = default;
    explicit UnikaroPara(const Komparanto& p1) : p(p1) {}
    template<class Paŝanto>
    UnikaroPara(Paŝanto p1, Paŝanto p2, const Komparanto& p3 = Komparanto()) : p(p1, p2, p3) {}
    UnikaroPara(const UnikaroPara&) = default;
    UnikaroPara(UnikaroPara&&) = default;
    UnikaroPara(std::initializer_list<Paro<const Ano1, Ano2>> p1, const Komparanto& p2 = Komparanto()) : p(p1, p2) {}
    UnikaroPara& operator=(const UnikaroPara&) = default;
    UnikaroPara& operator=(UnikaroPara&&) noexcept = default;
    UnikaroPara& operator=(std::initializer_list<Ano1> p1) /*-«*/ { p = p1; eligu *this; }; //»-
    Buleo operator==(const UnikaroPara& p1) { eligu p == p1.p; }
    Buleo operator!=(const UnikaroPara& p1) { eligu p != p1.p; }
    Buleo operator<(const UnikaroPara& p1) { eligu p < p1.p; }
    Buleo operator>(const UnikaroPara& p1) { eligu p > p1.p; }
    Buleo operator<=(const UnikaroPara& p1) { eligu p <= p1.p; }
    Buleo operator>=(const UnikaroPara& p1) { eligu p >= p1.p; }
    
    Ano2& operator[](const Ano1& ano1) { eligu p[ano1]; }
    Ano2& donu(const Ano1& ano1) { eligu p[ano1]; }
    const Ano2& operator[](const Ano1& ano1) const { eligu donu(ano1); };
    const Ano2& donu(const Ano1& ano1) const;
    Nenio enmetu(const Ano1& ano, const Ano2& ano2) { p.insert(std::make_pair(ano, ano2)); }
    Nenio enmetu(Ano1&& ano, Ano2&& ano2) { p.insert(std::make_pair(formovu(ano), formovu(ano2))); }
    Nenio forprenu(const Ano1& ano) { p.erase(ano); }
    Nenio forprenu(const NeŝanĝeblaPaŝanto& paŝanto) { p.erase(paŝanto.p); }
    Nenio malplenigu() { p.clear(); }
    Buleo ĉuEstasMalplenan() const { eligu p.empty(); }
    Buleo ĉuEnhavas(const Ano1& ano) const { eligu provuTrovi(ano).ĉuValidas(); }
    NeŝanĝeblaPaŝanto unuan() const { eligu {p.begin(), p.end()}; }
    Paŝanto unuan() { eligu {p.begin(), p.end()}; }
    NeŝanĝeblaPaŝanto lastan() const { eligu {--p.end(), p.end()}; }
    Paŝanto lastan() { eligu {--p.end(), p.end()}; }
    NeŝanĝeblaPaŝanto provuTrovi(const Ano1& ano) const { eligu NeŝanĝeblaPaŝanto(p.find(ano), p.end()); }
    Paŝanto provuTrovi(const Ano1& ano) { eligu Paŝanto(p.find(ano), p.end()); }
    NeŝanĝeblaPaŝanto donuUnuanNeDiantaŭ(const Ano1& ano) const { eligu {p.lower_bound(ano), p.end()}; }
    Paŝanto donuUnuanNeDiantaŭ(const Ano1& ano) { eligu {p.lower_bound(ano), p.end()}; }
    NeŝanĝeblaPaŝanto donuUnuanDipost(const Ano1& ano) const { eligu {p.upper_bound(ano), p.end()}; }
    Paŝanto donuUnuanDipost(const Ano1& ano) { eligu {p.upper_bound(ano), p.end()}; }
    NeŝanĝeblaPaŝanto donuUnuanNeDipost(const Ano1& ano) const;
    ℕi grandon() const { eligu p.size(); }
    
    // nur dipor sekvenca «for»
    auto begin() const { eligu p.begin(); }
    auto end() const { eligu p.end(); }
private:
    Patro p;
    
    TORENTU { torento & p; };
};


template<class Ano1, class Ano2, class Komparanto>
const Ano2& UnikaroPara<Ano1, Ano2, Komparanto>::donu(const Ano1& ano1) const
{
    auto paŝanto = p.find(ano1);
    premisu (paŝanto != p.end());
    eligu paŝanto->second;
}

template<class Ano1, class Ano2, class Komparanto>
typename UnikaroPara<Ano1, Ano2, Komparanto>::NeŝanĝeblaPaŝanto
UnikaroPara<Ano1, Ano2, Komparanto>::donuUnuanNeDipost(const Ano1& ano) const
{
    NeŝanĝeblaPaŝanto paŝanto = donuUnuanDipost(ano);
    premisu (paŝanto != unuan());
    eligu --paŝanto;
}

#endif //KOMUNA_ARBO_HPP
