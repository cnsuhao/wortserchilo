#ifndef KOMUNA_ALVOKODIKUNFORLASEBLAJARGUMENTOJ_HPP
#define KOMUNA_ALVOKODIKUNFORLASEBLAJARGUMENTOJ_HPP

#include "ĉu_enhavas_iun_funkcion.hpp"
#include "specoj.hpp"

template<class Traktu, class P1, class P2 = ℕ, class P3 = ℕ>
class AlvokoDikunForlaseblajArgumentoj
{
private:
    KREU_KRAMPAJ_ĉu_enhavas_(p3, malveraEkzemploDe<P1>(), malveraEkzemploDe<P2>(), malveraEkzemploDe<P3>());
    KREU_KRAMPAJ_ĉu_enhavas_(p2, malveraEkzemploDe<P1>(), malveraEkzemploDe<P2>());
    KREU_KRAMPAJ_ĉu_enhavas_(p1, malveraEkzemploDe<P1>());
    KREU_KRAMPAJ_ĉu_enhavas_(p0);
    static constexpr ℕ nombro = ĉu_enhavas_p3<Traktu> ? 3 :
                                                  (ĉu_enhavas_p2<Traktu> ? 2 :
                                                   (ĉu_enhavas_p1<Traktu> ? 1 : 0)); //-«
    tuj_premisu (nombro != 0 aŭ ĉu_enhavas_p0<Traktu>); //»-
public:
    AlvokoDikunForlaseblajArgumentoj(Traktu p_traktu) : traktu(p_traktu) {}
    
    template<ℕ n = nombro> uzu_se_<n == 3, Nenio> operator()(P1 a = P1(), P2 b = P2(), P3 c = P3()) { traktu(a, b, c); }
    template<ℕ n = nombro> uzu_se_<n == 2, Nenio> operator()(P1 a = P1(), P2 b = P2(), P3 c = P3()) { traktu(a, b); }
    template<ℕ n = nombro> uzu_se_<n == 1, Nenio> operator()(P1 a = P1(), P2 b = P2(), P3 c = P3()) { traktu(a); }
    template<ℕ n = nombro> uzu_se_<n == 0, Nenio> operator()(P1 a = P1(), P2 b = P2(), P3 c = P3()) { traktu(); }
private:
    Traktu traktu;
};
#endif //KOMUNA_ALVOKODIKUNFORLASEBLAJARGUMENTOJ_HPP
