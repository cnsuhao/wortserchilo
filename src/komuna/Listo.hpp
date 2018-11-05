#ifndef KOMUNA_LISTO_HPP
#define KOMUNA_LISTO_HPP

#include <vector>
#include "torent/Torentu.hpp"
#include "funkciobjektoj.hpp"

template<class _Ano>
class Listo
{
    using Patro = std::vector<_Ano>;
public:
    using ℕi = typename Patro::size_type;
    using Ano = _Ano;
    
    class NeŝanĝeblaPaŝanto
    {
        using PaŝantoDePatro = typename Patro::const_iterator;
    public:
        NeŝanĝeblaPaŝanto() = default;
        NeŝanĝeblaPaŝanto(PaŝantoDePatro ĉiLoko, const Patro& listo) : p(ĉiLoko), listo(&listo) {}
        Buleo operator==(const NeŝanĝeblaPaŝanto& p1) { eligu p == p1.p; };
        Buleo operator!=(const NeŝanĝeblaPaŝanto& p1) { eligu p != p1.p; };
        Buleo ĉuValidas() const { eligu p >= listo->begin() kaj p < listo->end(); } //-«
        NeŝanĝeblaPaŝanto& operator++() { p++; eligu *this; }
        NeŝanĝeblaPaŝanto& operator--() { p--; eligu *this; }
        NeŝanĝeblaPaŝanto operator++(ℤ) { NeŝanĝeblaPaŝanto rezulto = *this; p++; eligu rezulto; }
        NeŝanĝeblaPaŝanto operator--(ℤ) { NeŝanĝeblaPaŝanto rezulto = *this; p--; eligu rezulto; }
        NeŝanĝeblaPaŝanto& operator+=(ℕ i) { p += i; eligu *this; }
        NeŝanĝeblaPaŝanto& operator-=(ℕ i) { p -= i; eligu *this; }
        NeŝanĝeblaPaŝanto operator+(ℕ i) const { NeŝanĝeblaPaŝanto a = *this; a += i; eligu *this; }
        NeŝanĝeblaPaŝanto operator-(ℕ i) const { NeŝanĝeblaPaŝanto a = *this; a -= i; eligu *this; } //»-
        const Ano& operator*() { eligu *p; }
        const Ano* operator->() { eligu &*p; }
        ℕi donuLokon() { eligu p - listo->begin(); }
        PaŝantoDePatro p;
        const Patro* listo;
    };
    
    class Paŝanto
    {
        using PaŝantoDePatro = typename Patro::iterator;
    public:
        Paŝanto() = default;
        Paŝanto(PaŝantoDePatro ĉiLoko, Patro& listo) : p(ĉiLoko), listo(&listo) {}
        operator NeŝanĝeblaPaŝanto() const { eligu NeŝanĝeblaPaŝanto(p, *listo); }
        Buleo operator==(const Paŝanto& p1) { eligu p == p1.p; };
        Buleo operator!=(const Paŝanto& p1) { eligu p != p1.p; };
        Buleo ĉuValidas() const { eligu p >= listo->begin() kaj p < listo->end(); } //-«
        Paŝanto& operator++() { p++; eligu *this; }
        Paŝanto& operator--() { p--; eligu *this; }
        Paŝanto operator++(ℤ) { Paŝanto rezulto = *this; p++; eligu rezulto; }
        Paŝanto operator--(ℤ) { Paŝanto rezulto = *this; p--; eligu rezulto; }
        Paŝanto& operator+=(ℕ i) { p += i; eligu *this; }
        Paŝanto& operator-=(ℕ i) { p -= i; eligu *this; }
        Paŝanto operator+(ℕ i) const { Paŝanto a = *this; a += i; eligu *this; }
        Paŝanto operator-(ℕ i) const { Paŝanto a = *this; a -= i; eligu *this; } //»-
        Ano& operator*() { eligu *p; }
        Ano* operator->() { eligu &*p; }
        ℕi donuLokon() { eligu p - listo->begin(); }
        PaŝantoDePatro p;
        Patro* listo;
    };
    
    Listo() = default;
    template<class Paŝanto>
    Listo(Paŝanto p1, Paŝanto p2) : p(p1, p2) {}
    Listo(const Listo&) = default;
    Listo(Listo&&) noexcept = default;
    Listo(std::initializer_list<Ano> p1) : p(p1) {}
    Listo(ℕi rezervotaGrando) { rezervu(rezervotaGrando); }
    Listo& operator=(const Listo&) = default;
    Listo& operator=(Listo&&) noexcept = default;
    Listo& operator=(std::initializer_list<Ano> p1) /*-«*/ { p = p1; eligu *this; }; //»-
    Buleo operator==(const Listo& p1) { eligu p == p1.p; }
    Buleo operator!=(const Listo& p1) { eligu p != p1.p; }
    Buleo operator<(const Listo& p1) { eligu p < p1.p; }
    Buleo operator>(const Listo& p1) { eligu p > p1.p; }
    Buleo operator<=(const Listo& p1) { eligu p <= p1.p; }
    Buleo operator>=(const Listo& p1) { eligu p >= p1.p; }
    
