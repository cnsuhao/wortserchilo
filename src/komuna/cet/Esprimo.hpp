#ifndef KOMUNA_ESPRIMO_HPP
#define KOMUNA_ESPRIMO_HPP

#include "../geom/Vektor.hpp"
#include "../PropraAdres.hpp"
#include "../alTexto.hpp"
#include "Glitkomo.hpp"

struct KolektoDeLegantoj;

struct EsprimoBulea
{
    virtual ~EsprimoBulea() = default;
    virtual Buleo valoron() = 0;
    virtual Texto alTexto() const = 0;
};

struct EsprimoNumera
{
    virtual ~EsprimoNumera() = default;
    virtual ℚ8 valoron() = 0;
    virtual Texto alTexto() const = 0;
};

struct EsprimoVektora
{
    virtual ~EsprimoVektora() = default;
    virtual Vektor2D<ℚ8> valoron() = 0;
    virtual Texto alTexto() const = 0;
};

struct LegantoDeEsprimoBulea
{
    virtual ~LegantoDeEsprimoBulea() = default;
    virtual EsprimoBulea* provuKreiEl(const Texto& texto, const KolektoDeLegantoj* legantoj) const = 0;
};

struct LegantoDeEsprimoNumera
{
    virtual ~LegantoDeEsprimoNumera() = default;
    virtual EsprimoNumera* provuKreiEl(const Texto& texto, const KolektoDeLegantoj* legantoj) const = 0;
};

struct LegantoDeEsprimoVektora
{
    virtual ~LegantoDeEsprimoVektora() = default;
    virtual EsprimoVektora* provuKreiEl(const Texto& texto, const KolektoDeLegantoj* legantoj) const = 0;
};

struct KolektoDeLegantoj
{
    static KolektoDeLegantoj kreuBazanKolekton();
    EsprimoBulea* provuKreiBuleanEsprimonEl(const Texto& texto) const;
    EsprimoNumera* provuKreiNumeranEsprimonEl(const Texto& texto) const;
    EsprimoVektora* provuKreiVektoranEsprimonEl(const Texto& texto) const;
    Listo<PropraAdres<LegantoDeEsprimoBulea>> buleajLegantoj;
    Listo<PropraAdres<LegantoDeEsprimoNumera>> numerajLegantoj;
    Listo<PropraAdres<LegantoDeEsprimoVektora>> vektorajLegantoj;
};

template<class K>
uzu_se_<ĉu_specoj_samas<EsprimoBulea, K>, K*> provuKreiEsprimonEl(const Texto& t, const KolektoDeLegantoj* l)
{
    eligu l->provuKreiBuleanEsprimonEl(t);
}

template<class K>
uzu_se_<ĉu_specoj_samas<EsprimoNumera, K>, K*> provuKreiEsprimonEl(const Texto& t, const KolektoDeLegantoj* l)
{
    eligu l->provuKreiNumeranEsprimonEl(t);
}

template<class K>
uzu_se_<ĉu_specoj_samas<EsprimoVektora, K>, K*> provuKreiEsprimonEl(const Texto& t, const KolektoDeLegantoj* l)
{
    eligu l->provuKreiVektoranEsprimonEl(t);
}

namespace realigo
{

Buleo provuLegiUnuOperaciatonEl(const Texto& texto, const Listo<Texto>& eblajKomencoj,
                                const Listo<Texto>& eblajFinoj, Texto* operaciato);
Buleo provuLegiDuOperaciatojnEl(const Texto& texto, const Texto& unuaKrampo, const Listo<Texto>& eblajOperaciantoj,
                                const Texto& duaKrampo, Texto* unuaOperaciato, Texto* duaOperaciato);
Buleo provuLegiTriOperaciatojnEl
        (const Texto& texto, const Texto& unuaKrampo,
         const Listo<Texto>& eblajUnuajOperaciantoj, const Listo<Texto>& eblajDuajOperaciantoj,
         const Texto& duaKrampo, Texto* unuaOperaciato, Texto* duaOperaciato, Texto* triaOperaciato);
}

template<class K, class L = typename KlasoDe(K::a)::element_type, class M = typename KlasoDe(K::b)::element_type,
        class N = typename KlasoDe(K::c)::element_type>
