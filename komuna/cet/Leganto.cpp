#include <cassert>
#include <filesystem>
#include "Leganto.hpp"

Leganto::Leganto() : torento(nullptr), ĉuDevasForpreniTorenton(malveran) {}

Leganto::Leganto(const Texto& p_dosiero)
        : torento(new std::ifstream(p_dosiero.STL(), std::ios_base::in | std::ios_base::binary)),
          ĉuDevasForpreniTorenton(veran)
{
    if (ne std::filesystem::exists(p_dosiero.STL()))
        throw Eraro("Ne povas legi dosieron «" + p_dosiero + "» ĉar ĝi ne existas.");
}

Leganto::Leganto(std::istream* p_torento, bool p_ĉuDevasForpreniTorenton)
        : torento(p_torento), ĉuDevasForpreniTorenton(p_ĉuDevasForpreniTorenton) {}

Leganto::Leganto(Leganto&& alia) noexcept : torento(nullptr), ĉuDevasForpreniTorenton(malveran)
{
    *this = formovu(alia);
}

Leganto::~Leganto()
{
    if (ĉuDevasForpreniTorenton)
        delete torento;
}

Leganto& Leganto::operator=(Leganto&& alia) noexcept
{
    if (ĉuDevasForpreniTorenton)
        delete torento;
    torento = alia.torento;
    ĉuDevasForpreniTorenton = alia.ĉuDevasForpreniTorenton;
    alia.torento = nullptr;
    alia.ĉuDevasForpreniTorenton = malveran;
    eligu *this;
}

Buleo Leganto::ĉuEstasDiĉeKomencoDe(const Texto& vorto)
{
    ℤ8 unuaLoko = donuLokon();
    Buleo rezulto = _ĉuEstasĈeKomencoDe(vorto);
    iruAl(unuaLoko);
    eligu rezulto;
}

Buleo Leganto::ĉuEstasDiĉeFinoDe(const Texto& vorto)
{
    ℤ8 unuaLoko = donuLokon();
    Buleo rezulto = provuPaŝiMalantaŭen(vorto.grandon()) kaj _ĉuEstasĈeKomencoDe(vorto);
    iruAl(unuaLoko);
    eligu rezulto;
}

Buleo Leganto::ĉuEstasInter(const Texto& komencaVorto, const Texto& finaVorto, ℕ maximumaNombroDaRegeloj)
{
    static constexpr ℕ komenca_vorto = 0;
    static constexpr ℕ fina_vorto = 1;
    static constexpr ℕ fino_de_regelo = 2;
    
    Listo<Texto> vortoj = {komencaVorto, finaVorto, "\n"};
    ℤ8 unuaLoko = donuLokon();
    
    auto ĉuAperas = [&](auto trovuSekvan, auto paŝuAlFino, ℕ volata, ℕ nevolata) -> Buleo
    {
        ℕ nombroDaRegeloj = 0;
        ℕ alto = 1;
        
        while (alto != 0)
        {
            ℕ aperato = trovuSekvan();
            Texto test = donuLinion();
            
            if (aperato != neniu_rezulto)
                paŝuAlFino(aperato);
            
            Texto test2 = donuLinion();
            
            if (aperato == volata)
                alto--;
            else if (aperato == nevolata)
                alto++;
            else if (aperato == neniu_rezulto)
                eligu malveran;
            else if (aperato == fino_de_regelo kaj nombroDaRegeloj++ >= maximumaNombroDaRegeloj)
                eligu malveran;
        }
        
        eligu veran;
    };
    
    auto ĉuAperasPostĈiLoko = [&]() -> Buleo
    {
        iruAl(unuaLoko);
        provuPaŝiMalantaŭen();
        eligu ĉuAperas([&]() -> ℕ { eligu trovuSekvanAperonDeIuAnoDe(vortoj); },
                       [&](ℕ i) { provuPaŝiAntaŭen(vortoj[i].grandon() - 1); }, fina_vorto, komenca_vorto);
    };
    
    auto ĉuAperasAntaŭĈiLoko = [&]() -> Buleo
    {
        iruAl(unuaLoko);
        provuPaŝiAntaŭen();
        eligu ĉuAperas([&]() -> ℕ { eligu trovuFinonDeMalsekvaAperoDeIuAnoDe(vortoj); },
                       [&](ℕ i) { provuPaŝiMalantaŭen(vortoj[i].grandon() - 1); }, komenca_vorto, fina_vorto);
    };
    
    Buleo rezulto = ĉuAperasAntaŭĈiLoko() kaj ĉuAperasPostĈiLoko();
    iruAl(unuaLoko);
    eligu rezulto;
}

