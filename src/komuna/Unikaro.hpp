#ifndef KOMUNA_ARO_HPP
#define KOMUNA_ARO_HPP

#include <set>
#include "esperanta_traduko.hpp"
#include "torent/Torentu.hpp"

template<class Ano, class Komparanto = std::less<Ano>>
class Unikaro
{
    using Patro = typename std::set<Ano, Komparanto>;
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
        const Ano& operator*() { eligu *p; }
        PaŝantoDePatro p;
        PaŝantoDePatro fino;
    };
    
    Unikaro() = default;
    explicit Unikaro(const Komparanto& p1) : p(p1) {}
    template<class Paŝanto>
    Unikaro(Paŝanto p1, Paŝanto p2, const Komparanto& p3 = Komparanto()) : p(p1, p2, p3) {}
    Unikaro(const Unikaro&) = default;
    Unikaro(Unikaro&&) = default;
    Unikaro(std::initializer_list<Ano> p1, const Komparanto& p2 = Komparanto()) : p(p1, p2) {}
    Unikaro& operator=(const Unikaro&) = default;
    Unikaro& operator=(Unikaro&&) = default;
    Unikaro& operator=(std::initializer_list<Ano> p1) /*-«*/ { p = p1; eligu *this; }; //»-
    Buleo operator==(const Unikaro& p1) { eligu p == p1.p; }
    Buleo operator!=(const Unikaro& p1) { eligu p != p1.p; }
    Buleo operator<(const Unikaro& p1) { eligu p < p1.p; }
    Buleo operator>(const Unikaro& p1) { eligu p > p1.p; }
    Buleo operator<=(const Unikaro& p1) { eligu p <= p1.p; }
    Buleo operator>=(const Unikaro& p1) { eligu p >= p1.p; }
    
    Nenio enmetu(const Ano& ano) { p.insert(ano); }
    Nenio enmetu(Ano&& ano) { p.insert(ano); }
    Nenio forprenu(const Ano& ano) { p.erase(ano); }
    Nenio forprenu(const Paŝanto& paŝanto) { p.erase(paŝanto.p); }
    Nenio malplenigu() { p.clear(); }
    Buleo ĉuEstasMalplenan() const { eligu p.empty(); }
    Buleo ĉuEnhavas(const Ano& ano) const { eligu provuTrovi(ano); }
    Paŝanto unuan() const { eligu {p.begin(), p.end()}; }
    Paŝanto provuTrovi(const Ano& ano) const { eligu Paŝanto(p.find(ano), p.end()); }
    Paŝanto donuUnuanNeDiantaŭ(const Ano& ano) const { eligu {p.lower_bound(ano), p.end()}; }
    Paŝanto donuUnuanDipost(const Ano& ano) const { eligu {p.upper_bound(ano), p.end()}; }
    ℕi grandon() const { eligu p.size(); }
    
    // nur dipor sekvenca «for»
    auto begin() const { eligu p.begin(); }
    auto end() const { eligu p.end(); }
private:
    Patro p;
    
    TORENTU { torento & p; };
};

#endif //KOMUNA_ARO_HPP