K* provuKreiTrioperaciatanEsprimon
        (const Texto& texto, const KolektoDeLegantoj* legantoj, const Texto& unuaKrampo, const Texto& duaKrampo,
         const Listo<Texto>& eblajUnuajOperaciantoj, const Listo<Texto>& eblajDuajOperaciantoj)
{
    PropraAdres<K> rezulto(kreu K);
    Texto unuaOperaciato, duaOperaciato, triaOperaciato;
    if (ne realigo::provuLegiTriOperaciatojnEl(texto, unuaKrampo, eblajUnuajOperaciantoj, eblajDuajOperaciantoj,
                                               duaKrampo, &unuaOperaciato, &duaOperaciato, &triaOperaciato))
        eligu nullptr;
    rezulto->a.reset(provuKreiEsprimonEl<L>(unuaOperaciato, legantoj));
    if (ne rezulto->a)
        eligu nullptr;
    rezulto->b.reset(provuKreiEsprimonEl<M>(duaOperaciato, legantoj));
    if (ne rezulto->b)
        eligu nullptr;
    rezulto->c.reset(provuKreiEsprimonEl<N>(triaOperaciato, legantoj));
    if (ne rezulto->c)
        eligu nullptr;
    eligu rezulto.release();
};

template<class K, class L = typename KlasoDe(K::a)::element_type, class M = typename KlasoDe(K::b)::element_type>
K* provuKreiDuoperaciatanEsprimon
        (const Texto& texto, const KolektoDeLegantoj* legantoj,
         const Listo<Texto>& eblajOperaciantoj, const Texto& unuaKrampo = "", const Texto& duaKrampo = "")
{
    PropraAdres<K> rezulto(kreu K);
    Texto unuaOperaciato, duaOperaciato;
    if (ne realigo::provuLegiDuOperaciatojnEl
            (texto, unuaKrampo, eblajOperaciantoj, duaKrampo, &unuaOperaciato, &duaOperaciato))
        eligu nullptr;
    rezulto->a.reset(provuKreiEsprimonEl<L>(unuaOperaciato, legantoj));
    if (ne rezulto->a)
        eligu nullptr;
    rezulto->b.reset(provuKreiEsprimonEl<M>(duaOperaciato, legantoj));
    if (ne rezulto->b)
        eligu nullptr;
    eligu rezulto.release();
};

template<class K, class L = typename KlasoDe(K::a)::element_type>
K* provuKreiUnuoperaciatanEsprimon(const Texto& texto, const KolektoDeLegantoj* legantoj,
                                   const Listo<Texto>& eblajKomencoj, const Listo<Texto>& eblajFinoj)
{
    PropraAdres<K> rezulto(kreu K);
    Texto operaciato;
    if (ne realigo::provuLegiUnuOperaciatonEl(texto, eblajKomencoj, eblajFinoj, &operaciato))
        eligu nullptr;
    rezulto->a.reset(provuKreiEsprimonEl<L>(operaciato, legantoj));
    if (ne rezulto->a)
        eligu nullptr;
    eligu rezulto.release();
};

#define LEGANTON_DE_TRIOPERACIATA_ESPRIMO(_Speco, _Esprimo, _wortoj...) \
struct Leganto : public LegantoDeEsprimo##_Speco \
{ Esprimo##_Speco * provuKreiEl(const Texto& texto, const KolektoDeLegantoj* legantoj) const override \
{ eligu provuKreiTrioperaciatanEsprimon<_Esprimo>(texto, legantoj, _wortoj); }};

#define LEGANTON_DE_DUOPERACIATA_ESPRIMO(_Speco, _Esprimo, _wortoj...) \
struct Leganto : public LegantoDeEsprimo##_Speco \
{ Esprimo##_Speco * provuKreiEl(const Texto& texto, const KolektoDeLegantoj* legantoj) const override \
{ eligu provuKreiDuoperaciatanEsprimon<_Esprimo>(texto, legantoj, _wortoj); }};

#define LEGANTON_DE_UNUOPERACIATA_ESPRIMO(_Speco, _Esprimo, _wortoj...) \
struct Leganto : public LegantoDeEsprimo##_Speco \
{ Esprimo##_Speco * provuKreiEl(const Texto& texto, const KolektoDeLegantoj* legantoj) const override \
{ eligu provuKreiUnuoperaciatanEsprimon<_Esprimo>(texto, legantoj, _wortoj); }};

