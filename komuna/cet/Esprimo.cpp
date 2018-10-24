#include "Esprimo.hpp"
#include "../torent/TorentoTexta.hpp"
#include "Leganto.hpp"
#include "Lokaĵaro.hpp"


Buleo realigo::provuLegiUnuOperaciatonEl
        (const Texto& texto, const Listo<Texto>& eblajKomencoj, const Listo<Texto>& eblajFinoj, Texto* operaciato)
{
    premisu (ne eblajKomencoj.ĉuEnhavas("") aŭ eblajKomencoj.grandon() == 1);
    premisu (ne eblajFinoj.ĉuEnhavas("") aŭ eblajFinoj.grandon() == 1);
    Texto texto2 = texto;
    TorentoTexta torento(&texto2, 0);
    ::Leganto leganto(&torento);
    leganto.saltuPostBlankanSpacon();
    ℕ aperitaKomenco = leganto.rekonuĈiAperonDeIuAnoDe(eblajKomencoj);
    if (aperitaKomenco == Leganto::neniu_rezulto
        aŭ ne leganto.provuPaŝiAntaŭen(eblajKomencoj[aperitaKomenco].grandon()))
        eligu malveran;
    ℤ8 komencoDeOperaciato = leganto.donuLokon();
    ℕ aperitaFino = 0;
    if (eblajFinoj.ĉuEnhavas(""))
        leganto.iruAlFino();
    else if (ne leganto.provuIriAlUnuaAperoDiexterKrampojHede(eblajFinoj, &aperitaFino))
        eligu malveran;
    ℤ8 finoDeOperaciato = leganto.donuLokon();
    leganto.provuPaŝiAntaŭen(eblajFinoj[aperitaFino].grandon());
    leganto.saltuPostBlankanSpacon();
    if (leganto.provuPaŝiAntaŭen())
        eligu malveran;
    *operaciato = leganto.donuPartonInter(komencoDeOperaciato, finoDeOperaciato);
    eligu veran;
}

Buleo realigo::provuLegiDuOperaciatojnEl
        (const Texto& texto, const Texto& unuaKrampo, const Listo<Texto>& eblajOperaciantoj,
         const Texto& duaKrampo, Texto* unuaOperaciato, Texto* duaOperaciato)
{
    Texto texto2 = texto;
    TorentoTexta torento(&texto2, 0);
    ::Leganto leganto(&torento);
    premisu (leganto.donuLokon() != -1);
    leganto.saltuPostBlankanSpacon();
    if (ne leganto.ĉuEstasDiĉeKomencoDe(unuaKrampo) aŭ ne leganto.provuPaŝiAntaŭen(unuaKrampo.grandon()))
        eligu malveran;
    ℤ8 komencoDeUnuaOperaciato = leganto.donuLokon();
    ℕ trovato;
    if (ne leganto.provuIriAlUnuaAperoDiexterKrampojHede(eblajOperaciantoj, &trovato))
        eligu malveran;
    ℤ8 finoDeUnuaOperaciato = leganto.donuLokon();
    if (ne leganto.provuPaŝiAntaŭen(eblajOperaciantoj[trovato].grandon()))
        eligu malveran;
    ℤ8 komencoDeDuaOperaciato = leganto.donuLokon();
    if (duaKrampo.ĉuEstasMalplenan())
        leganto.iruAlFino();
    else if (ne leganto.provuIriAlUnuaAperoDiexterKrampoj(duaKrampo))
        eligu malveran;
    ℤ8 finoDeDuaOperaciato = leganto.donuLokon();
    leganto.provuPaŝiAntaŭen(duaKrampo.grandon());
    leganto.saltuPostBlankanSpacon();
    if (leganto.provuPaŝiAntaŭen())
        eligu malveran;
    *unuaOperaciato = leganto.donuPartonInter(komencoDeUnuaOperaciato, finoDeUnuaOperaciato);
    *duaOperaciato = leganto.donuPartonInter(komencoDeDuaOperaciato, finoDeDuaOperaciato);
    eligu veran;
}

