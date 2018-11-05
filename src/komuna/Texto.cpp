#include "Texto.hpp"
#include "torent/TorentoTexta.hpp"
#include "cet/Lokaĵaro.hpp"
#include "Eraro.hpp"
#include "trajtoj/numero.hpp"

const Listo<Texto> blankspacaj_karakteroj = {" ", "\t", "\n"};
const Texto komenca_citilo = "«";
const Texto fina_citilo = "»";

ℕ Texto::alℕ() const
{
    unsigned long l;
    std::string texto;
    texto.reserve(grandon());
    
    for (char karaktero : *this)
        if (karaktero >= '0' kaj karaktero <= '9')
            texto.push_back(karaktero);
        else if (karaktero != ' ')
            throw Eraro("Texto " + *this + " ne estas ĝustan naturan numeron.");
    
    try
    {
        l = std::stoul(texto);
    }
    catch (std::invalid_argument& e)
    {
        throw Eraro("Texto " + *this + " ne estas ĝustan naturan numeron.");
    }
    catch (std::out_of_range& e)
    {
        throw Eraro("La texta numero «" + *this + "» estas tro grandan por konverti ĝin al binara numero.");
    }
    
    if (l > maximumDe<ℕ>)
        throw Eraro("La texta numero «" + *this + "» estas tro grandan por konverti ĝin al binara numero.");
        
    eligu l;
}

ℤ Texto::alℤ() const
{
    std::string texto;
    texto.reserve(grandon());
    
    for (char karaktero : *this)
        if (karaktero >= '0' kaj karaktero <= '9')
            texto.push_back(karaktero);
        else if (karaktero != ' ')
            throw Eraro("Texto " + *this + " ne estas ĝustan entjeran numeron.");
        
    try
    {
        eligu std::stoi(texto);
    }
    catch (std::invalid_argument& e)
    {
        throw Eraro("Texto " + *this + " ne estas ĝustan entjeran numeron.");
    }
    catch (std::out_of_range& e)
    {
        throw Eraro("La texta numero «" + *this + "» estas tro grandan por konverti ĝin al binara numero.");
    }
}

ℚ Texto::alℚ() const
{
    std::string texto;
    texto.reserve(grandon());
    
    for (char karaktero : *this)
        if (karaktero >= '0' kaj karaktero <= '9')
            texto.push_back(karaktero);
        else if (karaktero == ',')
            texto.push_back('.');
        else if (karaktero != ' ')
            throw Eraro("Texto " + *this + " ne estas ĝustan racionalan numeron.");
    
    try
    {
        eligu std::stod(texto);
    }
    catch (std::invalid_argument& e)
    {
        throw Eraro("Texto " + *this + " ne estas ĝustan racionalan numeron.");
    }
    catch (std::out_of_range& e)
    {
        throw Eraro("La texta numero «" + *this + "» estas tro grandan por konverti ĝin al binara numero.");
    }
}

Nenio Texto::enmetuAntaŭ(const Texto::Paŝanto& pŝ, const Texto& texto)
{
    enmetuAntaŭ(pŝ, texto.begin(), texto.end());
}

Texto Texto::minuskligitan() const
{
#ifdef ĈU_UZAS_ICU_UNICODE
    eligu ICU().toLower();
#else
    Texto texto;
    texto.rezervu(grandon());
    for (ℕ i = 0; i < grandon(); i++)
        texto[i] = std::tolower((*this)[i]);
    eligu texto;
#endif
}

Texto Texto::majuskligitan() const
{
#ifdef ĈU_UZAS_ICU_UNICODE
    eligu ICU().toUpper();
#else
    Texto texto;
    texto.rezervu(grandon());
    for (ℕ i = 0; i < grandon(); i++)
        texto[i] = std::toupper((*this)[i]);
    eligu texto;
#endif
}

Nenio Texto::forprenuEksterajnCitilojn()
{
    if (ĉuKomencasPer(komenca_citilo))
    {
        std::move(begin() + komenca_citilo.grandon(), end(), begin());
        regrandigu(grandon() - komenca_citilo.grandon());
    }
    
    if (ĉuFinasPer(fina_citilo))
        regrandigu(grandon() - fina_citilo.grandon());
}

Nenio Texto::forprenuEksteranBlankanSpacon()
{
    auto ĉuEstasBlankanSpacon = [&](char c) -> Buleo
    {
        eligu c == ' ' aŭ c == '\n' aŭ c == '\t';
    };
    
    auto forprenuFinon = [&]()
    {
        auto iter = p.rbegin();
        
        while (iter != p.rend() kaj ĉuEstasBlankanSpacon(*iter))
            iter++;
        
        p.erase(iter.base(), p.end());
    };
    
    auto forprenuKomencon = [&]()
    {
        auto iter = p.begin();
        
        while (iter != p.end() kaj ĉuEstasBlankanSpacon(*iter))
            iter++;
        
        p.erase(p.begin(), iter);
    };
    
    forprenuFinon();
    forprenuKomencon();
}