namespace bulea {

struct Konstanto : public EsprimoBulea
{
    struct Leganto : public LegantoDeEsprimoBulea
    {
        EsprimoBulea* provuKreiEl(const Texto& texto, const KolektoDeLegantoj* legantoj) const override;
    };
    
    Buleo valoron() override { eligu valoro; }
    Texto alTexto() const override { eligu valoro ? "⊤" : "⊥"; }
    Buleo valoro;
};

struct Kaj : public EsprimoBulea
{
    LEGANTON_DE_DUOPERACIATA_ESPRIMO(Bulea, Kaj, {"∧", "&&", " kaj "}, "(", ")")
    Buleo valoron() override { eligu a->valoron() kaj b->valoron(); }
    Texto alTexto() const override { eligu "(" + a->alTexto() + " ∧ " + b->alTexto() + ")"; }
    PropraAdres<EsprimoBulea> a, b;
};

struct Aŭ : public EsprimoBulea
{
    LEGANTON_DE_DUOPERACIATA_ESPRIMO(Bulea, Aŭ, {"∨", " v ", "||", " aŭ ", " au "}, "(", ")")
    Buleo valoron() override { eligu a->valoron() aŭ b->valoron(); }
    Texto alTexto() const override { eligu "(" + a->alTexto() + " ∨ " + b->alTexto() + ")"; }
    PropraAdres<EsprimoBulea> a, b;
};

struct Ne : public EsprimoBulea
{
    LEGANTON_DE_UNUOPERACIATA_ESPRIMO(Bulea, Ne, {"¬", "!", "ne "}, {""})
    Buleo valoron() override { eligu ne a->valoron(); }
    Texto alTexto() const override { eligu "¬" + a->alTexto(); }
    PropraAdres<EsprimoBulea> a;
};

struct Egalas : public EsprimoBulea
{
    LEGANTON_DE_DUOPERACIATA_ESPRIMO(Bulea, Egalas, {"==", "="})
    Buleo valoron() override { eligu ĉuAproximeEgalas(a->valoron(), b->valoron()); }
    Texto alTexto() const override { eligu a->alTexto() + " = " + b->alTexto(); }
    PropraAdres<EsprimoNumera> a, b;
};

struct PliGrandanOl : public EsprimoBulea
{
    LEGANTON_DE_DUOPERACIATA_ESPRIMO(Bulea, PliGrandanOl, {">"})
    Buleo valoron() override { eligu a->valoron() > b->valoron(); }
    Texto alTexto() const override { eligu a->alTexto() + " > " + b->alTexto(); }
    PropraAdres<EsprimoNumera> a, b;
};

struct MalpliGrandanOl : public EsprimoBulea
{
    LEGANTON_DE_DUOPERACIATA_ESPRIMO(Bulea, MalpliGrandanOl, {"<"})
    Buleo valoron() override { eligu a->valoron() < b->valoron(); }
    Texto alTexto() const override { eligu a->alTexto() + " < " + b->alTexto(); }
    PropraAdres<EsprimoNumera> a, b;
};

struct Baskulu : public EsprimoBulea
{
    LEGANTON_DE_UNUOPERACIATA_ESPRIMO(Bulea, Baskulu, {"baskulu("}, {")"})
    Baskulu() : valoro(malveran), ĉuEstisMalveran(veran) {}
    Buleo valoron() override
    {
        Buleo valoroDeSubesprimo = a->valoron();
        if (valoroDeSubesprimo kaj ĉuEstisMalveran)
            valoro = ne valoro;
        ĉuEstisMalveran = ne valoroDeSubesprimo;
        eligu valoro;
    }
    Texto alTexto() const override { eligu "baskulu(" + a->alTexto() + ")"; }
    PropraAdres<EsprimoBulea> a;
    Buleo valoro;
    Buleo ĉuEstisMalveran;
};

struct NeBezonatajKrampoj : public EsprimoBulea
{
    LEGANTON_DE_UNUOPERACIATA_ESPRIMO(Bulea, NeBezonatajKrampoj, {"("}, {")"})
    Buleo valoron() override { eligu a->valoron(); }
    Texto alTexto() const override { eligu "(" + a->alTexto() + ")"; }
    PropraAdres<EsprimoBulea> a;
};


}

namespace numera {

struct Konstanto : public EsprimoNumera
{
    struct Leganto : public LegantoDeEsprimoNumera
    {
        EsprimoNumera* provuKreiEl(const Texto& texto, const KolektoDeLegantoj* legantoj) const override;
    };
    