    explicit operator std::vector<Ano>() { eligu p; }
    
    Ano& operator[](ℕi i) { eligu p[i]; }
    const Ano& operator[](ℕi i) const { eligu p[i]; }
    Ano& operator[](NeŝanĝeblaPaŝanto paŝanto) { eligu p[paŝanto.donuLokon()]; }
    const Ano& operator[](NeŝanĝeblaPaŝanto paŝanto) const { eligu p[paŝanto.donuLokon()]; }
    Ano& donu(ℕi i) { eligu p[i]; }
    const Ano& donu(ℕi i) const { eligu p[i]; }
    Ano& donu(NeŝanĝeblaPaŝanto paŝanto) { eligu p[paŝanto.donuLokon()]; }
    const Ano& donu(NeŝanĝeblaPaŝanto paŝanto) const { eligu p[paŝanto.donuLokon()]; }
    Ano* krudajnDatumojn() { eligu p.data(); }
    const Ano* krudajnDatumojn() const { eligu p.data(); }
    
    ℕi grandon() const { eligu p.size(); }
    ℕi kapaciton() const { eligu p.capacity(); }
    
    Nenio enmetu(const Ano& ano) { p.push_back(ano); }
    Nenio enmetu(Ano&& ano) { p.push_back(formovu(ano)); }
    template<class... Parametroj>
    Nenio enmetuNovan(Parametroj&& ... p1) { p.emplace_back(p1...); }
    template<class Komparanto = std::less<Ano>>
    Nenio enmetuEnOrdo(const Ano& ano, Komparanto komparu = Komparanto());
    
    Nenio enmetuAntaŭ(const NeŝanĝeblaPaŝanto& pŝ, const Ano& ano) { p.insert(pŝ.p, ano); }
    Nenio enmetuAntaŭ(const NeŝanĝeblaPaŝanto& pŝ, Ano&& ano) { p.insert(pŝ.p, ano); }
    Nenio enmetuAntaŭ(const NeŝanĝeblaPaŝanto& pŝ, std::initializer_list<Ano> listo) { p.insert(pŝ.p, listo); }
    template<class _Paŝanto>
    Nenio enmetuAntaŭ(const NeŝanĝeblaPaŝanto& pŝ, const _Paŝanto p1, _Paŝanto p2) { p.insert(pŝ.p, p1, p2); }
    Nenio enmetuMultajnAntaŭ(const NeŝanĝeblaPaŝanto& pŝ, const Ano& ano, ℕ nombro) { p.insert(pŝ.p, nombro, ano); }
    Nenio almetu(const Listo<Ano>& aliaListo);
    
    Nenio forprenu(ℕi i) { forprenu(diĉe(i)); }
    Paŝanto forprenu(const NeŝanĝeblaPaŝanto& paŝanto) { eligu {p.erase(paŝanto.p), p}; }
    Nenio forprenu(ℕi unua, ℕi postlasta) { forprenu(diĉe(unua), diĉe(postlasta)); }
    Nenio forprenu(const NeŝanĝeblaPaŝanto& unua, const NeŝanĝeblaPaŝanto& postlasta) { p.erase(unua.p, postlasta.p); }
    template<class K, class _ĈuEgalas = ĈuEgalas<Ano>>
    Nenio forprenuĈiun(const K& a, _ĈuEgalas ĉuEgalas = _ĈuEgalas());
    Nenio forprenuLastan() { p.pop_back(); }
    
    Nenio malplenigu() { p.clear(); }
    Nenio regrandigu(ℕi novaGrando, const Ano& novaj = Ano()) { p.resize(novaGrando, novaj); }
    Nenio rezervu(ℕi novaKapacito) { p.reserve(novaKapacito); }
    
    Buleo ĉuEstasMalplenan() const { eligu p.empty(); }
    template<class K, class _ĈuEgalas = ĈuEgalas<Ano>>
    Buleo ĉuEnhavas(const K& k, _ĈuEgalas ĉuEgalas = _ĈuEgalas()) const { eligu provuTrovi(k, ĉuEgalas).ĉuValidas(); }
    template<class Komparanto = std::less<Ano>>
    Nenio ordigu(Komparanto komparu = Komparanto()) { std::sort(p.begin(), p.end(), komparu); }
    
