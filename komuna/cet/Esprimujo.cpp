#include "Esprimujo.hpp"
#include "../Unikaro.hpp"
#include "../Eraro.hpp"
#include "Leganto.hpp"

Esprimujo::Esprimujo(Buleo p_ĉuAŭtomatikeEnmetasNeExistantajnValorojn, KolektoDeLegantoj p_legantoj)
        : legantoj(formovu(p_legantoj)),
          _ĉuAŭtomatikeEnmetasNeExistantajnValorojn(p_ĉuAŭtomatikeEnmetasNeExistantajnValorojn)
{
    legantoj.buleajLegantoj.enmetuNovan(kreu BuleaVarieblo::Leganto(this));
    legantoj.numerajLegantoj.enmetuNovan(kreu NumeraVarieblo::Leganto(this));
    legantoj.vektorajLegantoj.enmetuNovan(kreu VektoraVarieblo::Leganto(this));
}

Nenio Esprimujo::enmetuEsprimonBulean(const Texto& nomo, const Texto& esprimo)
{
    if (ne provuEnmetiEsprimonBulean(nomo, esprimo))
        throw formuEraron(nomo, esprimo, "bulean");
}

Nenio Esprimujo::enmetuEsprimonNumeran(const Texto& nomo, const Texto& esprimo)
{
    if (ne provuEnmetiEsprimonNumeran(nomo, esprimo))
        throw formuEraron(nomo, esprimo, "numeran");
}

Nenio Esprimujo::enmetuEsprimonVektoran(const Texto& nomo, const Texto& esprimo)
{
    if (ne provuEnmetiEsprimonVektoran(nomo, esprimo))
        throw formuEraron(nomo, esprimo, "vektoran");
}

Nenio Esprimujo::enmetuŜanĝeblanBuleon(const Texto& nomo, Buleo unuaValoro)
{
    if (ne provuEnmetiŜanĝeblanBuleon(nomo, unuaValoro))
        throw Eraro("Ne povis enmeti «" + nomo + "».", "Ĉi-esprimujo jam enhavas tiun nomon.");
}

Nenio Esprimujo::enmetuŜanĝeblanNumeron(const Texto& nomo, ℚ8 unuaValoro)
{
    if (ne provuEnmetiŜanĝeblanNumeron(nomo, unuaValoro))
        throw Eraro("Ne povis enmeti «" + nomo + "».", "Ĉi-esprimujo jam enhavas tiun nomon.");
}

Nenio Esprimujo::enmetuŜanĝeblanVektoron(const Texto& nomo, Vektor2D<ℚ8> unuaValoro)
{
    if (ne provuEnmetiŜanĝeblanVektoron(nomo, unuaValoro))
        throw Eraro("Ne povis enmeti «" + nomo + "».", "Ĉi-esprimujo jam enhavas tiun nomon.");
}

Nenio Esprimujo::anstataŭiguEsprimon(const Texto& nomo, const Texto& esprimo)
{
    if (ne provuAnstataŭigiEsprimon(nomo, esprimo))
        throw Eraro("Ne povis anstataŭigi esprimon «" + nomo + "».", "Ĉi-esprimujo ne enhavas tiun nomon, " //-«
                    "aŭ la nova esprimo «" + esprimo + "» ne ĝustas por la speco de «" + nomo + "»."); //»-
}

Buleo Esprimujo::provuEnmetiEsprimonBulean(const Texto& nomo, const Texto& esprimo)
{
    if (ĉuEnhavasVarieblon(nomo) aŭ ne ĉuNomoĜustas(nomo))
        eligu malveran;
    
    Esprimo<EsprimoBulea> rezulto;
    if (ne provuKreiEsprimon(esprimo, &rezulto))
        eligu malveran;
    Buleo valoro = rezulto.valoro;
    
    for (const Texto& dependato : rezulto.dependatajEsprimoj)
        donuDependantojn(dependato).enmetu(nomo);
    
    buleaj.enmetu(Texto(nomo), formovu(rezulto));
    prokrastitajNovajValoroj.buleoj.enmetu(nomo, valoro);
    eligu veran;
}

