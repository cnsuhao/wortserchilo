#ifndef KOMUNA_ESPRIMUJO_HPP
#define KOMUNA_ESPRIMUJO_HPP

#include "Esprimo.hpp"
#include "../UnikaroPara.hpp"
#include "../Eraro.hpp"

class Esprimujo
{
public:
    struct Valoroj
    {
        UnikaroPara<Texto, Buleo> buleoj;
        UnikaroPara<Texto, ℚ8> numeroj;
        UnikaroPara<Texto, Vektor2D<ℚ8>> vektoroj;
    };
    
    Esprimujo(Buleo p_ĉuAŭtomatikeEnmetasNeExistantajnValorojn = malveran,
              KolektoDeLegantoj p_legantoj = KolektoDeLegantoj::kreuBazanKolekton());
    
    Nenio enmetuEsprimonBulean(const Texto& nomo, const Texto& esprimo);
    Nenio enmetuEsprimonNumeran(const Texto& nomo, const Texto& esprimo);
    Nenio enmetuEsprimonVektoran(const Texto& nomo, const Texto& esprimo);
    Nenio enmetuŜanĝeblanBuleon(const Texto& nomo, Buleo unuaValoro);
    Nenio enmetuŜanĝeblanNumeron(const Texto& nomo, ℚ8 unuaValoro);
    Nenio enmetuŜanĝeblanVektoron(const Texto& nomo, Vektor2D<ℚ8> unuaValoro);
    Nenio anstataŭiguEsprimon(const Texto& nomo, const Texto& esprimo);
    Buleo provuEnmetiEsprimonBulean(const Texto& nomo, const Texto& esprimo);
    Buleo provuEnmetiEsprimonNumeran(const Texto& nomo, const Texto& esprimo);
    Buleo provuEnmetiEsprimonVektoran(const Texto& nomo, const Texto& esprimo);
    Buleo provuEnmetiŜanĝeblanBuleon(const Texto& nomo, Buleo unuaValoro);
    Buleo provuEnmetiŜanĝeblanNumeron(const Texto& nomo, ℚ8 unuaValoro);
    Buleo provuEnmetiŜanĝeblanVektoron(const Texto& nomo, Vektor2D<ℚ8> unuaValoro);
    Buleo provuAnstataŭigiEsprimon(const Texto& nomo, const Texto& esprimo);
    Nenio forprenu(const Texto& nomo);
    Valoroj renovigu(const Valoroj& valoroj);
    
    Buleo ĉuEnhavasVarieblon(const Texto& nomo) const;
    Buleo ĉuEnhavasBuleon(const Texto& nomo) const;
    Buleo donuBuleon(const Texto& nomo) const;
    Buleo ĉuEnhavasNumeron(const Texto& nomo) const;
    ℚ8 donuNumeron(const Texto& nomo) const;
    Buleo ĉuEnhavasVektoron(const Texto& nomo) const;
    Vektor2D<ℚ8> donuVektoron(const Texto& nomo) const;
    
    Listo<Texto> donuĈiunDependanton(const Texto& nomo) const;
    Listo<Texto> donuĈiunDependaton(const Texto& nomo) const;
    
    Nenio agorduĈuAŭtomatikeEnmetasNeExistantajnValorojn(Buleo b) { _ĉuAŭtomatikeEnmetasNeExistantajnValorojn = b; }
    Buleo ĉuAŭtomatikeEnmetasNeExistantajnValorojn() const { eligu _ĉuAŭtomatikeEnmetasNeExistantajnValorojn; }

private:
    // Ni determinas la dependantojn de esprimo per nombri novajn
    // aperojn de Variebloj dum interpreti textan esprimon.
    // Se oni forprenus esprimon dum ke oni formas novan esprimon,
    // la nova esprimo povus havi malĝustan liston de dependatoj.
    
    template<class _Esprimo>
    struct Esprimo
    {
        using _Valoro = KlasoDe(((_Esprimo*) nullptr)->valoron());
        PropraAdres<_Esprimo> esprimo;
        Listo<Texto> dependantajEsprimoj;
        Listo<Texto> dependatajEsprimoj; // todo
        Buleo ĉuEstasŜanĝeblan;
        _Valoro valoro;
    };
    
