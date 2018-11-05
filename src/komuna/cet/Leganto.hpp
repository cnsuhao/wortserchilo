#ifndef VIKIVORTARO_KONVERTANTO_XMLLEGANTO_HPP
#define VIKIVORTARO_KONVERTANTO_XMLLEGANTO_HPP

#include <fstream>
#include "../esperanta_traduko.hpp"
#include "../Texto.hpp"
#include "../trajtoj/numero.hpp"
#include "../Listo.hpp"
#include "../Eraro.hpp"

// todo ĝustigu trovu-funkciojn

class Leganto
{
public:
    Leganto();
    Leganto(const Texto& p_dosiero);
    Leganto(std::istream* p_torento, Buleo p_ĉuDevasForpreniTorenton = malveran);
    Leganto(const Leganto&) = delete;
    Leganto(Leganto&& alia) noexcept;
    ~Leganto();
    Leganto& operator=(const Leganto&) = delete;
    Leganto& operator=(Leganto&& alia) noexcept;
    
    Buleo ĉuEstasDiĉeKomencoDe(const Texto& vorto);
    Buleo ĉuEstasDiĉeFinoDe(const Texto& vorto);
    Buleo ĉuEstasInter(const Texto& komencaVorto, const Texto& finaVorto, ℕ maximumaNombroDaRegeloj = 10);
    Buleo provuIriAlSekva(const Texto& worto);
    Buleo provuIriAlFinoDeSekva(const Texto& worto);
    Buleo provuIriAlMalsekva(const Texto& worto);
    Buleo provuIriAlFinoDeMalsekva(const Texto& worto);
    ℕ trovuSekvanAperonDeIuAnoDe(const Listo<Texto>& wortoj);
    ℕ trovuSekvanAŭSamanAperonDeIuAnoDe(const Listo<Texto>& wortoj);
    ℕ rekonuĈiAperonDeIuAnoDe(const Listo<Texto>& wortoj);
    ℕ trovuFinonDeMalsekvaAperoDeIuAnoDe(const Listo<Texto>& wortoj);
    Buleo provuIriAlUnuaAperoDiexterKrampoj(const Texto& worto);
    Buleo provuIriAlUnuaAperoDiexterKrampojHede(const Listo<Texto>& p_wortoj, ℕ* trovito = nullptr);
    Buleo provuPaŝiAntaŭen();
    Buleo provuPaŝiAntaŭen(ℕ nombroDaPaŝoj);
    Buleo provuPaŝiMalantaŭen();
    Buleo provuPaŝiMalantaŭen(ℕ nombroDaPaŝoj);
    Nenio saltuPostBlankanSpacon();
    Nenio iruAl(ℤ8 loko);
    Nenio iruAlKomenco();
    Nenio iruAlFino();
    
    template<class K>
    K leguBinaran(); // ankaŭ paŝas antaŭen
    template<class K>
    Buleo provuLegiBinaran(K* celo); // Ankaŭ paŝas antaŭen. Lasas celon en hazarda stato se ĝi malsukcesas.
    
    ℤ8 donuLokon();
    Texto donuLinion();
    Texto donuPartonInter(ℤ8 komenco, ℤ8 fino);
    Buleo provuDoniKarakteron(char* celkaraktero);
    
    static constexpr ℕ neniu_rezulto = maximumDe<ℕ>;
private:
    Buleo _ĉuEstasĈeKomencoDe(const Texto& vorto);
    Buleo ĉuDevasForpreniTorenton;
    std::istream* torento;
};


template<class K>
K Leganto::leguBinaran()
{
    tuj_premisu (ĉu_estas_ℕ<K>);
    K rezulto;
    if (ne provuLegiBinaran(&rezulto))
        throw Eraro("Dosiero finis tro frue.");
    eligu rezulto;
}

template<class K>
Buleo Leganto::provuLegiBinaran(K* celo)
{
    tuj_premisu (ĉu_estas_ℕ<K>);
    for (ℕ i = 0; i < bajtojDen<K>; i++)
        if (ne torento->get(reinterpret_cast<char*>(celo)[i]))
            eligu malveran;
    eligu veran;
}

#endif //VIKIVORTARO_KONVERTANTO_XMLLEGANTO_HPP