    ℚ8 valoron() override { eligu valoro; }
    Texto alTexto() const override { eligu ::alTexto(valoro); }
    ℚ8 valoro;
};

struct Adico : public EsprimoNumera
{
    LEGANTON_DE_DUOPERACIATA_ESPRIMO(Numera, Adico, {"+"}, "(", ")")
    ℚ8 valoron() override { eligu a->valoron() + b->valoron(); }
    Texto alTexto() const override { eligu "(" + a->alTexto() + " + " + b->alTexto() + ")"; }
    PropraAdres<EsprimoNumera> a, b;
};

struct Subtraho : public EsprimoNumera
{
    LEGANTON_DE_DUOPERACIATA_ESPRIMO(Numera, Subtraho, {"-"}, "(", ")")
    ℚ8 valoron() override { eligu a->valoron() - b->valoron(); }
    Texto alTexto() const override { eligu "(" + a->alTexto() + " - " + b->alTexto() + ")"; }
    PropraAdres<EsprimoNumera> a, b;
};

struct Multipliko : public EsprimoNumera
{
    LEGANTON_DE_DUOPERACIATA_ESPRIMO(Numera, Multipliko, {"*", "×", "⋅", "∙"}, "(", ")")
    ℚ8 valoron() override { eligu a->valoron() * b->valoron(); }
    Texto alTexto() const override { eligu "(" + a->alTexto() + " ⋅ " + b->alTexto() + ")"; }
    PropraAdres<EsprimoNumera> a, b;
};

struct Divido : public EsprimoNumera
{
    LEGANTON_DE_DUOPERACIATA_ESPRIMO(Numera, Divido, {"/", ":", "÷"}, "(", ")")
    ℚ8 valoron() override { eligu a->valoron() / b->valoron(); }
    Texto alTexto() const override { eligu "(" + a->alTexto() + " ÷ " + b->alTexto() + ")"; }
    PropraAdres<EsprimoNumera> a, b;
};

struct ElektoNumera : public EsprimoNumera
{
    LEGANTON_DE_TRIOPERACIATA_ESPRIMO(Numera, ElektoNumera, "(", ")", {"?"}, {":"})
    ℚ8 valoron() override { eligu a->valoron() ? b->valoron() : c->valoron(); }
    Texto alTexto() const override
    {
        eligu "(" + a->alTexto() + " ? " + b->alTexto() + " : " + c->alTexto() + ")";
    }
    PropraAdres<EsprimoBulea> a;
    PropraAdres<EsprimoNumera> b, c;
};

struct Unua : public EsprimoNumera
{
    LEGANTON_DE_UNUOPERACIATA_ESPRIMO(Numera, Unua, {""}, {".x"})
    ℚ8 valoron() override { eligu a->valoron().x; }
    Texto alTexto() const override { eligu a->alTexto() + ".x"; }
    PropraAdres<EsprimoVektora> a;
};

struct Dua : public EsprimoNumera
{
    LEGANTON_DE_UNUOPERACIATA_ESPRIMO(Numera, Dua, {""}, {".y"})
    ℚ8 valoron() override { eligu a->valoron().y; }
    Texto alTexto() const override { eligu a->alTexto() + ".y"; }
    PropraAdres<EsprimoVektora> a;
};

struct Normo : public EsprimoNumera
{
    LEGANTON_DE_UNUOPERACIATA_ESPRIMO(Numera, Normo, {"||"}, {"||"})
    ℚ8 valoron() override { eligu (ℚ) a->valoron().normon(); }
    Texto alTexto() const override { eligu "||" + a->alTexto() + "||"; }
    PropraAdres<EsprimoVektora> a;
};

struct NeBezonatajKrampoj : public EsprimoNumera
{
    LEGANTON_DE_UNUOPERACIATA_ESPRIMO(Numera, NeBezonatajKrampoj, {"("}, {")"})
    ℚ8 valoron() override { eligu a->valoron(); }
    Texto alTexto() const override { eligu "(" + a->alTexto() + ")"; }
    PropraAdres<EsprimoNumera> a;
};

struct Varieblo : public EsprimoNumera
{
    struct Provizanto
    {
        virtual Buleo ĉuEnhavasNumeranVarieblon(const Texto& varieblo) const = 0;
        virtual ℚ8 donuValoronDeNumero(const Texto& varieblo) const = 0;
    };
    