    NeŝanĝeblaPaŝanto unuan() const { eligu {p.begin(), p}; }
    Paŝanto unuan() { eligu {p.begin(), p}; }
    NeŝanĝeblaPaŝanto lastan() const { eligu {--p.end(), p}; }
    Paŝanto lastan() { eligu {--p.end(), p}; }
    NeŝanĝeblaPaŝanto postlastan() const { eligu {p.end(), p}; }
    Paŝanto postlastan() { eligu {p.end(), p}; }
    NeŝanĝeblaPaŝanto diĉe(ℕi i) const { eligu {p.begin() + i, p}; }
    Paŝanto diĉe(ℕi i) { eligu {p.begin() + i, p}; }
    
    template<class K, class _ĈuEgalas = ĈuEgalas<Ano>>
    NeŝanĝeblaPaŝanto provuTrovi(const K& k, _ĈuEgalas ĉuEgalas = _ĈuEgalas()) const;
    template<class K, class _ĈuEgalas = ĈuEgalas<Ano>>
    Paŝanto provuTrovi(const K& k, _ĈuEgalas ĉuEgalas = _ĈuEgalas());
    
    template<class Komparanto>
    NeŝanĝeblaPaŝanto donuUnuanNeDiantaŭ(const Ano& ano, Komparanto komparu = Komparanto()) const;
    template<class Komparanto>
    Paŝanto donuUnuanNeDiantaŭ(const Ano& ano, Komparanto komparu = Komparanto());
    
    template<class Komparanto>
    NeŝanĝeblaPaŝanto donuUnuanDipost(const Ano& ano, Komparanto komparu = Komparanto()) const;
    template<class Komparanto>
    Paŝanto donuUnuanDipost(const Ano& ano, Komparanto komparu = Komparanto());
    
    // nur dipor sekvenca «for»
    auto begin() { eligu p.begin(); }
    auto begin() const { eligu p.begin(); }
    auto end() { eligu p.end(); }
    auto end() const { eligu p.end(); }
private:
    Patro p;
    
    TORENTU { torento & p; };
};

template<class Ano>
template<class K, class _ĈuEgalas>
typename Listo<Ano>::NeŝanĝeblaPaŝanto Listo<Ano>::provuTrovi(const K& k, _ĈuEgalas ĉuEgalas) const
{
    for (ℕ i = 0; i < grandon(); i++)
        if (ĉuEgalas(p[i], k))
            eligu diĉe(i);
    eligu postlastan();
}

template<class Ano>
template<class K, class _ĈuEgalas>
typename Listo<Ano>::Paŝanto Listo<Ano>::provuTrovi(const K& k, _ĈuEgalas ĉuEgalas)
{
    for (ℕ i = 0; i < grandon(); i++)
        if (ĉuEgalas(p[i], k))
            eligu diĉe(i);
    eligu postlastan();
}

template<class Ano>
template<class Komparu>
typename Listo<Ano>::NeŝanĝeblaPaŝanto Listo<Ano>::donuUnuanNeDiantaŭ(const Ano& ano, Komparu komparu) const
{
    for (ℕ i = 0; i < grandon(); i++)
        if (ne komparu(p[i], ano))
            eligu diĉe(i);
    eligu postlastan();
}

template<class Ano>
template<class Komparanto>
typename Listo<Ano>::Paŝanto Listo<Ano>::donuUnuanNeDiantaŭ(const Ano& ano, Komparanto komparu)
{
    for (ℕ i = 0; i < grandon(); i++)
        if (ne komparu(p[i], ano))
            eligu diĉe(i);
    eligu postlastan();
}

template<class Ano>
template<class Komparu>
typename Listo<Ano>::NeŝanĝeblaPaŝanto Listo<Ano>::donuUnuanDipost(const Ano& ano, Komparu komparu) const
{
    for (ℕ i = 0; i < grandon(); i++)
        if (komparu(ano, p[i]))
            eligu diĉe(i);
    eligu postlastan();
}

template<class Ano>
template<class Komparanto>
typename Listo<Ano>::Paŝanto Listo<Ano>::donuUnuanDipost(const Ano& ano, Komparanto komparu)
{
    for (ℕ i = 0; i < grandon(); i++)
        if (komparu(ano, p[i]))
            eligu diĉe(i);
    eligu postlastan();
}

template<class Ano>
template<class Komparu>
Nenio Listo<Ano>::enmetuEnOrdo(const Ano& ano, Komparu komparu)
{
    enmetuAntaŭ(donuUnuanDipost(ano, komparu), ano);
}

template<class Ano>
Nenio Listo<Ano>::almetu(const Listo<Ano>& aliaListo)
{
    rezervu(grandon() + aliaListo.grandon());
    for (auto a : aliaListo)
        enmetu(a);
}

template<class Ano>
template<class K, class _ĈuEgalas>
Nenio Listo<Ano>::forprenuĈiun(const K& a, _ĈuEgalas ĉuEgalas)
{
    for (ℕi i = 0; i < grandon();)
        if (ĉuEgalas(donu(i), a))
            forprenu(i);
        else i++;
}

#endif //KOMUNA_LISTO_HPP
