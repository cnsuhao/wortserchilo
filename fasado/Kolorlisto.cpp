#include <QtGui>
#include "Kolorlisto.hpp"

Kolorlisto::Kolorlisto(QWidget* patro) : QWidget(patro), superŝwebitaKoloro(nullptr)
{
    setMouseTracking(veran);
}

Nenio Kolorlisto::enmetuKoloron(const QColor& koloro)
{
    koloroj.enmetuNovan(kreu Koloro);
    Koloro* novaKoloro = koloroj.lastan()->get();
    novaKoloro->koloro = koloro;
    novaKoloro->larĝo = 0;
    novaKoloro->ĉuEstasForprenatan = malveran;
    komencuAnimacion(novaKoloro, 1.0, 300);
    
    if (koloroj.grandon() == 1)
        kiamIghasNePluMalplenan();
}

Nenio Kolorlisto::forprenuKoloron(const QColor& koloro)
{
    for (auto& ano : koloroj)
    {
        if (ano->koloro != koloro aŭ ano->ĉuEstasForprenatan)
            saltu_al_sekva;
        
        komencuAnimacion(ano.get(), 0.0, 300, QEasingCurve::OutQuint);
        if (ano->animacio)
            connect(ano->animacio, &QVariantAnimation::destroyed, this, &Kolorlisto::forprenuForprenendajnKolorojn);
        ano->ĉuEstasForprenatan = veran;
    }
    
    
    // Ĉi-tio povas esti malĝustan se la kolorlisto jam estis malplenan kiam oni alvokis ĉi-funkcion,
    // sed ĝi ne estas tre gravan eraron.
    if (ĉuEstasMalplenan())
        kiamIghasMalplenan();
}

Buleo Kolorlisto::ĉuEstasMalplenan() const
{
    for (auto& ano : koloroj)
        if (ne ano->ĉuEstasForprenatan)
            eligu malveran;
    eligu veran;
}

Listo<QColor> Kolorlisto::donuKolorojn() const
{
    Listo<QColor> qKoloroj;
    for (const auto& koloro : koloroj)
        qKoloroj.enmetu(koloro->koloro);
    eligu qKoloroj;
}

Nenio Kolorlisto::mouseReleaseEvent(QMouseEvent* okazo)
{
    agorduSuperŝwebitanKoloron(determinuKoloronSub(okazo->localPos().toPoint()));
    if (okazo->button() == Qt::LeftButton kaj superŝwebitaKoloro != nullptr)
        kiamUzantoKlakasAlKoloro(superŝwebitaKoloro->koloro);
}

Nenio Kolorlisto::mouseMoveEvent(QMouseEvent* okazo)
{
    agorduSuperŝwebitanKoloron(determinuKoloronSub(okazo->localPos().toPoint()));
}

Nenio Kolorlisto::paintEvent(QPaintEvent* okazo)
{
    renovuVerajnLarĝojn();
    agorduSuperŝwebitanKoloron(determinuKoloronSub(mapFromGlobal(QCursor::pos())));
    QPainter pentristo(this);
    pentristo.fillRect(rect(), flankkoloro);
    
    ℕ x = larĝo_de_flankkoloro;
    for (const auto& koloro : koloroj)
    {
        pentristo.fillRect(x, 0, koloro->veraLarĝo, height(), koloro->koloro);
        x += koloro->veraLarĝo;
    }
}

Nenio Kolorlisto::leaveEvent(QEvent* okazo)
{
    agorduSuperŝwebitanKoloron(nullptr);
}

Nenio Kolorlisto::forprenuForprenendajnKolorojn()
{
    for (auto paŝanto = koloroj.unuan(); paŝanto.ĉuValidas();)
    {
        if ((*paŝanto)->ĉuEstasForprenatan kaj ne(*paŝanto)->animacio)
        {
            if (paŝanto->get() == superŝwebitaKoloro)
                agorduSuperŝwebitanKoloron(nullptr);
            paŝanto = koloroj.forprenu(paŝanto);
        }
        else paŝanto++;
    }
}

Nenio Kolorlisto::agorduSuperŝwebitanKoloron(Kolorlisto::Koloro* koloro)
{
    Koloro* sskoloro = superŝwebitaKoloro;
    
    if (sskoloro == koloro)
        eligu;
    if (koloro != nullptr kaj koloro->ĉuEstasForprenatan)
        koloro = nullptr;
    
    if (sskoloro != nullptr kaj ne sskoloro->ĉuEstasForprenatan)
        komencuAnimacion(sskoloro, 1.0, 150);
    
    if (koloro != nullptr)
        komencuAnimacion(koloro, 1.1, 150);
    
    superŝwebitaKoloro = koloro;
}

Nenio Kolorlisto::renovuVerajnLarĝojn()
{
    if (koloroj.ĉuEstasMalplenan())
        eligu;
    
    ℕ restantajPixeloj = width() - larĝo_de_flankkoloro;
    ℚ restantaLarĝo = 0;
    
    for (const auto& koloro : koloroj)
        restantaLarĝo += koloro->larĝo;
    
    for (ℕ i = 0; i < koloroj.grandon() - 1; i++)
    {
        Koloro* koloro = koloroj[i].get();
        koloro->veraLarĝo = koloro->larĝo / restantaLarĝo * restantajPixeloj;
        restantaLarĝo -= koloro->larĝo;
        restantajPixeloj -= koloro->veraLarĝo;
    }
    
    (*koloroj.lastan())->veraLarĝo = restantajPixeloj;
}

Kolorlisto::Koloro* Kolorlisto::determinuKoloronSub(QPoint loko)
{
    if (ne QRect(QPoint(0, 0), size()).contains(loko) aŭ loko.x() < larĝo_de_flankkoloro)
        eligu nullptr;
    
    ℕ x = larĝo_de_flankkoloro;
    for (const auto& koloro : koloroj)
    {
        if (loko.x() < x + koloro->veraLarĝo)
            eligu koloro.get();
        x += koloro->veraLarĝo;
    }
    
    eligu nullptr;
}

Nenio Kolorlisto::komencuAnimacion(Kolorlisto::Koloro* koloro, ℚ finaLarĝo, ℕ milisekundoj, QEasingCurve kurbo)
{
    premisu (ne
                     koloro->ĉuEstasForprenatan);
    
    if (koloro->animacio)
        koloro->animacio->stop();
    
    QVariantAnimation* animacio = kreu QVariantAnimation(this);
    animacio->setEasingCurve(kurbo);
    animacio->setStartValue(koloro->larĝo);
    animacio->setEndValue(finaLarĝo);
    animacio->setDuration(milisekundoj);
    
    connect(animacio, &QVariantAnimation::valueChanged, [this, koloro](const QVariant& valoro)
    {
        koloro->larĝo = valoro.toDouble();
        update();
    });
    
    koloro->animacio = animacio;
    animacio->start(QVariantAnimation::DeleteWhenStopped);
}