Buleo Esprimujo::provuEnmetiEsprimonNumeran(const Texto& nomo, const Texto& esprimo)
{
    if (ĉuEnhavasVarieblon(nomo) aŭ ne ĉuNomoĜustas(nomo))
        eligu malveran;
    
    Esprimo<EsprimoNumera> rezulto;
    if (ne provuKreiEsprimon(esprimo, &rezulto))
        eligu malveran;
    ℚ8 valoro = rezulto.valoro;
    
    for (const Texto& dependato : rezulto.dependatajEsprimoj)
        donuDependantojn(dependato).enmetu(nomo);
    
    numeraj.enmetu(Texto(nomo), formovu(rezulto));
    prokrastitajNovajValoroj.numeroj.enmetu(nomo, valoro);
    eligu veran;
}

Buleo Esprimujo::provuEnmetiEsprimonVektoran(const Texto& nomo, const Texto& esprimo)
{
    if (ĉuEnhavasVarieblon(nomo) aŭ ne ĉuNomoĜustas(nomo))
        eligu malveran;
    
    Esprimo<EsprimoVektora> rezulto;
    if (ne provuKreiEsprimon(esprimo, &rezulto))
        eligu malveran;
    Vektor2D<ℚ8> valoro = rezulto.valoro;
    
    for (const Texto& dependato : rezulto.dependatajEsprimoj)
        donuDependantojn(dependato).enmetu(nomo);
    
    vektoraj.enmetu(Texto(nomo), formovu(rezulto));
    prokrastitajNovajValoroj.vektoroj.enmetu(nomo, valoro);
    eligu veran;
}

Buleo Esprimujo::provuEnmetiŜanĝeblanBuleon(const Texto& nomo, Buleo unuaValoro)
{
    if (ĉuEnhavasVarieblon(nomo) aŭ ne ĉuNomoĜustas(nomo))
        eligu malveran;
    Esprimo<EsprimoBulea> esprimo;
    esprimo.ĉuEstasŜanĝeblan = veran;
    esprimo.valoro = unuaValoro;
    buleaj.enmetu(Texto(nomo), formovu(esprimo));
    eligu veran;
}

Buleo Esprimujo::provuEnmetiŜanĝeblanNumeron(const Texto& nomo, ℚ8 unuaValoro)
{
    if (ĉuEnhavasVarieblon(nomo) aŭ ne ĉuNomoĜustas(nomo))
        eligu malveran;
    Esprimo<EsprimoNumera> esprimo;
    esprimo.ĉuEstasŜanĝeblan = veran;
    esprimo.valoro = unuaValoro;
    numeraj.enmetu(Texto(nomo), formovu(esprimo));
    eligu veran;
}

Buleo Esprimujo::provuEnmetiŜanĝeblanVektoron(const Texto& nomo, Vektor2D<ℚ8> unuaValoro)
{
    if (ĉuEnhavasVarieblon(nomo) aŭ ne ĉuNomoĜustas(nomo))
        eligu malveran;
    Esprimo<EsprimoVektora> esprimo;
    esprimo.ĉuEstasŜanĝeblan = veran;
    esprimo.valoro = unuaValoro;
    vektoraj.enmetu(Texto(nomo), formovu(esprimo));
    eligu veran;
}

