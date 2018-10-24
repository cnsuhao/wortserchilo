#ifndef KOMUNA_TEXTO_HPP
#define KOMUNA_TEXTO_HPP

#ifdef ĈU_UZAS_QT
#include <QString>
#endif
#ifdef ĈU_UZAS_ICU_UNICODE
#include <unicode/unistr.h>
#endif
#include <string>
#include <regex>
#include "esperanta_traduko.hpp"
#include "Listo.hpp"

class Texto
{
    using Patro = std::string;
public:
    using ℕi = Patro::size_type;
    using Ano = Patro::value_type;
    friend Texto operator+(const Texto::Ano& p1, const Texto& p2);
    friend Texto operator+(const Texto::Ano* p1, const Texto& p2);
    friend Texto operator+(std::initializer_list<Texto::Ano> p1, const Texto& p2);
    
    class Paŝanto
    {
        using PaŝantoDePatro = typename Patro::const_iterator;
    public:
        Paŝanto() = default;
        Paŝanto(PaŝantoDePatro ĉiLoko, const Patro* p_texto) : p(ĉiLoko), texto(p_texto) {}
        Buleo operator==(const Paŝanto& p1) { eligu p == p1.p; };
        Buleo operator!=(const Paŝanto& p1) { eligu p != p1.p; };
        Buleo ĉuValidas() const;
        Buleo ĉuEstasUnuan() const;
        Buleo ĉuEstasPostlastan() const; //-«
        Paŝanto& operator++() { p++; eligu *this; }
        Paŝanto& operator--() { p--; eligu *this; }
        Paŝanto operator++(ℤ) { Paŝanto rezulto = *this; p++; eligu rezulto; }
        Paŝanto operator--(ℤ) { Paŝanto rezulto = *this; p--; eligu rezulto; }
        Paŝanto& operator+=(ℕ i) { p += i; eligu *this; }
        Paŝanto& operator-=(ℕ i) { p -= i; eligu *this; }
        Paŝanto operator+(ℕ i) const { Paŝanto a = *this; a += i; eligu *this; }
        Paŝanto operator-(ℕ i) const { Paŝanto a = *this; a -= i; eligu *this; } //»-
        const Ano& operator*() { eligu *p; }
        const Ano* operator->() { eligu &*p; }
        const ℕi donuLokon() noexcept;
        PaŝantoDePatro p;
        const Patro* texto;
    };
    
    Texto() = default;
    Texto(const Texto&) = default;
    Texto(Texto&&) = default;
    Texto(const std::string& p1) : p(p1) {}
    Texto(std::string&& p1) : p(p1) {}
    template<class Paŝanto>
    Texto(Paŝanto p1, Paŝanto p2) : p(p1, p2) {}
    Texto(const Ano* p1) : p(p1) {}
    Texto(const Ano* p1, ℕi longo) : p(p1, longo) {}
    Texto(std::initializer_list<Ano> p1) : p(p1) {}
#ifdef ĈU_UZAS_QT
    Texto(const QString& p1) : p(p1.toStdString()) {}
#endif
#ifdef ĈU_UZAS_ICU_UNICODE
    Texto(const UnicodeString& p1) { p1.toUTF8String(p); }
#endif

    template<class K>
    static Texto el(const K& k) { eligu Texto(std::to_string(k)); }
    Texto& operator=(const Texto&) = default;
    Texto& operator=(Texto&&) = default; //-«
    Texto& operator=(const std::string& p1) { p = p1; eligu *this; }
    Texto& operator=(std::string&& p1) { p = p1; eligu *this; }
    Texto& operator=(Ano p1) { p = p1; eligu *this; };
    Texto& operator=(const Ano* p1) { p = p1; eligu *this; };
    Texto& operator=(std::initializer_list<Ano> p1) { p = p1; eligu *this; }; //»-
    Buleo operator==(const Texto& p1) const { eligu p == p1.p; }
    Buleo operator==(const Ano* p1) const { eligu p == p1; }
    Buleo operator!=(const Texto& p1) const { eligu p != p1.p; }
    Buleo operator!=(const Ano* p1) const { eligu p != p1; }
    Buleo operator<(const Texto& p1) const { eligu p < p1.p; }
    Buleo operator>(const Texto& p1) const { eligu p > p1.p; }
    Buleo operator<=(const Texto& p1) const { eligu p <= p1.p; }
    Buleo operator>=(const Texto& p1) const { eligu p >= p1.p; } //-«
    Texto& operator+=(const Texto& p1) { p += p1.p; eligu *this; }
    Texto& operator+=(Ano p1) { p += p1; eligu *this; }
    Texto& operator+=(const Ano* p1) { p += p1; eligu *this; }
    Texto& operator+=(std::initializer_list<Ano> p1) { p += p1; eligu *this; } //»-
    Texto operator+(const Texto& p1) const { eligu Texto(p + p1.p); }
    Texto operator+(Ano p1) const { eligu Texto(p + p1); }
    Texto operator+(const Ano* p1) const { eligu Texto(p + p1); }
    
    explicit operator std::string() const { eligu p; }
    std::string STL() const { eligu p; }
    const char* c_str() const { eligu p.c_str(); }
#ifdef ĈU_UZAS_QT
    QString QT() const { eligu QString::fromUtf8(c_str()); }
#endif
#ifdef ĈU_UZAS_ICU_UNICODE
    UnicodeString ICU() const { eligu UnicodeString::fromUTF8(c_str()); }
#endif
    ℕ alℕ() const;
    ℤ alℤ() const;
    ℚ alℚ() const;
    
    Ano& operator[](ℕi i) { eligu p[i]; }
    const Ano& operator[](ℕi i) const { eligu p[i]; }
    Ano& operator[](Paŝanto paŝanto) { eligu p[paŝanto.donuLokon()]; }
    const Ano& operator[](Paŝanto paŝanto) const { eligu p[paŝanto.donuLokon()]; }
    