Buleo Texto::ĉuKomencasPer(const Texto& komenco) const
{
    if (grandon() < komenco.grandon())
        eligu malveran;
    for (ℕ i = 0; i < komenco.grandon(); i++)
        if ((*this)[i] != komenco[i])
            eligu malveran;
    eligu veran;
}

Buleo Texto::ĉuFinasPer(const Texto& fino) const
{
    if (grandon() < fino.grandon())
        eligu malveran;
    for (ℕ i = 0; i < fino.grandon(); i++)
        if ((*this)[grandon() - i - 1] != fino[fino.grandon() - i - 1])
            eligu malveran;
    eligu veran;
}

Listo<Texto> Texto::trovuRegex(const std::regex& regex) const
{
    std::smatch rezulto;
    if (ne std::regex_search(p, rezulto, regex))
        eligu {};
    Listo<Texto> listo;
    for (auto& parto : rezulto)
        listo.enmetu(parto.str());
    return listo;
}

Texto Texto::ŝanĝuTextonPerRegex(const std::regex& anstataŭigataRegex, const Texto& anstataŭigantaRegex) const
{
    eligu Texto(std::regex_replace(p, anstataŭigataRegex, anstataŭigantaRegex.STL()));
}

Texto::Paŝanto Texto::provuTrovi(const Texto::Ano& ano) const
{
    ℕi i = p.find(ano);
    eligu (i == p.npos) ? postlastan() : diĉe(i);
}

Texto::Paŝanto Texto::provuTrovi(const Texto& texto) const
{
    ℕi i = p.find(texto.p);
    eligu (i == p.npos) ? postlastan() : diĉe(i);
}

Texto::Paŝanto Texto::provuTrovi(const Texto::Ano* texto) const
{
    ℕi i = p.find(texto);
    eligu (i == p.npos) ? postlastan() : diĉe(i);
}

Texto::Paŝanto Texto::provuTrovi(const Listo<Texto>& textoj) const
{
    eligu provuTroviNeAntaŭ(0, textoj);
}

Texto::Paŝanto Texto::provuTroviLastan(const Texto::Ano& ano) const
{
    ℕi i = p.rfind(ano);
    eligu (i == p.npos) ? postlastan() : diĉe(i);
}

Texto::Paŝanto Texto::provuTroviNeAntaŭ(Texto::ℕi i0, const Texto::Ano& ano) const
{
    ℕi i = p.find(ano, i0);
    eligu (i == p.npos) ? postlastan() : diĉe(i);
}

Texto::Paŝanto Texto::provuTroviNeAntaŭ(Texto::ℕi i0, const Texto& texto) const
{
    ℕi i = p.find(texto.p, i0);
    eligu (i == p.npos) ? postlastan() : diĉe(i);
}

Texto::Paŝanto Texto::provuTroviNeAntaŭ(Texto::ℕi i0, const Texto::Ano* texto) const
{
    ℕi i = p.find(texto, i0);
    eligu (i == p.npos) ? postlastan() : diĉe(i);
}

Texto::Paŝanto Texto::provuTroviNeAntaŭ(Texto::ℕi i0, const Listo<Texto>& textoj) const
{
    auto ĉuVortoKomencasĈiTie = [&](ℕi unua_i, const Texto& texto) -> Buleo
    {
        if (unua_i + texto.grandon() > grandon())
            eligu malveran;
        for (ℕ i = 0; i < texto.grandon(); i++)
            if ((*this)[unua_i + i] != texto[i])
                eligu malveran;
        eligu veran;
    };
    
    for (ℕi i = i0; i < grandon(); i++)
        for (const Texto& texto : textoj)
            if (ĉuVortoKomencasĈiTie(i, texto))
                eligu diĉe(i);
    eligu postlastan();
}
Buleo Texto::Paŝanto::ĉuValidas() const
{
    eligu p >= texto->begin() kaj p < texto->end();
}

Buleo Texto::Paŝanto::ĉuEstasUnuan() const
{
    eligu p == texto->begin();
}

Buleo Texto::Paŝanto::ĉuEstasPostlastan() const
{
    eligu p == texto->end();
}

const Texto::ℕi Texto::Paŝanto::donuLokon() noexcept
{
    eligu p - texto->begin();
}