Buleo Esprimujo::provuAnstataŭigiEsprimon(const Texto& nomo, const Texto& texto)
{
    auto ĉuEsprimoRekursas = [this](const Texto& nomo, Listo<Texto> dependatoj)
    {
        for (ℕ i = 0; i < dependatoj.grandon(); i++)
        {
            const Texto& dependato = dependatoj[i];
            for (const Texto& novaDependato : donuDependatojn(dependato))
            {
                if (novaDependato == nomo)
                    eligu veran;
                if (ne dependatoj.ĉuEnhavas(novaDependato))
                    dependatoj.enmetu(novaDependato);
            }
        }
        
        eligu malveran;
    };
    
    auto _provuAnstataŭigiEsprimon = [this, &ĉuEsprimoRekursas]
            (const Texto& nomo, const Texto& texto, auto malnovaEsprimo) -> Buleo
    {
        KlasoDeAdres(malnovaEsprimo) novaEsprimo;
        if (malnovaEsprimo->ĉuEstasŜanĝeblan
            aŭ ne provuKreiEsprimon(texto, &novaEsprimo)
            aŭ ĉuEsprimoRekursas(nomo, novaEsprimo.dependatajEsprimoj))
            eligu malveran;
        for (const Texto& dependata : malnovaEsprimo->dependatajEsprimoj)
            donuDependantojn(dependata).forprenuĈiun(nomo);
        for (const Texto& dependata : novaEsprimo.dependatajEsprimoj)
            donuDependantojn(dependata).enmetu(nomo);
        novaEsprimo.dependantajEsprimoj = formovu(malnovaEsprimo->dependantajEsprimoj);
        *malnovaEsprimo = formovu(novaEsprimo);
        eligu veran;
    };
    
    
    UnikaroPara<Texto, Vektor2D<ℚ8>> ŝanĝitajVektoroj;
    
    if (ĉuEnhavasBuleon(nomo))
    {
        Esprimo<EsprimoBulea>* esprimo = &buleaj[nomo];
        Buleo valoroUnue = esprimo->valoro;
        if (ne _provuAnstataŭigiEsprimon(nomo, texto, esprimo))
            eligu malveran;
        if (esprimo->valoro != valoroUnue)
            prokrastitajNovajValoroj.buleoj.enmetu(nomo, esprimo->valoro);
    }
    else if (ĉuEnhavasNumeron(nomo))
    {
        Esprimo<EsprimoNumera>* esprimo = &numeraj[nomo];
        ℚ8 valoroUnue = esprimo->valoro;
        if (ne _provuAnstataŭigiEsprimon(nomo, texto, esprimo))
            eligu malveran;
        if (esprimo->valoro != valoroUnue)
            prokrastitajNovajValoroj.numeroj.enmetu(nomo, esprimo->valoro);
    }
    else if (ĉuEnhavasVektoron(nomo))
    {
        Esprimo<EsprimoVektora>* esprimo = &vektoraj[nomo];
        Vektor2D<ℚ8> valoroUnue = esprimo->valoro;
        if (ne _provuAnstataŭigiEsprimon(nomo, texto, esprimo))
            eligu malveran;
        if (esprimo->valoro != valoroUnue)
            prokrastitajNovajValoroj.vektoroj.enmetu(nomo, esprimo->valoro);
    }
    else
        eligu malveran;
    
    redeterminuDependantajnEsprimojn(&prokrastitajNovajValoroj.buleoj,
                                     &prokrastitajNovajValoroj.numeroj,
                                     &prokrastitajNovajValoroj.vektoroj);
    eligu veran;
}

Nenio Esprimujo::forprenu(const Texto& nomo)
{
    if (ne donuDependantojn(nomo).ĉuEstasMalplenan())
        throw Eraro("Ne povis forpreni esprimon «" + nomo + "»", "La esprimo ankoraŭ havas dependantojn,"
                                                                 "exemple «" + donuDependantojn(nomo)[0] + "».");
    for (const Texto& dependato : donuDependatojn(nomo))
        donuDependantojn(dependato).forprenuĈiun(nomo);
    buleaj.forprenu(nomo);
    numeraj.forprenu(nomo);
    vektoraj.forprenu(nomo);
}

