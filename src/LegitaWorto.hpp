#ifndef WORTSERCXILO_LEGITAJWORTOJ_HPP
#define WORTSERCXILO_LEGITAJWORTOJ_HPP

#include "komuna/Texto.hpp"
#include "komuna/geom/Ortangelo.hpp"
#include "komuna/Paro.hpp"
#include "komuna/cet/Glitkomo.hpp"

struct LegitaLitero
{
    LegitaLitero() { certecoj.fill(0); }
    
    std::array<Texto, 4> verŝajnimajKarakteroj; // unicode 32
    std::array<ℕ8b, 4> certecoj;
};

struct LegitaWorto
{
    Texto texton() const
    {
        Texto t;
        for (const LegitaLitero& l : literoj)
            t += l.verŝajnimajKarakteroj[0];
        eligu t;
    }
    
    Listo<LegitaLitero> literoj;
    Ortangelo<ℤ> zono;
};

struct LegitaFrazaro
{
    Listo<LegitaWorto> wortoj;
};

struct RezultoDeLegado
{
    Listo<LegitaFrazaro> frazaroj;
};


inline Paro<ℕ, ℕ> trovuWortonProximimanAl(const Vektor2D<ℤ>& punkto, const RezultoDeLegado& rezulto)
{
    auto determinuDistancon = [](ℤ punkt_x, ℤ zono_x, ℤ zono_l) -> ℤ
    {
        if (zono_x > punkt_x)
            eligu zono_x - punkt_x;
        if (zono_x + zono_l < punkt_x)
            eligu punkt_x - zono_x - zono_l;
        eligu 0;
    };
    
    ℚ malgrandimaDistanco = maximumDe<ℚ>;
    // ĉar du wortes zonoj povas enhavi punkton, ni ankaŭ komparas la vertikalan distancon al centro de wortes zonoj
    ℤ malgrandimaVertikalaDistancoAlCentro = maximumDe<ℤ>;
    Paro<ℕ, ℕ> proximimaWorto(0, 0);
    
    for (ℕ i_frazaro = 0; i_frazaro < rezulto.frazaroj.grandon(); i_frazaro++)
    {
        for (ℕ i_worto = 0; i_worto < rezulto.frazaroj[i_frazaro].wortoj.grandon(); i_worto++)
        {
            const LegitaWorto& worto = rezulto.frazaroj[i_frazaro].wortoj[i_worto];
            ℤ vertikalaDistancoAlCentro = std::abs(worto.zono.y - punkto.y);
            ℤ distanco_x = determinuDistancon(punkto.x, worto.zono.x, worto.zono.l);
            ℤ distanco_y = determinuDistancon(punkto.y, worto.zono.y, worto.zono.a);
            ℚ distanco = std::sqrt(distanco_x * distanco_x + distanco_y * distanco_y);
            
            if (distanco < malgrandimaDistanco
                aŭ (ĉuAproximeEgalas(distanco, malgrandimaDistanco)
                    kaj vertikalaDistancoAlCentro < malgrandimaVertikalaDistancoAlCentro))
            {
                malgrandimaDistanco = distanco;
                malgrandimaVertikalaDistancoAlCentro = vertikalaDistancoAlCentro;
                proximimaWorto = {i_frazaro, i_worto};
            };
        }
    }
    
    eligu proximimaWorto;
}

#endif //WORTSERCXILO_LEGITAJWORTOJ_HPP