    // Oni ankoraŭ devas meti la novan esprimon en la listoj de dependantoj hede ĉiu dependato.
    template<class K>
    Buleo provuKreiEsprimon(const Texto& texto, Esprimo<K>* celo);
    Nenio redeterminuDependantajnEsprimojn(UnikaroPara<Texto, Buleo>* ŝanĝitajBuleoj,
                                           UnikaroPara<Texto, ℚ8>* ŝanĝitajNumeroj,
                                           UnikaroPara<Texto, Vektor2D<ℚ8>>* ŝanĝitajVektoroj);
    
    Buleo ĉuNomoĜustas(const Texto& nomo) const;
    Listo<Texto>& donuDependantojn(const Texto& nomo);
    Listo<Texto>& donuDependatojn(const Texto& nomo);
    const Listo<Texto>& donuDependantojn(const Texto& nomo) const;
    const Listo<Texto>& donuDependatojn(const Texto& nomo) const;
    Nenio metuĈiunDependantonEn(Listo<Texto>* celo, const Texto& nomo) const;
    Nenio metuĈiunDependatonEn(Listo<Texto>* celo, const Texto& nomo) const;
    Eraro formuEraron(const Texto& nomo, const Texto& esprimo, const Texto& speco_adj_akz) const;
    
    UnikaroPara<Texto, ℕ> _dependatoj;
    
    UnikaroPara<Texto, Esprimo<EsprimoBulea>> buleaj;
    UnikaroPara<Texto, Esprimo<EsprimoNumera>> numeraj;
    UnikaroPara<Texto, Esprimo<EsprimoVektora>> vektoraj;
    Valoroj prokrastitajNovajValoroj;
    KolektoDeLegantoj legantoj;
    Buleo _ĉuAŭtomatikeEnmetasNeExistantajnValorojn;

#ifdef _DEBUG
    Listo<Texto> neExistantajŜanĝeblajValoroj;
#endif

#define KREU_SPECON_DE_VARIEBLO(Spec, Valoro) \
    struct Spec##aVarieblo : public Esprimo##Spec##a \
    { \
        struct Leganto : public LegantoDeEsprimo##Spec##a \
        { \
            Leganto(Esprimujo* p_esprimujo) : esprimujo(p_esprimujo) {} \
            \
            Esprimo##Spec##a* provuKreiEl(const Texto& texto, const KolektoDeLegantoj* legantoj) const override \
            { \
                Texto texto2 = texto; \
                texto2.forprenuEksteranBlankanSpacon(); \
                if (esprimujo->ĉuEnhavas##Spec##on(texto2)) \
                    eligu kreu Spec##aVarieblo(texto2, esprimujo); \
                eligu nullptr; \
            } \
            \
            Esprimujo* esprimujo; \
        }; \
        \
        Spec##aVarieblo(const Texto& p_nomo, Esprimujo* p_esprimujo) : nomo(p_nomo), esprimujo(p_esprimujo) \
        { \
            if (esprimujo->_dependatoj.ĉuEnhavas(nomo)) \
                esprimujo->_dependatoj[nomo]++; \
            else esprimujo->_dependatoj[nomo] = 1; \
        } \
        \
        ~Spec##aVarieblo() override \
        { \
            esprimujo->_dependatoj[nomo]--; \
        } \
        \
        Valoro valoron() override { eligu esprimujo->donu##Spec##on(nomo); } \
        Texto alTexto() const override { eligu nomo; } \
        \
        Texto nomo; \
        Esprimujo* esprimujo; \
    };
    
    KREU_SPECON_DE_VARIEBLO(Bule, Buleo);
    KREU_SPECON_DE_VARIEBLO(Numer, ℚ8);
    KREU_SPECON_DE_VARIEBLO(Vektor, Vektor2D<ℚ8>);
#undef KREU_SPECON_DE_VARIEBLO
};

#endif //KOMUNA_ESPRIMUJO_HPP
