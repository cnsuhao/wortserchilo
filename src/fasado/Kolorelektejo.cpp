#include <QtGui>
#include "Kolorelektejo.hpp"

Kolorelektejo::Kolorelektejo(QWidget* patro) : QWidget(patro), ĉuMusoEstasEnFasadano(malveran), zomfaktoro(1)
{
    setMouseTracking(veran);
}

Nenio Kolorelektejo::ŝarĝuBildon(Texto dosiero)
{
    fontbildo.load(dosiero.QT());
    if (fontbildo.format() != QImage::Format_RGB32)
        fontbildo = fontbildo.convertToFormat(QImage::Format_RGB32);
    update();
}

Nenio Kolorelektejo::agorduCentranLokon(Vektor2D<ℤ> novaCentraLoko)
{
    Vektor2D<ℤ> malnovaCentraLoko = centraLoko;
    centraLoko = novaCentraLoko;
    if (malnovaCentraLoko != novaCentraLoko)
        kiamOniShanghasCentranLokon(novaCentraLoko);
    update();
}

Nenio Kolorelektejo::agorduZomfaktoron(int p_zomfaktoro)
{
    ℤ malnovaZomfaktoro = zomfaktoro;
    zomfaktoro = p_zomfaktoro;
    if (malnovaZomfaktoro != p_zomfaktoro)
        kiamOniShanghasZomfaktoron(zomfaktoro);
    update();
}

Nenio Kolorelektejo::mousePressEvent(QMouseEvent* okazo)
{
    QWidget::mousePressEvent(okazo);
    if (okazo->button() == Qt::LeftButton)
        kiamUzantoLiveKlakasAlKoloro(donuKoloronSubMuso());
    else if (okazo->button() == Qt::RightButton)
        kiamUzantoDextreKlakasAlKoloro(donuKoloronSubMuso());
    update();
}

Nenio Kolorelektejo::mouseMoveEvent(QMouseEvent* okazo)
{
    update();
}

Nenio Kolorelektejo::wheelEvent(QWheelEvent* okazo)
{
    Buleo ĉuAkceptis = veran;
    system_clock::time_point nun = system_clock::now();
    
    agorduCentranLokon(donuBildkoordinatonDe(donuMuslokon()));
    
    if (okazo->angleDelta().y() > 0 kaj zomfaktoro + 2 <= maximuma_zomfaktoro)
        agorduZomfaktoron(zomfaktoro + 2);
    else if (okazo->angleDelta().y() < 0 kaj zomfaktoro - 2 >= minimuma_zomfaktoro)
        agorduZomfaktoron(zomfaktoro - 2);
    else if (nun - tempoDeLastaAkceptitaMusradrulo > daŭro_dum_kiu_ni_ankoraŭ_akceptas_musradruloj_sen_efekto)
        ĉuAkceptis = malveran;
    
    if (ĉuAkceptis)
    {
        okazo->accept();
        tempoDeLastaAkceptitaMusradrulo = nun;
    }
}

Nenio Kolorelektejo::paintEvent(QPaintEvent* okazo)
{
    Ortangelo<ℤ> videblaZono = determinuVideblanPartonDeBildo();
    QRect qVideblaZono(videblaZono.x, videblaZono.y, videblaZono.l, videblaZono.a);
    QRect celzono(0, 0, width(), height());
    QPainter pentristo(this);
    pentristo.setRenderHint(QPainter::Antialiasing, malveran);
    pentristo.setCompositionMode(QPainter::CompositionMode_SourceOver);
    pentristo.drawImage(celzono, fontbildo, qVideblaZono);
    
    if (ĉuMusoEstasEnFasadano kaj QRect(QPoint(0, 0), size()).contains(donuMuslokon()))
    {
        QRect kolorortangelo(width() - 40, 0, width(), 30);
        QColor koloro = donuKoloronSubMuso();
        pentristo.setPen(koloro);
        pentristo.setBrush(koloro);
        pentristo.drawRect(kolorortangelo);
    }
    
    pentristo.end();
}

Nenio Kolorelektejo::enterEvent(QEvent* okazo)
{
    ĉuMusoEstasEnFasadano = veran;
}

Nenio Kolorelektejo::leaveEvent(QEvent* okazo)
{
    ĉuMusoEstasEnFasadano = malveran;
    update();
}

QColor Kolorelektejo::donuKoloronSubMuso() const
{
    Vektor2D<ℤ> bildkoordinato = donuBildkoordinatonDe(donuMuslokon());
    eligu fontbildo.pixelColor(bildkoordinato.x, bildkoordinato.y);
}

QPoint Kolorelektejo::donuMuslokon() const
{
    eligu mapFromGlobal(QCursor::pos());
}

Vektor2D<ℤ> Kolorelektejo::donuBildkoordinatonDe(const QPoint& loko) const
{
    Ortangelo<ℤ> videblaParto = determinuVideblanPartonDeBildo();
    eligu Vektor2D<ℤ>(loko.x(), loko.y()) / zomfaktoro + Vektor2D<ℤ>(videblaParto.x, videblaParto.y);
}

Ortangelo<ℤ> Kolorelektejo::determinuVideblanPartonDeBildo() const
{
    Ortangelo<ℤ> zono(0, 0, rect().width() / zomfaktoro, rect().height() / zomfaktoro);
    zono.x = centraLoko.x - zono.l / 2;
    zono.y = centraLoko.y - zono.a / 2;
    zono.x = std::min(zono.x, fontbildo.size().width() - zono.l);
    zono.y = std::min(zono.y, fontbildo.size().height() - zono.a);
    zono.x = std::max(zono.x, 0);
    zono.y = std::max(zono.y, 0);
    eligu zono;
}