#include <thread>
#include <filesystem>
#include "Wortarestro.hpp"
#include "komuna/DividataAdres.hpp"
#include "komuna/alTexto.hpp"

Wortarestro::Wortarestro(Texto dosieroDeWortarujo)
{
    kreuProvizoranDosierujon();
    wortarujo = zipios::ZipFile(dosieroDeWortarujo.STL());
}

Wortarestro::~Wortarestro()
{
    forprenuProvizoranDosierujon();
}

Nenio Wortarestro::agorduRetejonDeParsoid(const Texto& p_retejoDeParsoid)
{
    retejoDeParsoid = p_retejoDeParsoid;
    for (_Wortaro& wortaro : wortaroj)
        if (wortaro.difinoj)
            wortaro.difinoj->agorduRetejonDeParsoid(retejoDeParsoid);
}

Nenio Wortarestro::agorduVolatajnLinguojn(Listo<Paro<Texto, Linguo>> novajLinguoj)
{
    auto ĉuEgalas = [](const Paro<Texto, Linguo>& a, const Linguo& linguo) -> Buleo { eligu a.second == linguo; };
    
    for (ℕ i = 0; i < wortaroj.grandon(); i++)
        if (novajLinguoj.ĉuEnhavas(wortaroj[i].linguo, ĉuEgalas))
            novajLinguoj.forprenuĈiun(wortaroj[i].linguo, ĉuEgalas);
        else wortaroj.forprenu(i);
    
    for (const Paro<Texto, Linguo>& paro : novajLinguoj)
        wortaroj.enmetu(_Wortaro(paro.second, &wortarujo, retejoDeParsoid));
}

Listo<Linguo> Wortarestro::donuŜarĝitajnLinguojn() const
{
    Listo<Linguo> linguoj;
    for (auto& wortaro : wortaroj)
        linguoj.enmetu(wortaro.linguo);
    eligu linguoj;
}

Listo<Wortarestro::Sugesto> Wortarestro::donuSugestojnPor(const Texto& ebleEraraWorto)
{
    std::string minuskligitaWorto = ebleEraraWorto.minuskligitan().STL();
    
    Listo<Sugesto> sugestoj;
    for (_Wortaro& wortaro : wortaroj)
        for (const suggestItem& sugesto : wortaro.sugestanto.Correct(minuskligitaWorto))
            sugestoj.enmetu({wortaro.linguo, sugesto.term, sugesto.distance});
    eligu sugestoj;
}

Listo<Wortarestro::Sugesto> Wortarestro::donuSugestojnPor(const Texto& ebleEraraWorto, const Linguo& linguo)
{
    std::string minuskligitaWorto = ebleEraraWorto.minuskligitan().STL();
    
    Listo<Sugesto> sugestoj;
    for (_Wortaro& wortaro : wortaroj)
        if (wortaro.linguo == linguo)
            for (const suggestItem& sugesto : wortaro.sugestanto.Correct(minuskligitaWorto))
                sugestoj.enmetu({wortaro.linguo, sugesto.term, sugesto.distance});
    eligu sugestoj;
}

Difino Wortarestro::donuDifinonDe(const Texto& worto, Linguo linguo)
{
    for (_Wortaro& wortaro : wortaroj)
        if (wortaro.linguo == linguo)
            eligu {worto, wortaro.linguo, wortaro.difinoj->donuHtmlDifinonDe(worto), 0};
    throw Eraro("Ne povas doni difinon de «" + worto + "» en «" + linguo.iso639_3 + "».",
                "Linguo «" + linguo.iso639_3 + "» ne estas ŝarĝitan.");
}

InformoDeWortaroj Wortarestro::donuInformonDeĈiujWortaroj()
{
    auto provuDoniNombronDaWortoj = [this](DividataAdres<zipios::FileEntry> dosiero)
    {
        // bedaŭrinde la torento de zipios ne donas dosierlokojn
        zipios::FileCollection::stream_pointer_t torento = wortarujo.getInputStream(dosiero->getName());
        char _linio[100];
        torento->getline(_linio, 100);
        Texto linio(_linio);
        
        Leganto leganto(kreu TorentoTexta(&linio), veran);
        premisu (leganto.ĉuEstasDiĉeKomencoDe("format=wikitext1"));
        
        leganto.provuIriAlFinoDeSekva("wortoj=");
        ℤ8 komencoDeNombro = leganto.donuLokon();
        leganto.trovuSekvanAperonDeIuAnoDe(blankspacaj_karakteroj);
        Texto nombroTexta = leganto.donuPartonInter(komencoDeNombro, leganto.donuLokon());
        eligu nombroTexta.alℕ();
    };
    
    auto provuKreiWortaron = [&provuDoniNombronDaWortoj](DividataAdres<zipios::FileEntry> dosiero)
    {
        InformoDeWortaroj::Wortaro wortaro;
        
        if (dosiero->isDirectory() aŭ ne Texto(dosiero->getName()).ĉuKomencasPer(dosierujo_de_difinoj))
            eligu InformoDeWortaroj::Wortaro();
        
        wortaro.nombroDaWortoj = provuDoniNombronDaWortoj(dosiero);
        wortaro.linguo.iso639_3 = dosiero->getFileName();
        
        if (wortaro.linguo.iso639_3.grandon() == 2)
            wortaro.linguo = Linguo::provuDoniLinguonDeIso639_2(wortaro.linguo.iso639_3);
        
        if (wortaro.linguo.ĉuNiKonasLinguon())
            eligu wortaro;
        
        std::cerr << "Forlasis linguon «" + wortaro.linguo.iso639_3.STL() + "» ("
                     + alTexto(wortaro.nombroDaWortoj).STL() + " wortoj) el listo de linguoj." << std::endl;//»-
        eligu InformoDeWortaroj::Wortaro();
    };
    
    
    InformoDeWortaroj informo;
    informo.grupoj.enmetuNovan();
    InformoDeWortaroj::Grupo& enwiktionary = *informo.grupoj.lastan();
    enwiktionary.fonto = "en.wiktionary.org";
    enwiktionary.mallongaNomo = "en.w";
    enwiktionary.linguoDeDifinoj = angla_linguo;
    
    for (auto dosiero : wortarujo.entries())
    {
        InformoDeWortaroj::Wortaro wortaro = provuKreiWortaron(dosiero);
        if (wortaro.linguo != Linguo())
            enwiktionary.wortaroj.enmetu(formovu(wortaro));
    }
    
    eligu informo;
}

