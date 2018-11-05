#ifndef VORTSERCXILO_WORTARO_HPP
#define VORTSERCXILO_WORTARO_HPP

#include "komuna/cet/Leganto.hpp"
#include "Wortaro.hpp"
#include "Parsoid.hpp"

class Wortaro_wikitext1 : public Wortaro
{
public:
    // se retejoDeParsoid == "", donuHtmlDifinon donas la wikitexton.
    
    class Paŝanto
    {
    public:
        Paŝanto(Leganto&& leganto, const Texto& p_retejoDeParsoid)
                : leganto(formovu(leganto)), retejoDeParsoid(p_retejoDeParsoid) {};
        Buleo ĉuValidas();
        Nenio paŝuAntaŭen(); // donas la worton sekvan dilaŭ alfabeta ordo
        Nenio paŝuRetroen(); // donas la worton malsekvan dilaŭ alfabeta ordo
        Texto donuWorton();
        Texto donuHtmlDifinon();
    private:
        Texto retejoDeParsoid;
        Leganto leganto;
        Parsoid parsoid;
    };
    
    Wortaro_wikitext1(std::function<Leganto()> p_kreuLeganton, const Texto& p_retejoDeParsoid = "");
    SymSpell kreuSugestanton() override;
    Texto donuHtmlDifinonDe(const Texto& worto) const override;
    Nenio agorduRetejonDeParsoid(const Texto& p_retejo) override;
    
    Paŝanto unuan() const;
    Paŝanto lastan() const;
    Paŝanto postlastan() const;
    Paŝanto provuTrovi(const Texto& worto) const;
private:
    Texto determinuFonton(Texto unuaLinio) const;
    Leganto trovuUnuanAperonDeWorto(const Texto& worto) const;
    std::function<Leganto()> kreuLeganton;
    Texto retejoDeParsoid;
    ℤ8 unuaCelo;
    ℤ8 lastaCelo;
};

#endif //VORTSERCXILO_WORTARO_HPP