Esprimujo::Valoroj Esprimujo::renovigu(const Valoroj& valoroj)
{
    auto ŝanĝuVarieblojn = [this](auto& ebleŜanĝotaj, auto& esprimoj, auto& ŝanĝitaj, auto enmetuŜanĝeblan)
    {
        for (const auto& paro : ebleŜanĝotaj)
        {
            const Texto& nomo = paro.first;
            const auto& novaValoro = paro.second;
            
            if (ne esprimoj.ĉuEnhavas(nomo))
            {
                if (ĉuAŭtomatikeEnmetasNeExistantajnValorojn())
                    (this->*enmetuŜanĝeblan)(nomo, novaValoro);
#ifdef _DEBUG
                else if (ne neExistantajŜanĝeblajValoroj.ĉuEnhavas(nomo))
                {
                    neExistantajŜanĝeblajValoroj.enmetu(nomo);
                    std::cerr << "Ŝanĝebla valoro «" + nomo.STL() + "» ne existas!" << std::endl;
                }
#endif
                saltu_al_sekva;
            }
            
            auto& esprimo = esprimoj[nomo];
            if (ne esprimo.ĉuEstasŜanĝeblan aŭ esprimo.valoro == novaValoro)
                saltu_al_sekva;
            
            esprimo.valoro = novaValoro;
            ŝanĝitaj[nomo] = novaValoro;
        }
    };
    
    Valoroj ŝanĝitajValoroj;
    ŝanĝuVarieblojn(valoroj.buleoj, buleaj, ŝanĝitajValoroj.buleoj, &Esprimujo::enmetuŜanĝeblanBuleon);
    ŝanĝuVarieblojn(valoroj.numeroj, numeraj, ŝanĝitajValoroj.numeroj, &Esprimujo::enmetuŜanĝeblanNumeron);
    ŝanĝuVarieblojn(valoroj.vektoroj, vektoraj, ŝanĝitajValoroj.vektoroj, &Esprimujo::enmetuŜanĝeblanVektoron);
    redeterminuDependantajnEsprimojn(&ŝanĝitajValoroj.buleoj, &ŝanĝitajValoroj.numeroj, &ŝanĝitajValoroj.vektoroj);
    eligu ŝanĝitajValoroj;
}

Buleo Esprimujo::ĉuEnhavasVarieblon(const Texto& nomo) const
{
    eligu buleaj.ĉuEnhavas(nomo) aŭ numeraj.ĉuEnhavas(nomo) aŭ vektoraj.ĉuEnhavas(nomo);
}

Buleo Esprimujo::ĉuEnhavasBuleon(const Texto& nomo) const { eligu buleaj.ĉuEnhavas(nomo); } //-«
Buleo Esprimujo::donuBuleon(const Texto& nomo) const { premisu (buleaj.ĉuEnhavas(nomo)); eligu buleaj[nomo].valoro; }
Buleo Esprimujo::ĉuEnhavasNumeron(const Texto& nomo) const { eligu numeraj.ĉuEnhavas(nomo); }
ℚ8 Esprimujo::donuNumeron(const Texto& nomo) const { premisu (numeraj.ĉuEnhavas(nomo)); eligu numeraj[nomo].valoro; }
Buleo Esprimujo::ĉuEnhavasVektoron(const Texto& nomo) const { eligu vektoraj.ĉuEnhavas(nomo); } //»-
Vektor2D<ℚ8> Esprimujo::donuVektoron(const Texto& nomo) const
{
    premisu (vektoraj.ĉuEnhavas(nomo));
    eligu vektoraj[nomo].valoro;
}

Listo<Texto> Esprimujo::donuĈiunDependanton(const Texto& nomo) const
{
    Listo<Texto> dependantoj;
    metuĈiunDependatonEn(&dependantoj, nomo);
    for (ℕ i = 0; i < dependantoj.grandon(); i++)
        metuĈiunDependatonEn(&dependantoj, dependantoj[i]);
    eligu dependantoj;
}

Listo<Texto> Esprimujo::donuĈiunDependaton(const Texto& nomo) const
{
    Listo<Texto> dependatoj;
    metuĈiunDependatonEn(&dependatoj, nomo);
    for (ℕ i = 0; i < dependatoj.grandon(); i++)
        metuĈiunDependatonEn(&dependatoj, dependatoj[i]);
    eligu dependatoj;
}

template<class K>
Buleo Esprimujo::provuKreiEsprimon(const Texto& texto, Esprimujo::Esprimo<K>* celo)
{
    Esprimo<K> rezulto;
    _dependatoj.malplenigu();
    rezulto.esprimo.reset(provuKreiEsprimonEl<K>(texto, &legantoj));
    rezulto.ĉuEstasŜanĝeblan = malveran;
    
    if (rezulto.esprimo == nullptr)
    {
        _dependatoj.malplenigu();
        eligu malveran;
    }
    
    for (const auto& paro : _dependatoj)
        if (paro.second != 0)
            rezulto.dependatajEsprimoj.enmetu(paro.first);
    
    rezulto.valoro = rezulto.esprimo->valoron();
    _dependatoj.malplenigu();
    
    *celo = formovu(rezulto);
    eligu veran;
}