Nenio Wortarestro::kreuProvizoranDosierujon()
{
    std::filesystem::create_directory(provizora_dosierujo.STL());
    std::filesystem::create_directory((provizora_dosierujo + dosierujo_de_difinoj).STL());
    //std::filesystem::create_directory((provizora_dosierujo + dosierujo_de_sugestantoj).STL());
    premisu (std::filesystem::exists((provizora_dosierujo + dosierujo_de_difinoj).STL()));
}

Nenio Wortarestro::forprenuProvizoranDosierujon()
{
    try
    {
        std::filesystem::remove((provizora_dosierujo + dosierujo_de_difinoj).STL());
        std::filesystem::remove(provizora_dosierujo.STL());
    }
    catch (std::filesystem::filesystem_error& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

Wortarestro::_Wortaro::_Wortaro(const Linguo& p_linguo, zipios::ZipFile* wortarujo, const Texto& retejoDeParsoid)
        : linguo(p_linguo)
{
    Texto dosiero = donuDosieronDe(linguo);
    Texto provizoraDosiero = provizora_dosierujo + dosiero;
    zipios::FileCollection::stream_pointer_t torento = wortarujo->getInputStream(dosiero.STL());
    
    if (torento == nullptr)
        throw Eraro("Difinoj de " + p_linguo.iso639_3 + " mankas.");
    
    std::ofstream skribanto(provizoraDosiero.STL(), std::ios::binary | std::ios::out | std::ios::trunc);
    
    if (ne skribanto.good())
        throw Eraro("Ne povis krei provizoran wortaron");
    
    for (char karaktero; torento->get(karaktero).good();)
        skribanto << karaktero;
    skribanto.flush();
    
    auto kreuLeganton = [provizoraDosiero]() -> Leganto
    {
        eligu Leganto(new std::ifstream(provizoraDosiero.STL(), std::ios::binary | std::ios::in));
    };
    
    Leganto leganto = formovu(kreuLeganton());
    
    if (leganto.ĉuEstasDiĉeKomencoDe("format=wikitext1"))
        difinoj.reset(new Wortaro_wikitext1(kreuLeganton, retejoDeParsoid));
    else
        throw Eraro_NeRekonitanSpeconDeWortaro(provizoraDosiero);
    
    // bedaŭrinde ŝarĝi sugestanton neniam sukcesas
    /*Texto dosiero_de_sugestanto = provizora_dosierujo + dosierujo_de_sugestantoj + linguo.iso639_3;
    Buleo ĉuŜarĝiSukcesis = malveran;
    
    try
    {
        if (std::filesystem::exists(dosiero_de_sugestanto.STL()))
        {
            sugestanto.Load(dosiero_de_sugestanto.STL());
            ĉuŜarĝiSukcesis = veran;
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "Ŝarĝi " << dosiero_de_sugestanto.STL() << " malsukcesis: " << e.what() << std::endl;
    }
    
    if (ne ĉuŜarĝiSukcesis)
    {*/
    sugestanto = formovu(difinoj->kreuSugestanton());
    /*    sugestanto.Save(dosiero_de_sugestanto.STL());
    }*/
}

Wortarestro::_Wortaro::~_Wortaro()
{
    if (difinoj)
        std::filesystem::remove((provizora_dosierujo + donuDosieronDe(linguo)).STL());
}

Texto Wortarestro::_Wortaro::donuDosieronDe(const Linguo& linguo)
{
    Texto iso639_2 = linguo.provuDoniIso639_2();
    if (ne iso639_2.ĉuEstasMalplenan())
        eligu dosierujo_de_difinoj + iso639_2;
    eligu dosierujo_de_difinoj + linguo.iso639_3;
}