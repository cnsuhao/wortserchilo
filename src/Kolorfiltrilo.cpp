#include "Kolorfiltrilo.hpp"
#include "komuna/trajtoj/numero.hpp"

void Kolorfiltrilo::kreuBlanknigranBildon(const Texto& fontdosiero, const Texto& celdosiero) const
{
    auto filtruPixelon = [this](ℤ x, ℤ y, QImage* bildo)
    {
        auto determinuDiferencon = [](const QColor& a, const QColor& b) -> ℤ
        {
            eligu std::abs(a.red() - b.red()) + std::abs(a.green() - b.green()) + std::abs(a.blue() - b.blue());
        };
        
        const static QColor nigro(Qt::black);
        const static QColor blanko(Qt::white);
        QColor koloro = bildo->pixelColor(x, y);
        QColor finaKoloro = blanko;
        ℤ malgrandimaDiferenco = maximumDe<ℤ>;
        
        auto traktuKoloron = [&](const QColor& filtro, const QColor& celkoloroDeFiltro)
        {
            ℤ diferenco = determinuDiferencon(koloro, filtro);
            if (diferenco > malgrandimaDiferenco)
                eligu;
            malgrandimaDiferenco = diferenco;
            finaKoloro = celkoloroDeFiltro;
        };
    
        for (const QColor& blankaKoloro : blankajKoloroj)
            traktuKoloron(blankaKoloro, blanko);
        for (const QColor& nigraKoloro : nigrajKoloroj)
            traktuKoloron(nigraKoloro, nigro);
        
        bildo->setPixelColor(x, y, finaKoloro);
    };
    
    
    QImage bildo;
    bildo.load(fontdosiero.QT());
    
    if (bildo.format() != QImage::Format_RGB32)
        bildo = bildo.convertToFormat(QImage::Format_RGB32);
    
    for (ℤ y = 0; y < bildo.height(); y++)
        for (ℤ x = 0; x < bildo.width(); x++)
            filtruPixelon(x, y, &bildo);
    
    bildo.save(celdosiero.QT());
}