Nenio Esprimujo::redeterminuDependantajnEsprimojn(UnikaroPara<Texto, Buleo>* ŝanĝitajBuleoj,
                                                  UnikaroPara<Texto, ℚ8>* ŝanĝitajNumeroj,
                                                  UnikaroPara<Texto, Vektor2D<ℚ8>>* ŝanĝitajVektoroj)
{
    auto elprenuTraktotajnEsprimojnDisenTraktotajDependatoj = [this](Listo<Texto>* traktotajEsprimoj) -> Listo<Texto>
    {
        Listo<Texto> traktotajEsprimojDisenTraktotajDependatoj;
        
        auto ĉuHavasTraktotanDependaton = [&](const Texto& nomo)
        {
            for (const Texto& dependato : donuDependatojn(nomo))
                if (traktotajEsprimoj->ĉuEnhavas(dependato)
                    aŭ traktotajEsprimojDisenTraktotajDependatoj.ĉuEnhavas(nomo))
                    eligu veran;
            eligu malveran;
        };
        
        for (ℕ i = 0; i < traktotajEsprimoj->grandon();)
        {
            Texto& nomo = traktotajEsprimoj->donu(i);
            
            if (ĉuHavasTraktotanDependaton(nomo))
                i++;
            else
            {
                traktotajEsprimojDisenTraktotajDependatoj.enmetu(formovu(nomo));
                traktotajEsprimoj->forprenu(i);
            }
        }
        
        eligu traktotajEsprimojDisenTraktotajDependatoj;
    };
    
    auto redeterminuEsprimon = [](const Texto& nomo, auto& esprimaro, auto ŝanĝitajValoroj)
    {
        auto& esprimo = esprimaro[nomo]; //-«
        premisu (ne esprimo.ĉuEstasŜanĝeblan); //»-
        premisu (esprimo.esprimo != nullptr);
        auto novaValoro = esprimo.esprimo->valoron();
        if (novaValoro != esprimo.valoro)
            ŝanĝitajValoroj->enmetu(nomo, novaValoro);
        esprimo.valoro = novaValoro;
    };
    
    auto redeterminuEsprimojn = [&](const Listo<Texto>& esprimoj)
    {
        for (const Texto& nomo : esprimoj)
        {
            if (ĉuEnhavasBuleon(nomo))
                redeterminuEsprimon(nomo, buleaj, ŝanĝitajBuleoj);
            else if (ĉuEnhavasNumeron(nomo))
                redeterminuEsprimon(nomo, numeraj, ŝanĝitajNumeroj);
            else if (ĉuEnhavasVektoron(nomo))
                redeterminuEsprimon(nomo, vektoraj, ŝanĝitajVektoroj); //-«
            else kraŝu; //»-
        }
    };
    
    
    Listo<Texto> traktotajEsprimoj;
    
    for (const auto& ŝanĝitaBuleo : *ŝanĝitajBuleoj)
        metuĈiunDependantonEn(&traktotajEsprimoj, ŝanĝitaBuleo.first);
    for (const auto& ŝanĝitaNumero : *ŝanĝitajNumeroj)
        metuĈiunDependantonEn(&traktotajEsprimoj, ŝanĝitaNumero.first);
    for (const auto& ŝanĝitaVektoro : *ŝanĝitajVektoroj)
        metuĈiunDependantonEn(&traktotajEsprimoj, ŝanĝitaVektoro.first);
    for (ℕ i = 0; i < traktotajEsprimoj.grandon(); i++) // norma luso ĉar oni ŝanĝas traktotajnEsprimojn en ĉi-luso
        metuĈiunDependantonEn(&traktotajEsprimoj, traktotajEsprimoj[i]);
    
    while (ne traktotajEsprimoj.ĉuEstasMalplenan())
    {
        Listo<Texto> traktotajEsprimojDisenTraktotajDependatoj =
                elprenuTraktotajnEsprimojnDisenTraktotajDependatoj(&traktotajEsprimoj);
        
        if (traktotajEsprimojDisenTraktotajDependatoj.ĉuEstasMalplenan())
            // iuj rekursivaj esprimoj estas den traktotajEsprimoj
            redeterminuEsprimojn(traktotajEsprimoj); // ignoru rekursivecon, rompas la esprimojn
        else redeterminuEsprimojn(traktotajEsprimojDisenTraktotajDependatoj);
    }
}

