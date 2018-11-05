#ifndef WORTSERCXILO_LEGANTODEBILDOJ_HPP
#define WORTSERCXILO_LEGANTODEBILDOJ_HPP

#include <tesseract/baseapi.h>
#include "Wortarestro.hpp"
#include "komuna/geom/Ortangelo.hpp"
#include "LegitaWorto.hpp"
#include "Bildleganto.hpp"
#include "komuna/UnikaroPara.hpp"

class TesseractLeganto : public RealigoDeBildleganto
{
public:
    explicit TesseractLeganto(UnikaroPara<Texto, Texto> parametroj, const Listo<Texto>& linguoj);
    explicit TesseractLeganto(Texto dosierujoDeTesseract, const Listo<Texto>& linguoj);
    ~TesseractLeganto() override = default;
    Texto nomon() const override { eligu nomo; }
    Rezulto leguBildon(const Texto& bilddosiero) override;
    Listo<Texto> donuElekteblajnLinguojn() const override;
    Nenio reagorduLinguojn(const Listo<Texto>& linguoj) override; // ankaŭ (re)ŝaltas tesseract
    Nenio kreuBlanknigranVersionDe(const Texto& koloraBildo, const Texto& celdosiero) const override;
    inline const static Texto nomo = "Tesseract";
    inline const static UnikaroPara<Texto, Texto> parametroj = {{"dosierujo de Tesseract", "dosierujo"}};
private:
    Nenio agorduDosierujonDeTesseract(Texto p_dosierujoDeTesseract);
    Buleo provuLegi(const Texto& bilddosiero);
    RezultoDeLegado kreuRezulton();
    Texto dosierujoDeTesseract;
    tesseract::TessBaseAPI tesseract;
};

#endif //WORTSERCXILO_LEGANTODEBILDOJ_HPP
