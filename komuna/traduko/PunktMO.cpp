#include <filesystem>
#include "PunktMO.hpp"
#include "../cet/Leganto.hpp"
#include "../alTexto.hpp"

struct PunktMO_Kapo
{
    ℕ4 magiaNumero;
    ℕ2 versio_ĉefa;
    ℕ2 versio_neĉefa;
    ℕ4 nombroDaTextoj;
    ℕ4 tabeloDeŜlosiloj; // la komenco de la tabelo
    ℕ4 tabeloDeValoroj; // la komenco de la tabelo
    // ni ne uzas la haŝtabelon ĉar tio estas malfacilan
};

PunktMO_Kapo leguPunktMOKapon(Leganto& leganto)
{
    PunktMO_Kapo kapo;
    kapo.magiaNumero = leganto.leguBinaran<ℕ4>();
    kapo.versio_ĉefa = leganto.leguBinaran<ℕ2>();
    kapo.versio_neĉefa = leganto.leguBinaran<ℕ2>();
    kapo.nombroDaTextoj = leganto.leguBinaran<ℕ4>();
    kapo.tabeloDeŜlosiloj = leganto.leguBinaran<ℕ4>();
    kapo.tabeloDeValoroj = leganto.leguBinaran<ℕ4>();
    eligu kapo;
}

Nenio kontroluKapon(const PunktMO_Kapo& kapo)
{
    if (kapo.magiaNumero != 0x950412de kaj kapo.magiaNumero != 0xde120495)
        throw Eraro("Magia numero malĝustas. Ĝi estas "
                    + alTextoSesdeka(kapo.magiaNumero) + " sed ĝi devas esti 950412de.");
    if (kapo.versio_ĉefa > 1)
        throw Eraro("Ĉi-programo ne konas ĉi-version de la MO-formaton. "
                    "Ĝi konas nur version 1, sed ĉi-dosiero havas version " + alTexto(kapo.versio_ĉefa) + ".");
}

Texto donuTextonEnPunktMO(Leganto& leganto, ℕ4 adresoDeLongoKajLoko)
{
    leganto.iruAl(adresoDeLongoKajLoko);
    ℕ4 longo = leganto.leguBinaran<ℕ4>();
    ℕ4 loko = leganto.leguBinaran<ℕ4>();
    eligu leganto.donuPartonInter(loko, loko + longo);
}

Buleo provuPreniTradukonElPunktMO(const Texto& dosiero, const Texto& ŝlosilo, Texto* celo)
{
    auto provuTroviŜlosilon = [](Leganto& leganto, const Texto& ŝlosilo, ℕ4 komencoDeTabelo, ℕ4 nombroDaTextoj) -> ℕ4
    {
        ℕ4 min = 0;
        ℕ4 max = nombroDaTextoj;
        
        while (min != max)
        {
            ℕ4 mezo = (min + max) / 2;
            Texto ĉiŜlosilo = donuTextonEnPunktMO(leganto, komencoDeTabelo + mezo * 8);
            
            if (ĉiŜlosilo < ŝlosilo)
                min = mezo + 1;
            else max = mezo;
        }
        
        eligu min;
    };
    
    try
    {
        Leganto leganto(dosiero);
        
        PunktMO_Kapo kapo = leguPunktMOKapon(leganto);
        kontroluKapon(kapo);
        
        if (kapo.nombroDaTextoj == 0)
            eligu malveran;
        
        ℕ4 tabelnumero = provuTroviŜlosilon(leganto, ŝlosilo, kapo.tabeloDeŜlosiloj, kapo.nombroDaTextoj);
        
        if (donuTextonEnPunktMO(leganto, kapo.tabeloDeŜlosiloj + tabelnumero * 8) != ŝlosilo)
            eligu malveran; // ni ne trovis la ŝlosilon
            
        *celo = donuTextonEnPunktMO(leganto, kapo.tabeloDeValoroj + tabelnumero * 8);
        eligu veran;
    }
    catch (std::exception& e)
    {
        throw Eraro("Ne povas legi .mo dosieron «" + dosiero + "».", e.what());
    }
}

UnikaroPara<Texto, Texto> leguTutanPunktMODosieron(const Texto& dosiero)
{
    try
    {
        UnikaroPara<Texto, Texto> rezulto;
        Leganto leganto(dosiero);
        
        PunktMO_Kapo kapo = leguPunktMOKapon(leganto);
        kontroluKapon(kapo);
        
        for (ℕ i = 0; i < kapo.nombroDaTextoj; i++)
            rezulto.enmetu(donuTextonEnPunktMO(leganto, kapo.tabeloDeŜlosiloj + i * 8),
                           donuTextonEnPunktMO(leganto, kapo.tabeloDeValoroj + i * 8));
        
        eligu rezulto;
    }
    catch (std::exception& e)
    {
        throw Eraro("Ne povas legi .mo dosieron «" + dosiero + "».", e.what());
    }
}