Buleo Esprimujo::ĉuNomoĜustas(const Texto& nomo) const
{
    const static std::regex regex("^[a-zA-ZĈĉĜĝĤĥŜŝŬŭ_][a-zA-Z0-9ĈĉĜĝĤĥŜŝŬŭ_]*$");
    const static Listo<Texto> reservatajWortoj = {"kaj", "ne", "aŭ", "au", "T", "v"};
    eligu ne nomo.trovuRegex(regex).ĉuEstasMalplenan()
          kaj ne reservatajWortoj.ĉuEnhavas(nomo);
}

Listo<Texto>& Esprimujo::donuDependantojn(const Texto& nomo)
{
    if (ĉuEnhavasBuleon(nomo))
        eligu buleaj[nomo].dependantajEsprimoj;
    if (ĉuEnhavasNumeron(nomo))
        eligu numeraj[nomo].dependantajEsprimoj;
    premisu (ĉuEnhavasVektoron(nomo));
    eligu vektoraj[nomo].dependantajEsprimoj;
}

Listo<Texto>& Esprimujo::donuDependatojn(const Texto& nomo)
{
    if (ĉuEnhavasBuleon(nomo))
        eligu buleaj[nomo].dependatajEsprimoj;
    if (ĉuEnhavasNumeron(nomo))
        eligu numeraj[nomo].dependatajEsprimoj;
    premisu (ĉuEnhavasVektoron(nomo));
    eligu vektoraj[nomo].dependatajEsprimoj;
}

const Listo<Texto>& Esprimujo::donuDependantojn(const Texto& nomo) const
{
    if (ĉuEnhavasBuleon(nomo))
        eligu buleaj[nomo].dependantajEsprimoj;
    if (ĉuEnhavasNumeron(nomo))
        eligu numeraj[nomo].dependantajEsprimoj;
    premisu (ĉuEnhavasVektoron(nomo));
    eligu vektoraj[nomo].dependantajEsprimoj;
}

const Listo<Texto>& Esprimujo::donuDependatojn(const Texto& nomo) const
{
    if (ĉuEnhavasBuleon(nomo))
        eligu buleaj[nomo].dependatajEsprimoj;
    if (ĉuEnhavasNumeron(nomo))
        eligu numeraj[nomo].dependatajEsprimoj;
    premisu (ĉuEnhavasVektoron(nomo));
    eligu vektoraj[nomo].dependatajEsprimoj;
}

Nenio Esprimujo::metuĈiunDependantonEn(Listo<Texto>* celo, const Texto& nomo) const
{
    for (const Texto& dependanto : donuDependantojn(nomo))
        if (ne celo->ĉuEnhavas(dependanto))
            celo->enmetu(dependanto);
}

Nenio Esprimujo::metuĈiunDependatonEn(Listo<Texto>* celo, const Texto& nomo) const
{
    for (const Texto& dependanto : donuDependatojn(nomo))
        if (ne celo->ĉuEnhavas(dependanto))
            celo->enmetu(dependanto);
}

Eraro Esprimujo::formuEraron(const Texto& nomo, const Texto& esprimo, const Texto& speco_adj_akz) const
{
    eligu Eraro("Ne povis enmeti esprimon «" + nomo + "».",
                "Ĉi-esprimujo jam enhavas iun esprimon dikun nomo «" + nomo +
                "» aŭ «" + esprimo + "» ne estas ĝustan " + speco_adj_akz + " esprimon");
}