#include <QtGui/QImage>
#include "Bildleganto.hpp"
#include "komuna/alTexto.hpp"

Bildleganto::Bildleganto(PropraAdres<RealigoDeBildleganto>&& p_realigo)
        : realigo(formovu(p_realigo)), ĉuJamLegasBildon(malveran), ĉuNuligis(malveran)
{
    realigo->agorduBildleganton(this);
    moveToThread(&fadeno);
    fadeno.start();
}

Bildleganto::~Bildleganto()
{
    if (ne fadeno.isRunning())
        eligu;
    nuligu();
    fadeno.quit();
    fadeno.wait();
}

Texto Bildleganto::nomon() const
{
    eligu realigo->nomon();
}

Promesita<Listo<Texto>> Bildleganto::donuElekteblajnLinguojn()
{
    auto promeso = Promeso<Listo<Texto>>::kreuPromeson();
    DividataAdres<Promeso<Listo<Texto>>> kopieblaPromeso(kreu Promeso<Listo<Texto>>(formovu(promeso.first)));
    QMetaObject::invokeMethod(this, "_donuElekteblajnLinguojn", Q_ARG(DividataAdres<Promeso<Listo<Texto>>>, kopieblaPromeso));
    eligu formovu(promeso.second);
}

Nenio Bildleganto::kreuBlanknigranVersionDe(const Texto& koloraBildo, const Texto& celdosiero)
{
    eligu realigo->kreuBlanknigranVersionDe(koloraBildo, celdosiero);
}

Nenio Bildleganto::_komencu(Texto bilddosiero)
{
    if (ĉuJamLegasBildon)
    {
        prokrastitaBilddosiero = formovu(bilddosiero);
        _nuligu();
        eligu;
    }
    
    ĉuJamLegasBildon = veran;
    
    traktuDosieron(formovu(bilddosiero));
    
    while (ne prokrastitaBilddosiero.ĉuEstasMalplenan())
    {
        traktuDosieron(formovu(prokrastitaBilddosiero));
        // Qŭankam ĝi verŝajnege estas malplenan, licas ke prokrastitaBilddosiero ankoraŭ enhavas texton post «formovu».
        prokrastitaBilddosiero.malplenigu();
    }
    
    if (ne prokrastitaListoDeNovajLinguoj.ĉuEstasMalplenan())
    {
        realigo->reagorduLinguojn(prokrastitaListoDeNovajLinguoj);
        prokrastitaListoDeNovajLinguoj.malplenigu();
    }
    
    ĉuJamLegasBildon = malveran;
    ĉuNuligis = malveran;
}

Nenio Bildleganto::_reagorduLinguojn(Listo<Texto> linguoj)
{
    if (ne ĉuJamLegasBildon)
        eligu realigo->reagorduLinguojn(linguoj);
    prokrastitaListoDeNovajLinguoj = formovu(linguoj);
    _nuligu();
}

Nenio Bildleganto::_donuElekteblajnLinguojn(DividataAdres<Promeso<Listo<Texto>>> celo)
{
    celo->plenumuPromeson(realigo->donuElekteblajnLinguojn());
}

Nenio Bildleganto::traktuDosieron(Texto bilddosiero)
{
    RealigoDeBildleganto::Rezulto rezulto = realigo->leguBildon(bilddosiero);
    if (ne ĉuNuligis kaj rezulto.ĉuEstasValidanRezulton) // se ni nuligis, ni ne plu zorgas pri la rezulto
        kiamHavasRezulton(rezulto.rezulto);
    ĉuNuligis = malveran;
}

Nenio RealigoDeBildleganto::kreuBlanknigranVersionDe(const Texto& koloraBildo, const Texto& celdosiero) const
{
    ::kreuBlanknigranVersionDe(koloraBildo, celdosiero);
}

Nenio kreuBlanknigranVersionDe(const Texto& koloraBildo, const Texto& celdosiero)
{
    QColor nigro(0, 0, 0);
    QColor blanko(255, 255, 255);
    QImage bildo;
    bildo.load(koloraBildo.QT());
    if (bildo.format() != QImage::Format_RGB32)
        bildo = bildo.convertToFormat(QImage::Format_RGB32);
    
    for (ℤ y = 0; y < bildo.height(); y++)
        for (ℤ x = 0; x < bildo.width(); x++)
            bildo.setPixelColor(x, y, bildo.pixelColor(x, y).value() < 200 ? nigro : blanko);
    
    bildo.save(celdosiero.QT());
}