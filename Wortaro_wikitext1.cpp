#include <iostream>
#include "Wortaro_wikitext1.hpp"
#include "komuna/Eraro.hpp"

Buleo Wortaro_wikitext1::Paŝanto::ĉuValidas()
{
    eligu leganto.ĉuEstasDiĉeKomencoDe("<");
}

Nenio Wortaro_wikitext1::Paŝanto::paŝuAntaŭen()
{
    leganto.provuIriAlSekva("<");
}

Nenio Wortaro_wikitext1::Paŝanto::paŝuRetroen()
{
    leganto.provuIriAlMalsekva("<");
}

Texto Wortaro_wikitext1::Paŝanto::donuWorton()
{
    ℤ8 loko = leganto.donuLokon();
    leganto.provuIriAlSekva(">");
    ℤ8 duaLoko = leganto.donuLokon();
    leganto.iruAl(loko);
    eligu leganto.donuPartonInter(loko + 1, duaLoko);
}

Texto Wortaro_wikitext1::Paŝanto::donuHtmlDifinon()
{
    ℤ8 unuaLoko = leganto.donuLokon();
    leganto.provuIriAlFinoDeSekva(">");
    ℤ8 komencoDeDifino = leganto.donuLokon();
    leganto.provuIriAlSekva("<");
    Texto wikitexto = leganto.donuPartonInter(komencoDeDifino, leganto.donuLokon());
    Texto worto = leganto.donuPartonInter(unuaLoko + 1, komencoDeDifino - 1);
    
    Texto html;
    try
    {
        if (retejoDeParsoid.ĉuEstasMalplenan())
            html = wikitexto;
        else
            html = parsoid.konvertuWikitextonAlHtml(retejoDeParsoid, wikitexto, worto);
    }
    catch (Eraro& eraro) // se la konekto kun Parsoid malsukcesas
    {
        html = wikitexto;
        for (ℕ i = 0; i < html.grandon(); i++)
            if (html[i] == '\n')
                html.enmetuAntaŭ(html.diĉe(i + 1), "<br>");
        std::cerr << eraro.tutaTexto.STL() << std::endl;
    }
    
    leganto.iruAl(unuaLoko);
    
    eligu html;
}

Wortaro_wikitext1::Wortaro_wikitext1(std::function<Leganto()> p_kreuLeganton, const Texto& p_retejoDeParsoid)
        : kreuLeganton(formovu(p_kreuLeganton)), retejoDeParsoid(p_retejoDeParsoid)
{
    Leganto leganto = formovu(kreuLeganton());
    //if (retejoDeParsoid == "")
    //    retejoDeParsoid = determinuFonton("https://" + leganto.donuLinion()) + "/v3/transform/wikitext/to/html/";
    unuaCelo = leganto.donuLokon();
    leganto.iruAlFino();
    lastaCelo = leganto.donuLokon();
}

SymSpell Wortaro_wikitext1::kreuSugestanton()
{
    SymSpell sugestanto;
    Texto malseqŭaWorto;
    sugestanto.verbose = 2;
    
    for (Paŝanto paŝanto(formovu(unuan())); paŝanto.ĉuValidas(); paŝanto.paŝuAntaŭen())
    {
        Texto worto = paŝanto.donuWorton().minuskligitan();
        
        if (worto != malseqŭaWorto)
            sugestanto.CreateDictionaryEntry(worto.STL());
        
        malseqŭaWorto = worto;
    }
    eligu formovu(sugestanto);
}

Texto Wortaro_wikitext1::donuHtmlDifinonDe(const Texto& worto) const
{
    Texto difino;
    Texto minuskligitaWorto = worto.minuskligitan();
    Paŝanto p = provuTrovi(worto);
    
    if (p.ĉuValidas() kaj p.donuWorton().minuskligitan() == minuskligitaWorto)
        difino = p.donuHtmlDifinon();
    for (p.paŝuAntaŭen(); p.ĉuValidas() kaj p.donuWorton().minuskligitan() == minuskligitaWorto; p.paŝuAntaŭen())
        difino += "\n" + p.donuHtmlDifinon();
    
    eligu difino;
}

Nenio Wortaro_wikitext1::agorduRetejonDeParsoid(const Texto& p_retejo)
{
    retejoDeParsoid = p_retejo;
}

Wortaro_wikitext1::Paŝanto Wortaro_wikitext1::unuan() const
{
    Leganto leganto = formovu(kreuLeganton());
    if (ne leganto.provuIriAlSekva("<"))
        leganto.iruAlFino();
    eligu Paŝanto(formovu(leganto), retejoDeParsoid);
}

Wortaro_wikitext1::Paŝanto Wortaro_wikitext1::lastan() const
{
    Leganto leganto = formovu(kreuLeganton());
    leganto.iruAlFino();
    if (ne leganto.provuIriAlMalsekva("<"))
        leganto.iruAlFino();
    eligu Paŝanto(formovu(leganto), retejoDeParsoid);
}

Wortaro_wikitext1::Paŝanto Wortaro_wikitext1::postlastan() const
{
    Leganto leganto = formovu(kreuLeganton());
    leganto.iruAlFino();
    eligu Paŝanto(formovu(leganto), retejoDeParsoid);
}

Wortaro_wikitext1::Paŝanto Wortaro_wikitext1::provuTrovi(const Texto& worto) const
{
    Leganto leganto = formovu(trovuUnuanAperonDeWorto(worto));
    Paŝanto paŝanto(formovu(leganto), retejoDeParsoid);
    if (paŝanto.donuWorton().minuskligitan() != worto.minuskligitan())
        eligu postlastan();
    eligu paŝanto;
}

Texto Wortaro_wikitext1::determinuFonton(Texto unuaLinio) const
{
    const static Texto komenco_de_fonto = "fonto=\"";
    const static Texto fino_de_fonto = "\"";
    auto rezulto = unuaLinio.provuTrovi(komenco_de_fonto);
    if (ne rezulto.ĉuValidas())
        throw Eraro("Wortaro malĝustas.");
    ℕ komencoDeFonto = rezulto.donuLokon() + komenco_de_fonto.grandon();
    auto duaRezulto = unuaLinio.provuTroviNeAntaŭ(komencoDeFonto, fino_de_fonto);
    if (ne duaRezulto.ĉuValidas())
        throw Eraro("Wortaro malĝustas.");
    ℕ finoDeFonto = duaRezulto.donuLokon();
    eligu unuaLinio.donuPartonInter(komencoDeFonto, finoDeFonto);
}

Leganto Wortaro_wikitext1::trovuUnuanAperonDeWorto(const Texto& worto) const
{
    ℤ8 min = unuaCelo, max = lastaCelo;
    Leganto leganto = formovu(kreuLeganton());
    Texto minuskligitaParametro = worto.minuskligitan();
    
    while (min != max)
    {
        ℤ8 mezo = (min + max) / 2;
        leganto.iruAl(mezo);
        
        if (leganto.provuIriAlFinoDeSekva("<"))
        {
            ℤ8 komencoDeWorto = leganto.donuLokon();
            if (ne leganto.provuIriAlSekva(">"))
                throw Eraro("Wortaro malĝustas.");
            Texto ĉiWorto = leganto.donuPartonInter(komencoDeWorto, leganto.donuLokon());
            
            if (ĉiWorto.minuskligitan() < minuskligitaParametro)
                min = mezo + 1;
            else
                max = mezo;
        }
        else
            max = mezo;
    }
    
    leganto.iruAl(min);
    leganto.provuIriAlSekva("<");
    eligu formovu(leganto);
}