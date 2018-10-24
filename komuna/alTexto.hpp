#ifndef KOMUNA_ALTEXTO_HPP
#define KOMUNA_ALTEXTO_HPP

#include "Texto.hpp"
#include "trajtoj/specoj.hpp"
#include "trajtoj/numero.hpp"
#include "torent/TorentoTexta.hpp"
#include "cet/Lokaĵaro.hpp"

template<class K>
Texto alTextoSesdeka(K k)
{
    tuj_premisu(ĉu_estas_ℕ<K>);
    static constexpr ℕ nombroDaSesdekajNumeroj = bitojDen<K> / 4;
    const static char karakteroj[] = "0123456789ABCDEF";
    Texto rezulto;
    rezulto.rezervu(nombroDaSesdekajNumeroj);
    for (ℕ i = nombroDaSesdekajNumeroj; i-- > 0;)
        rezulto.enmetu(karakteroj[(k >> (i * 4)) % 16]);
    eligu rezulto;
}

template<class K>
uzu_se_<ne ĉu_specoj_samas<K, ℕ8b> kaj ne ĉu_specoj_samas<K, ℤ8b> kaj ne ĉu_specoj_samas<K, Buleo>
        kaj ne std::is_pointer_v<K> kaj ne ĉu_estas_ℚ_krom_ℤ<K>, Texto> alTexto(K k)
{
    Texto texto;
    {
        TorentoTexta torento(&texto);
        torento << k;
    }
    eligu texto;
}

template<class K>
uzu_se_<ĉu_specoj_samas<K, ℕ8b>, Texto> alTexto(K k)
{
    eligu alTexto<ℕ>(k);
}

template<class K>
uzu_se_<ĉu_specoj_samas<K, ℤ8b>, Texto> alTexto(K k)
{
    eligu alTexto<ℤ>(k);
}

template<class K>
uzu_se_<ĉu_specoj_samas<K, Buleo>, Texto> alTexto(K k)
{
    eligu k ? "veran" : "malveran";
}

template<class K>
uzu_se_<std::is_pointer_v<K>, Texto> alTexto(K k)
{
    eligu "0x" + alTextoSesdeka(reinterpret_cast<std::uintptr_t>(k));
}

template<class K>
uzu_se_<ĉu_estas_ℚ_krom_ℤ<K>, Texto> alTexto(K k, const ℕ maximumaNombroDaDecimaloj = 3,
                                             Buleo ĉuVolasFinajnNulojn = malveran)
{
    Texto texto;
    TorentoTexta torento(&texto);
    torento.imbue(normaLokaĵaro);
    torento << std::fixed << std::setprecision(maximumaNombroDaDecimaloj) << k; // todo bonorigu
    torento.flush();
    
    if (ne ĉuVolasFinajnNulojn kaj texto.ĉuEnhavas(','))
    {
        while (*texto.lastan() == '0')
            texto.forprenuLastan();
        
        if (*texto.lastan() == ',')
            texto.forprenuLastan();
    }
    
    eligu texto;
}

#endif //KOMUNA_ALTEXTO_HPP