Buleo realigo::provuLegiTriOperaciatojnEl
        (const Texto& texto, const Texto& unuaKrampo,
         const Listo<Texto>& eblajUnuajOperaciantoj, const Listo<Texto>& eblajDuajOperaciantoj,
         const Texto& duaKrampo, Texto* unuaOperaciato, Texto* duaOperaciato, Texto* triaOperaciato)
{
    Texto texto2 = texto;
    TorentoTexta torento(&texto2, 0);
    ::Leganto leganto(&torento);
    leganto.saltuPostBlankanSpacon();
    if (ne leganto.ĉuEstasDiĉeKomencoDe(unuaKrampo) aŭ ne leganto.provuPaŝiAntaŭen(unuaKrampo.grandon()))
        eligu malveran;
    ℕ unuaOperacianto;
    ℤ8 komencoDeUnuaOperaciato = leganto.donuLokon();
    if (ne leganto.provuIriAlUnuaAperoDiexterKrampojHede(eblajUnuajOperaciantoj, &unuaOperacianto))
        eligu malveran;
    ℤ8 finoDeUnuaOperaciato = leganto.donuLokon();
    if (ne leganto.provuPaŝiAntaŭen(eblajUnuajOperaciantoj[unuaOperacianto].grandon()))
        eligu malveran;
    ℕ duaOperacianto;
    ℤ8 komencoDeDuaOperaciato = leganto.donuLokon();
    if (ne leganto.provuIriAlUnuaAperoDiexterKrampojHede(eblajDuajOperaciantoj, &duaOperacianto))
        eligu malveran;
    ℤ8 finoDeDuaOperaciato = leganto.donuLokon();
    if (ne leganto.provuPaŝiAntaŭen(eblajDuajOperaciantoj[duaOperacianto].grandon()))
        eligu malveran;
    ℤ8 komencoDeTriaOperaciato = leganto.donuLokon();
    if (ne leganto.provuIriAlUnuaAperoDiexterKrampoj(duaKrampo))
        eligu malveran;
    ℤ8 finoDeTriaOperaciato = leganto.donuLokon();
    leganto.provuPaŝiAntaŭen(duaKrampo.grandon());
    leganto.saltuPostBlankanSpacon();
    if (leganto.provuPaŝiAntaŭen())
        eligu malveran;
    *unuaOperaciato = leganto.donuPartonInter(komencoDeUnuaOperaciato, finoDeUnuaOperaciato);
    *duaOperaciato = leganto.donuPartonInter(komencoDeDuaOperaciato, finoDeDuaOperaciato);
    *triaOperaciato = leganto.donuPartonInter(komencoDeTriaOperaciato, finoDeTriaOperaciato);
    eligu veran;
}

#define KBU(x) PropraAdres<LegantoDeEsprimoBulea>(kreu bulea::x::Leganto)
#define KNU(x) PropraAdres<LegantoDeEsprimoNumera>(kreu numera::x::Leganto)
#define KVE(x) PropraAdres<LegantoDeEsprimoVektora>(kreu vektora::x::Leganto)

KolektoDeLegantoj KolektoDeLegantoj::kreuBazanKolekton()
{
    KolektoDeLegantoj kolekto;
    PropraAdres<LegantoDeEsprimoBulea> buleaj[] =
            {KBU(Konstanto), KBU(Kaj), KBU(Aŭ), KBU(Ne), KBU(Egalas),
             KBU(PliGrandanOl), KBU(MalpliGrandanOl), KBU(Baskulu), KBU(NeBezonatajKrampoj)};
    PropraAdres<LegantoDeEsprimoNumera> numeraj[] =
            {KNU(Konstanto), KNU(Adico), KNU(Subtraho), KNU(Multipliko), KNU(Divido),
             KNU(ElektoNumera), KNU(Unua), KNU(Dua), KNU(Normo), KNU(NeBezonatajKrampoj)};
    PropraAdres<LegantoDeEsprimoVektora> vektoraj[] =
            {KVE(Komponu), KVE(Multipliko), KVE(ElektoVektora), KVE(NeBezonatajKrampoj)};
    
    for (PropraAdres<LegantoDeEsprimoBulea>& leganto : buleaj)
        kolekto.buleajLegantoj.enmetu(formovu(leganto));
    for (PropraAdres<LegantoDeEsprimoNumera>& leganto : numeraj)
        kolekto.numerajLegantoj.enmetu(formovu(leganto));
    for (PropraAdres<LegantoDeEsprimoVektora>& leganto : vektoraj)
        kolekto.vektorajLegantoj.enmetu(formovu(leganto));
    eligu formovu(kolekto);
}