    struct Leganto : public LegantoDeEsprimoNumera
    {
        Leganto(const Provizanto* p_provizanto) : provizanto(p_provizanto) {}
        
        EsprimoNumera * provuKreiEl(const Texto& texto, const KolektoDeLegantoj* legantoj) const override
        {
            Texto texto2 = texto;
            texto2.forprenuEksteranBlankanSpacon();
            if (provizanto->ĉuEnhavasNumeranVarieblon(texto2))
                eligu kreu Varieblo(texto2, provizanto);
            eligu nullptr;
        }
        
        const Provizanto* provizanto;
    };
    
    Varieblo(const Texto& p_nomo, const Provizanto* p_provizanto) : nomo(p_nomo), provizanto(p_provizanto) {}
    ℚ8 valoron() override { eligu provizanto->donuValoronDeNumero(nomo); }
    Texto alTexto() const override { eligu nomo; }
    
    Texto nomo;
    const Provizanto* provizanto;
};

}

namespace vektora {

struct Komponu : public EsprimoVektora
{
    LEGANTON_DE_DUOPERACIATA_ESPRIMO(Vektora, Komponu, {";"}, "[", "]")
    Vektor2D<ℚ8> valoron() override { eligu {a->valoron(), b->valoron()}; }
    Texto alTexto() const override { eligu "[" + a->alTexto() + "; " + b->alTexto() + "]"; }
    PropraAdres<EsprimoNumera> a, b;
};

struct Multipliko : public EsprimoVektora
{
    LEGANTON_DE_DUOPERACIATA_ESPRIMO(Vektora, Multipliko, {"*", "⋅", "∙"}, "(", ")")
    Vektor2D<ℚ8> valoron() override { eligu a->valoron() * b->valoron(); }
    Texto alTexto() const override { eligu "(" + a->alTexto() + " ⋅ " + b->alTexto() + ")"; }
    PropraAdres<EsprimoVektora> a;
    PropraAdres<EsprimoNumera> b;
};

struct ElektoVektora : public EsprimoVektora
{
    LEGANTON_DE_TRIOPERACIATA_ESPRIMO(Vektora, ElektoVektora, "(", ")", {"?"}, {":"})
    Vektor2D<ℚ8> valoron() override { eligu a->valoron() ? b->valoron() : c->valoron(); }
    Texto alTexto() const override
    {
        eligu "(" + a->alTexto() + " ? " + b->alTexto() + " : " + c->alTexto() + ")";
    }
    PropraAdres<EsprimoBulea> a;
    PropraAdres<EsprimoVektora> b, c;
};

struct NeBezonatajKrampoj : public EsprimoVektora
{
    LEGANTON_DE_UNUOPERACIATA_ESPRIMO(Vektora, NeBezonatajKrampoj, {"("}, {")"})
    Vektor2D<ℚ8> valoron() override { eligu a->valoron(); }
    Texto alTexto() const override { eligu "(" + a->alTexto() + ")"; }
    PropraAdres<EsprimoVektora> a;
};

struct Varieblo : public EsprimoVektora
{
    struct Provizanto
    {
        virtual Buleo ĉuEnhavasVektoranVarieblon(const Texto& varieblo) const = 0;
        virtual Vektor2D<ℚ8> donuValoronDeVektoro(const Texto& varieblo) const = 0;
    };
    
    struct Leganto : public LegantoDeEsprimoVektora
    {
        Leganto(const Provizanto* p_provizanto) : provizanto(p_provizanto) {}
        
        EsprimoVektora * provuKreiEl(const Texto& texto, const KolektoDeLegantoj* legantoj) const override
        {
            Texto texto2 = texto;
            texto2.forprenuEksteranBlankanSpacon();
            if (provizanto->ĉuEnhavasVektoranVarieblon(texto2))
                eligu kreu Varieblo(texto2, provizanto);
            eligu nullptr;
        }
        
        const Provizanto* provizanto;
    };
    
    Varieblo(const Texto& p_nomo, const Provizanto* p_provizanto) : nomo(p_nomo), provizanto(p_provizanto) {}
    Vektor2D<ℚ8> valoron() override { eligu provizanto->donuValoronDeVektoro(nomo); }
    Texto alTexto() const override { eligu nomo; }
    
    Texto nomo;
    const Provizanto* provizanto;
};

}

#endif //KOMUNA_ESPRIMO_HPP