    ℕi grandon() const { eligu p.size(); }
    
    Nenio enmetu(const Ano& ano) { p.push_back(ano); }
    Nenio enmetu(Ano&& ano) { p.push_back(ano); }
    Nenio enmetuAntaŭ(const Paŝanto& pŝ, const Ano& ano) { p.insert(pŝ.p, ano); }
    Nenio enmetuAntaŭ(const Paŝanto& pŝ, Ano&& ano) { p.insert(pŝ.p, ano); }
    Nenio enmetuAntaŭ(const Paŝanto& pŝ, const Texto& texto);
    template<class _Paŝanto>
    Nenio enmetuAntaŭ(const Paŝanto& pŝ, const _Paŝanto p1, _Paŝanto p2) { p.insert(pŝ.p, p1, p2); }
    Nenio enmetuMultajnAntaŭ(const Paŝanto& pŝ, const Ano& k, ℕ nombro) { p.insert(pŝ.p, nombro, k); }
    
    Nenio forprenu(ℕi i) { forprenu(diĉe(i)); }
    Nenio forprenu(const Paŝanto& paŝanto) { p.erase(paŝanto.p); }
    Nenio forprenu(ℕi unua, ℕi lasta) { forprenu(diĉe(unua), diĉe(lasta)); }
    Nenio forprenu(const Paŝanto& unua, const Paŝanto& lasta) { p.erase(unua.p, lasta.p); }
    Nenio forprenuĈionDipost(ℕi loko) { forprenuĈionDipost(diĉe(loko)); }
    Nenio forprenuĈionDipost(const Paŝanto& loko) { forprenu(loko + 1, postlastan()); }
    Nenio forprenuĈionDiantaŭ(ℕi loko) { forprenuĈionDiantaŭ(diĉe(loko)); }
    Nenio forprenuĈionDiantaŭ(const Paŝanto& loko) { forprenu(unuan(), loko); }
    Nenio forprenuLastan() { p.pop_back(); }
    
    Nenio malplenigu() { p.clear(); }
    Nenio regrandigu(ℕi novaGrando, Ano novaj = Ano()) { p.resize(novaGrando, novaj); }
    Nenio rezervu(ℕi novaKapacito) { p.reserve(novaKapacito); }
    Texto minuskligitan() const;
    Texto majuskligitan() const;
    Nenio forprenuEksterajnCitilojn();
    Nenio forprenuEksteranBlankanSpacon();
    
    Buleo ĉuEstasMalplenan() const { eligu p.empty(); }
    Buleo ĉuEnhavas(const Ano& ano) const { eligu provuTrovi(ano).ĉuValidas(); }
    Buleo ĉuEnhavas(const Texto& texto) const { eligu provuTrovi(texto).ĉuValidas(); }
    Buleo ĉuEnhavas(const Ano* texto) const { eligu provuTrovi(texto).ĉuValidas(); }
    Buleo ĉuEnhavas(const Listo<Texto>& textoj) const { eligu provuTrovi(textoj).ĉuValidas(); }
    Buleo ĉuKomencasPer(const Texto& komenco) const;
    Buleo ĉuFinasPer(const Texto& fino) const;
    
    Texto donuPartonInter(ℕi i1, ℕi i2) const { eligu {p.substr(i1, i2 - i1)}; }
    
    Listo<Texto> trovuRegex(const std::regex& regex) const; // malplenan se ĉi-texto ne kongruas kun la regex
    Texto ŝanĝuTextonPerRegex(const std::regex& anstataŭigataRegex, const Texto& anstataŭigantaRegex) const;
    
    Paŝanto unuan() const { eligu {p.begin(), &p}; }
    Paŝanto lastan() const { eligu {--p.end(), &p}; }
    Paŝanto postlastan() const { eligu {p.end(), &p}; }
    Paŝanto diĉe(ℕi i) const { eligu {p.begin() + i, &p}; }
    Paŝanto provuTrovi(const Ano& ano) const;
    Paŝanto provuTrovi(const Texto& texto) const;
    Paŝanto provuTrovi(const Ano* texto) const;
    Paŝanto provuTrovi(const Listo<Texto>& textoj) const;
    Paŝanto provuTroviLastan(const Ano& ano) const;
    Paŝanto provuTroviNeAntaŭ(ℕi i0, const Ano& ano) const;
    Paŝanto provuTroviNeAntaŭ(ℕi i0, const Texto& texto) const;
    Paŝanto provuTroviNeAntaŭ(ℕi i0, const Ano* texto) const;
    Paŝanto provuTroviNeAntaŭ(ℕi i0, const Listo<Texto>& textoj) const;
    
    // nur dipor sekvenca «for»
    auto begin() { eligu p.begin(); }
    auto begin() const { eligu p.begin(); }
    auto end() { eligu p.end(); }
    auto end() const { eligu p.end(); }
    
    static constexpr ℕi neniu = Patro::npos;
private:
    Patro p;
    
    TORENTU { torento & p; };
};

inline Texto operator+(const Texto::Ano& p1, const Texto& p2) { eligu Texto(p1 + p2.p); }
inline Texto operator+(const Texto::Ano* p1, const Texto& p2) { eligu Texto(p1 + p2.p); }
inline Texto operator+(std::initializer_list<Texto::Ano> p1, const Texto& p2) { eligu Texto(p1 + p2.p); }

extern const Listo<Texto> blankspacaj_karakteroj;
const inline Listo<Texto> numeraj_karakteroj = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
extern const Texto komenca_citilo;
extern const Texto fina_citilo;

#endif //KOMUNA_TEXTO_HPP