#undef KBU
#undef KNU
#undef KVE

EsprimoBulea* KolektoDeLegantoj::provuKreiBuleanEsprimonEl(const Texto& texto) const
{
    for (const PropraAdres<LegantoDeEsprimoBulea>& leganto : buleajLegantoj)
    {
        EsprimoBulea* esprimo = leganto->provuKreiEl(texto, this);
        if (esprimo != nullptr)
            eligu esprimo;
    }
    
    eligu nullptr;
}

EsprimoNumera* KolektoDeLegantoj::provuKreiNumeranEsprimonEl(const Texto& texto) const
{
    for (const PropraAdres<LegantoDeEsprimoNumera>& leganto : numerajLegantoj)
    {
        EsprimoNumera* esprimo = leganto->provuKreiEl(texto, this);
        if (esprimo != nullptr)
            eligu esprimo;
    }
    
    eligu nullptr;
}

EsprimoVektora* KolektoDeLegantoj::provuKreiVektoranEsprimonEl(const Texto& texto) const
{
    for (const PropraAdres<LegantoDeEsprimoVektora>& leganto : vektorajLegantoj)
    {
        EsprimoVektora* esprimo = leganto->provuKreiEl(texto, this);
        if (esprimo != nullptr)
            eligu esprimo;
    }
    
    eligu nullptr;
}

EsprimoBulea* bulea::Konstanto::Leganto::provuKreiEl(const Texto& texto, const KolektoDeLegantoj* legantoj) const
{
    Listo<Texto> veraj = {"vera", "veran", "⊤", "T", "1", "true"};
    Listo<Texto> malveraj = {"malvera", "malveran", "⊥", "0", "false"};
    
    auto kreuKonstanton = [&](Buleo valoro) -> Konstanto*
    {
        Konstanto* konstanto = kreu Konstanto;
        konstanto->valoro = valoro;
        eligu konstanto;
    };
    
    Texto texto2 = texto;
    texto2.forprenuEksteranBlankanSpacon();
    
    if (veraj.ĉuEnhavas(texto2))
        eligu kreuKonstanton(veran);
    else if (malveraj.ĉuEnhavas(texto2))
        eligu kreuKonstanton(malveran);
    else
        eligu nullptr;
}

EsprimoNumera* numera::Konstanto::Leganto::provuKreiEl(const Texto& texto, const KolektoDeLegantoj* legantoj) const
{
    const static Listo<Texto> aliaj_akceptataj_karakteroj = {".", ",", "-"};
    
    for (char karaktero : texto)
    {
        Texto tKaraktero = {karaktero};
        if (ne blankspacaj_karakteroj.ĉuEnhavas(tKaraktero)
            kaj ne numeraj_karakteroj.ĉuEnhavas(tKaraktero)
            kaj ne aliaj_akceptataj_karakteroj.ĉuEnhavas(tKaraktero))
            eligu nullptr;
    }
    
    ℚ8 valoro;
    std::istringstream torento(texto.STL(), std::ios::in | std::ios::binary);
    torento.imbue(normaLokaĵaro);
    
    try { torento >> valoro; }
    catch (std::ios_base::failure& e) { eligu nullptr; }
    
    PropraAdres<Konstanto> konstanto(kreu Konstanto);
    konstanto->valoro = valoro;
    eligu konstanto.release();
}