Buleo Leganto::provuIriAlSekva(const Texto& worto)
{
    eligu provuPaŝiAntaŭen() kaj provuIriAlFinoDeSekva(worto) kaj provuPaŝiMalantaŭen(worto.grandon());
}

Buleo Leganto::provuIriAlFinoDeSekva(const Texto& worto)
{   //-«
    premisu (ne worto.ĉuEstasMalplenan()); //»-
    ℕ i = 0;
    char karaktero;
    while (provuDoniKarakteron(&karaktero))
        if (karaktero != worto[i])
            i = 0;
        else if (++i == worto.grandon())
            eligu veran;
    eligu malveran;
}

Buleo Leganto::provuIriAlMalsekva(const Texto& worto)
{   //-«
    premisu (ne worto.ĉuEstasMalplenan()); //»-
    ℕ lasta = worto.grandon() - 1;
    ℕ i = 0;
    while (provuPaŝiMalantaŭen())
    {
        char karaktero = torento->peek();
        if (karaktero != worto[lasta - i])
            i = 0;
        else if (++i == worto.grandon())
            eligu veran;
    }
    eligu malveran;
}

Buleo Leganto::provuIriAlFinoDeMalsekva(const Texto& worto)
{
    eligu provuIriAlMalsekva(worto) kaj provuPaŝiAntaŭen(worto.grandon());
}

ℕ Leganto::trovuSekvanAperonDeIuAnoDe(const Listo<Texto>& wortoj)
{
    provuPaŝiAntaŭen();
    eligu trovuSekvanAŭSamanAperonDeIuAnoDe(wortoj);
}

ℕ Leganto::trovuSekvanAŭSamanAperonDeIuAnoDe(const Listo<Texto>& wortoj)
{
    Listo<ℕ> lokoj;
    char karaktero;
    lokoj.regrandigu(wortoj.grandon(), 0);
    
    while (provuDoniKarakteron(&karaktero))
    {
        for (ℕ i = 0; i < wortoj.grandon(); i++)
        {
            if (karaktero != wortoj[i][lokoj[i]])
            {
                if (lokoj[i] != 0)
                {
                    ℕ Δs = lokoj[i] - 1;
                    provuPaŝiMalantaŭen(Δs);
                    for (ℕ j = 0; j < wortoj.grandon(); j++)
                        lokoj[j] = (Δs > lokoj[j]) ? 0 : lokoj[j] - Δs;
                    lokoj[i] = 0;
                }
            }
            else if (++lokoj[i] == wortoj[i].grandon())
            {
                provuPaŝiMalantaŭen(wortoj[i].grandon());
                eligu i;
            }
        }
    }
    
    eligu neniu_rezulto;
}

ℕ Leganto::rekonuĈiAperonDeIuAnoDe(const Listo<Texto>& wortoj)
{
    for (ℕ i = 0; i < wortoj.grandon(); i++)
        if (ĉuEstasDiĉeKomencoDe(wortoj[i]))
            eligu i;
    eligu neniu_rezulto;
}

ℕ Leganto::trovuFinonDeMalsekvaAperoDeIuAnoDe(const Listo<Texto>& wortoj)
{
    Listo<ℕ> lokoj;
    lokoj.regrandigu(wortoj.grandon(), 0);
    
    while (provuPaŝiMalantaŭen())
    {
        char karaktero = torento->peek();
        for (ℕ i = 0; i < wortoj.grandon(); i++)
        {
            if (karaktero != wortoj[i][wortoj[i].grandon() - 1 - lokoj[i]])
                lokoj[i] = 0;
            else if (++lokoj[i] == wortoj[i].grandon())
            {
                provuPaŝiAntaŭen(wortoj[i].grandon());
                eligu i;
            }
        }
    }
    
    eligu neniu_rezulto;
}

Buleo Leganto::provuIriAlUnuaAperoDiexterKrampoj(const Texto& worto)
{
    eligu provuIriAlUnuaAperoDiexterKrampojHede({worto});
}

