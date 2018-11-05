#include <QtCore/QCoreApplication>
#include "PrenantoDeDifinoj.hpp"
#include "komuna/alTexto.hpp"

PrenantoDeDifinoj::PrenantoDeDifinoj(Texto worto, Wortarestro* wortarestro, std::mutex* mutex_wortarestro,
                                     Buleo ĉuWortoEstasExaktan, Linguo volataLinguo)
        : worto(worto), wortarestro(wortarestro), mutex_wortarestro(mutex_wortarestro),
          ĉuWortoEstasExaktan(ĉuWortoEstasExaktan), volataLinguo(volataLinguo),
          aktivaSugesto(0), ĉuNuligis(malveran), ĉuEstasEnLuso(malveran)
{
    moveToThread(&fadeno);
    fadeno.start();
}

PrenantoDeDifinoj::~PrenantoDeDifinoj()
{
    if (ne fadeno.isRunning())
        eligu;
    nuligu();
    fadeno.quit();
    fadeno.wait();
}

Nenio PrenantoDeDifinoj::_komencu()
{
    premisu (sugestoj.ĉuEstasMalplenan());
    kreuListonDeSugestoj();
    _rekomencu();
}

Nenio PrenantoDeDifinoj::_rekomencu()
{
    auto donuDifinonDe = [this](const Texto& worto, const Linguo& linguo) -> Difino
    {
        std::lock_guard<std::mutex> ŝloso(*mutex_wortarestro);
        eligu wortarestro->donuDifinonDe(worto, linguo);
    };
    
    ĉuVolasPliDifinojn = veran;
    ĉuEstasEnLuso = veran;
    
    while (ĉuVolasPliDifinojn kaj ne ĉuNuligis kaj aktivaSugesto < sugestoj.grandon())
    {
        Wortarestro::Sugesto sugesto = sugestoj[aktivaSugesto];
        Difino difino = donuDifinonDe(sugesto.worto, sugesto.linguo);
        difino.distanco = sugesto.distanco;
        aktivaSugesto++;
        traktuNovanDifinon(difino);
        QCoreApplication::processEvents();
    }
    
    if (ĉuNuligis aŭ aktivaSugesto >= sugestoj.grandon())
        kiamFinis();
    
    ĉuEstasEnLuso = malveran;
}

Nenio PrenantoDeDifinoj::_nuligu()
{
    if (ĉuNuligis)
        eligu;
    ĉuNuligis = veran;
    if (ne ĉuEstasEnLuso)
        kiamFinis();
}

Nenio PrenantoDeDifinoj::kreuListonDeSugestoj()
{
    std::lock_guard<std::mutex> ŝloso(*mutex_wortarestro);
    if (ĉuWortoEstasExaktan)
    {
        if (volataLinguo == neniu_linguo)
            for (Linguo linguo : wortarestro->donuŜarĝitajnLinguojn())
                sugestoj.enmetu({linguo, worto, 0});
        else sugestoj.enmetu({volataLinguo, worto, 0});
    }
    else if (volataLinguo == neniu_linguo)
        sugestoj = wortarestro->donuSugestojnPor(worto);
    else sugestoj = wortarestro->donuSugestojnPor(worto, volataLinguo);
    
    sugestoj.ordigu([](const Wortarestro::Sugesto& a, const Wortarestro::Sugesto& b) -> Buleo //-«
                    { eligu a.distanco < b.distanco; }); //»-
}