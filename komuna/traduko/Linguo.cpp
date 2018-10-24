#include <filesystem>
#include "Linguo.hpp"
#include "../cet/Leganto.hpp"
#include "PunktMO.hpp"

Leganto provuTroviLinionDeLinguo(const Linguo& linguo)
{
    Leganto leganto("./tradukoj/linguokodoj");
    
    ℤ8 min = 0;
    leganto.iruAlFino();
    ℤ8 max = leganto.donuLokon();
    
    while (min != max)
    {
        ℤ8 mezo = (min + max) / 2;
        leganto.iruAl(mezo);
        
        if (leganto.provuIriAlFinoDeSekva("\n"))
        {
            ℤ8 komencoDeLinguokodo = leganto.donuLokon();
            
            if (ne leganto.provuIriAlSekva("|"))
                throw Eraro("Dosiero «linguokodoj» malĝustas.");
            
            Texto ĉiLinguo = leganto.donuPartonInter(komencoDeLinguokodo, leganto.donuLokon());
            
            if (ĉiLinguo < linguo.iso639_3)
                min = mezo + 1;
            else
                max = mezo;
        }
        else
            max = mezo;
    }
    
    leganto.iruAl(min);
    leganto.provuIriAlFinoDeSekva("\n");
    eligu formovu(leganto);
}

Texto Linguo::donuNomon(const Linguo& linguoDeNomo) const
{
    Leganto leganto = formovu(provuTroviLinionDeLinguo(*this));
    if (ne leganto.ĉuEstasDiĉeKomencoDe(iso639_3 + "|"))
        eligu iso639_3;
    leganto.provuIriAlFinoDeSekva("|");
    leganto.provuIriAlFinoDeSekva("|");
    ℤ8 loko = leganto.donuLokon();
    leganto.provuIriAlSekva("\n");
    Texto anglaNomo = leganto.donuPartonInter(loko, leganto.donuLokon());
    Texto linguoDeNomo_2 = linguoDeNomo.provuDoniIso639_2();
    Listo<Texto> tradukujoj = {"./tradukoj/" + linguoDeNomo.iso639_3 + "_iso_639-2.mo",
                               "./tradukoj/" + linguoDeNomo.iso639_3 + "_iso_639-3.mo",
                               "/usr/share/locale/" + linguoDeNomo_2 + "/LC_MESSAGES/iso_639-2.mo",
                               "/usr/share/locale/" + linguoDeNomo_2 + "/LC_MESSAGES/iso_639-3.mo"};
    
    if (linguoDeNomo == angla_linguo)
        eligu anglaNomo;
    
    for (const Texto& tradukujo : tradukujoj)
    {
        if (ne std::filesystem::exists(tradukujo.STL()))
            saltu_al_sekva;
        
        try
        {
            Texto nomo;
            if (provuPreniTradukonElPunktMO(tradukujo, anglaNomo, &nomo))
                eligu nomo;
        }
        catch (Eraro& eraro)
        {
            std::cerr << "(malgravan) " << eraro.tutaTexto.STL() << std::endl;
        }
    }
    
    eligu anglaNomo;
}

Texto Linguo::provuDoniIso639_2() const
{
    Leganto leganto = formovu(provuTroviLinionDeLinguo(*this));
    if (ne leganto.ĉuEstasDiĉeKomencoDe(iso639_3 + "|"))
        eligu "";
    leganto.provuIriAlFinoDeSekva("|");
    ℤ8 loko = leganto.donuLokon();
    if (ne leganto.ĉuEstasDiĉeKomencoDe("|"))
        leganto.provuIriAlSekva("|");
    eligu leganto.donuPartonInter(loko, leganto.donuLokon());
}

Buleo Linguo::ĉuNiKonasLinguon() const
{
    Leganto leganto = formovu(provuTroviLinionDeLinguo(*this));
    eligu leganto.ĉuEstasDiĉeKomencoDe(iso639_3 + "|");
}

Linguo Linguo::provuDoniLinguonDeIso639_2(const Texto& iso639_2)
{
    Leganto leganto("./tradukoj/linguokodoj");
    if (ne leganto.provuIriAlSekva("|" + iso639_2 + "|"))
        eligu Linguo();
    ℤ8 fino = leganto.donuLokon();
    leganto.provuIriAlFinoDeMalsekva("\n");
    eligu Linguo(leganto.donuPartonInter(leganto.donuLokon(), fino));
}