Buleo Leganto::provuIriAlUnuaAperoDiexterKrampojHede(const Listo<Texto>& p_wortoj, ℕ* trovito)
{   //-«
    premisu (ne p_wortoj.ĉuEnhavas("")); //»-
    static constexpr ℕ unua_fermanta_krampo = 3;
    static constexpr ℕ nombro_da_krampoj = 6;
    Listo<Texto> wortoj = {"(", "[", "{", "}", "]", ")"};
    wortoj.almetu(p_wortoj);
    ℤ profundo = 0;
    
    for (ℕ rezulto = trovuSekvanAŭSamanAperonDeIuAnoDe(wortoj); rezulto != Leganto::neniu_rezulto;
         rezulto = trovuSekvanAperonDeIuAnoDe(wortoj))
    {
        if (rezulto < unua_fermanta_krampo)
            profundo++;
        else if (rezulto < nombro_da_krampoj kaj profundo == 0 kaj p_wortoj.ĉuEnhavas(wortoj[rezulto]))
        {
            if (trovito != nullptr)
                *trovito = p_wortoj.provuTrovi(wortoj[rezulto]).donuLokon();
            eligu veran;
        }
        else if (rezulto < nombro_da_krampoj kaj profundo == 0)
            eligu malveran;
        else if (rezulto < nombro_da_krampoj)
            profundo--;
        else if (profundo <= 0)
        {
            if (trovito != nullptr)
                *trovito = rezulto - nombro_da_krampoj;
            eligu veran;
        }
    }
    
    eligu malveran;
}

Buleo Leganto::provuPaŝiAntaŭen()
{
    char c;
    if (ne torento->get(c))
    {
        torento->clear();
        eligu malveran;
    }
    eligu veran;
}

Buleo Leganto::provuPaŝiAntaŭen(ℕ nombroDaPaŝoj)
{
    char c;
    while (nombroDaPaŝoj-- > 0)
    {
        if (ne torento->get(c))
        {
            torento->clear();
            eligu malveran;
        }
    }
    eligu veran;
}

Buleo Leganto::provuPaŝiMalantaŭen()
{
    if (ne torento->unget())
    {
        torento->clear();
        eligu malveran;
    }
    eligu veran;
}

Buleo Leganto::provuPaŝiMalantaŭen(unsigned int nombroDaPaŝoj)
{
    while (nombroDaPaŝoj-- > 0)
    {
        if (ne torento->unget())
        {
            torento->clear();
            eligu malveran;
        }
    }
    eligu veran;
}

Nenio Leganto::saltuPostBlankanSpacon()
{
    char karaktero;
    while (provuDoniKarakteron(&karaktero))
    {
        if (ne blankspacaj_karakteroj.ĉuEnhavas(Texto("") + karaktero))
        {
            provuPaŝiMalantaŭen();
            eligu;
        }
    }
}

Nenio Leganto::iruAl(ℤ8 loko)
{
    torento->seekg(loko);
}

Nenio Leganto::iruAlKomenco()
{
    torento->seekg(0, std::ios::beg);
}

Nenio Leganto::iruAlFino()
{
    torento->seekg(0, std::ios::end);
}

ℤ8 Leganto::donuLokon()
{
    eligu torento->tellg();
}

Texto Leganto::donuLinion()
{
    std::string texto;
    ℤ8 lokoUnue = donuLokon();
    std::getline(*torento, texto);
    iruAl(lokoUnue);
    eligu texto;
}

Texto Leganto::donuPartonInter(ℤ8 komenco, ℤ8 fino)
{
    premisu (fino >= komenco);
    ℤ8 lokoUnue = donuLokon();
    Texto texto;
    iruAl(komenco);
    for (char c; donuLokon() != fino kaj torento->get(c);)
        texto += c;
    iruAl(lokoUnue);
    torento->clear();
    eligu texto;
}

Buleo Leganto::provuDoniKarakteron(char* celkaraktero)
{
    eligu torento->get(*celkaraktero).good();
}

Buleo Leganto::_ĉuEstasĈeKomencoDe(const Texto& vorto)
{
    for (ℕ i = 0; i != vorto.grandon(); i++)
    {
        char c;
        
        if (ne torento->get(c) aŭ c != vorto[i])
        {
            torento->clear();
            eligu malveran;
        }
    }
    
    eligu veran;
}