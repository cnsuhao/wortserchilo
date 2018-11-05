#include <QtGui>
#include <QtWidgets/QApplication>
#include "Desegnejo.hpp"

BinaraDesegnejo::BinaraDesegnejo(QWidget* patro)
        : QWidget(patro), ĉuDesegnisIonEkdeKursoroEnirisFasadano(malveran), ĉuPentrasIon(malveran),
          ĉuMusoEstasEnFasadano(malveran), livaBroŝo(nigra_broŝo), zomfaktoro(1), broŝgrando(1)
{
    setMouseTracking(veran);
}

Nenio BinaraDesegnejo::ŝarĝuBildon(Texto dosiero)
{
    fontbildo.load(dosiero.QT());
    if (fontbildo.format() != QImage::Format_RGB32)
        fontbildo = fontbildo.convertToFormat(QImage::Format_RGB32);
    surmetaBildo = QImage(fontbildo.size(), QImage::Format_ARGB32);
    surmetaBildo.fill(QColor(0, 0, 0, 0));
    emfazoj.malplenigu();
    update();
}

Nenio BinaraDesegnejo::konservuBildon(Texto dosiero)
{
    QImage celbildo = fontbildo;
    QPainter pentristo(&celbildo);
    pentristo.setCompositionMode(QPainter::CompositionMode_SourceOver);
    pentristo.drawImage(celbildo.rect(), surmetaBildo);
    pentristo.end();
    celbildo.save(dosiero.QT());
}

Nenio BinaraDesegnejo::enmetuEmfazon(Ortangelo<ℤ> zono)
{
    emfazoj.enmetu(zono);
    update();
}

Nenio BinaraDesegnejo::forprenuEmfazon(Ortangelo<ℤ> zono)
{
    auto serĉrezulto = emfazoj.provuTrovi(zono);
    if (serĉrezulto.ĉuValidas())
        emfazoj.forprenu(serĉrezulto);
    update();
}

Nenio BinaraDesegnejo::agorduBroshgrandon(int p_broshgrando)
{
    broŝgrando = p_broshgrando;
    update();
}

Nenio BinaraDesegnejo::agorduCentranLokon(Vektor2D<ℤ> novaCentraLoko)
{
    Vektor2D<ℤ> malnovaCentraLoko = centraLoko;
    centraLoko = novaCentraLoko;
    if (malnovaCentraLoko != novaCentraLoko)
        kiamOniShanghasCentranLokon(novaCentraLoko);
    update();
}

Nenio BinaraDesegnejo::agorduZomfaktoron(int p_zomfaktoro)
{
    ℤ malnovaZomfaktoro = zomfaktoro;
    zomfaktoro = p_zomfaktoro;
    if (malnovaZomfaktoro != p_zomfaktoro)
        kiamOniShanghasZomfaktoron(zomfaktoro);
    update();
}

Nenio BinaraDesegnejo::mousePressEvent(QMouseEvent* okazo)
{
    QWidget::mousePressEvent(okazo);
    ĉuPentrasIon = ĉuOniPremasIunMusklavon(okazo);
    aplikuBroŝojn(okazo);
    if (ĉuPentrasIon)
        ĉuDesegnisIonEkdeKursoroEnirisFasadano = veran;
    update();
}

Nenio BinaraDesegnejo::mouseReleaseEvent(QMouseEvent* okazo)
{
    QWidget::mouseReleaseEvent(okazo);
    ĉuPentrasIon = ĉuOniPremasIunMusklavon(okazo);
    update();
}

Nenio BinaraDesegnejo::mouseMoveEvent(QMouseEvent* okazo)
{
    aplikuBroŝojn(okazo);
    update();
}

Nenio BinaraDesegnejo::wheelEvent(QWheelEvent* okazo)
{
    if (okazo->modifiers() & Qt::ShiftModifier)
    {
        if (okazo->angleDelta().y() > 0)
            broŝgrando = std::min(broŝgrando + 1, maximuma_broŝgrando);
        else if (okazo->angleDelta().y() < 0)
            broŝgrando = std::max(broŝgrando - 1, minimuma_broŝgrando);
        update();
        okazo->accept();
    }
    else
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
}

Nenio BinaraDesegnejo::paintEvent(QPaintEvent* okazo)
{
    QImage provizoraSurmetaBildo = surmetaBildo;
    Ortangelo<ℤ> videblaZono = determinuVideblanPartonDeBildo();
    Vektor2D<ℤ> livaSupraPunkto(videblaZono.x, videblaZono.y);
    QRect qVideblaZono(videblaZono.x, videblaZono.y, videblaZono.l, videblaZono.a);
    QRect celzono(QPoint(0, 0), size());
    QPainter pentristo(this);
    
    if (ĉuMusoEstasEnFasadano kaj ne ĉuPentrasIon)
    {
        Vektor2D<ℤ> _bildkoordinato = donuBildkoordinatonDe(donuMuslokon());
        if (QApplication::keyboardModifiers() & Qt::ALT)
            aplikuBroŝon(nigra_inundanto, _bildkoordinato, &provizoraSurmetaBildo);
        else if (QApplication::keyboardModifiers() & Qt::CTRL)
            aplikuBroŝon(blanka_inundanto, _bildkoordinato, &provizoraSurmetaBildo);
        else aplikuBroŝon(livaBroŝo, _bildkoordinato, &provizoraSurmetaBildo);
    }
    
    pentristo.setRenderHint(QPainter::Antialiasing, malveran);
    pentristo.setCompositionMode(QPainter::CompositionMode_SourceOver);
    pentristo.drawImage(celzono, fontbildo, qVideblaZono);
    pentristo.drawImage(celzono, provizoraSurmetaBildo, qVideblaZono);
    
    QImage neEmfazitaZono(size(), QImage::Format_ARGB32);
    neEmfazitaZono.fill(QColor(230, 230, 230));
    QPainter neEmfazitaPentristo(&neEmfazitaZono);
    neEmfazitaPentristo.setCompositionMode(QPainter::CompositionMode_DestinationOut);
    neEmfazitaPentristo.setBrush(QColor(Qt::black));
    
    for (Ortangelo<ℤ> ortangelo : emfazoj)
    {
        ortangelo -= livaSupraPunkto;
        ortangelo.x *= zomfaktoro;
        ortangelo.y *= zomfaktoro;
        ortangelo.l *= zomfaktoro;
        ortangelo.a *= zomfaktoro;
        neEmfazitaPentristo.drawRect(QRect(ortangelo.x, ortangelo.y, ortangelo.l, ortangelo.a + 1));
        
        if (zomfaktoro == 1)
            pentristo.drawLine(ortangelo.x, ortangelo.y + ortangelo.a + 1,
                               ortangelo.x + ortangelo.l, ortangelo.y + ortangelo.a + 1);
    }
    
    neEmfazitaPentristo.end();
    pentristo.setOpacity(.4);
    pentristo.drawImage(celzono, neEmfazitaZono);
    
    pentristo.end();
}

Nenio BinaraDesegnejo::enterEvent(QEvent* okazo)
{
    ĉuMusoEstasEnFasadano = veran;
}

Nenio BinaraDesegnejo::leaveEvent(QEvent* okazo)
{
    if (ĉuDesegnisIonEkdeKursoroEnirisFasadano)
        kiamUzantoFinisDesegniIon();
    ĉuDesegnisIonEkdeKursoroEnirisFasadano = malveran;
    ĉuMusoEstasEnFasadano = malveran;
    update();
}

Buleo BinaraDesegnejo::ĉuOniPremasIunMusklavon(const QMouseEvent* okazo) const
{
    eligu okazo->buttons() & Qt::LeftButton | okazo->buttons() & Qt::RightButton | okazo->buttons() & Qt::MidButton;
}

Nenio BinaraDesegnejo::aplikuBroŝojn(QMouseEvent* okazo)
{
    Vektor2D<ℤ> bildkoordinato = donuBildkoordinatonDe(okazo->localPos().toPoint());
    
    if (okazo->modifiers() & Qt::ALT kaj okazo->buttons() & Qt::LeftButton)
        aplikuBroŝon(nigra_inundanto, bildkoordinato, &surmetaBildo);
    else if (okazo->modifiers() & Qt::CTRL kaj okazo->buttons() & Qt::LeftButton)
        aplikuBroŝon(blanka_inundanto, bildkoordinato, &surmetaBildo);
    else if (okazo->buttons() & Qt::LeftButton)
        aplikuBroŝon(livaBroŝo, bildkoordinato, &surmetaBildo);
    else if (okazo->buttons() & Qt::RightButton)
        aplikuBroŝon(blanka_broŝo, bildkoordinato, &surmetaBildo);
    else if (okazo->buttons() & Qt::MidButton)
        aplikuBroŝon(wiŝilo, bildkoordinato, &surmetaBildo);
}

Nenio BinaraDesegnejo::aplikuBroŝon(BinaraDesegnejo::Broŝo broŝo, Vektor2D<ℤ> koordinato, QImage* bildo)
{
    if (broŝo == nigra_inundanto)
        inundu(koordinato, Qt::black, &fontbildo, &surmetaBildo, bildo);
    else if (broŝo == blanka_inundanto)
        inundu(koordinato, Qt::white, &fontbildo, &surmetaBildo, bildo);
    else
        aplikuNormanBroŝon(broŝo, koordinato, broŝgrando, bildo);
}

Nenio BinaraDesegnejo::aplikuNormanBroŝon(Broŝo broŝo, Vektor2D<ℤ> koordinato, ℤ broŝgrando, QImage* celbildo)
{
    QPainter pentristo(celbildo);
    pentristo.setRenderHint(QPainter::Antialiasing, malveran);
    
    QColor koloro = Qt::black;
    
    if (broŝo == blanka_broŝo)
        koloro = Qt::white;
    else if (broŝo == wiŝilo)
        pentristo.setCompositionMode(QPainter::CompositionMode_DestinationOut);
    
    pentristo.setPen(koloro);
    pentristo.setBrush(koloro);
    
    if (broŝgrando == 1)
        pentristo.drawPoint(koordinato.x, koordinato.y);
    else
        pentristo.drawEllipse(koordinato.x - broŝgrando / 2, koordinato.y - broŝgrando / 2,
                              broŝgrando - 1, broŝgrando - 1);
    pentristo.end();
}


Nenio BinaraDesegnejo::inundu(Vektor2D<ℤ> koordinato, QColor koloro, const QImage* bildo1, const QImage* bildo2,
                              QImage* celbildo)
{
    QImage bildo = *bildo1;
    QPainter pentristo(&bildo);
    pentristo.setCompositionMode(QPainter::CompositionMode_SourceOver);
    pentristo.drawImage(bildo.rect(), *bildo2);
    pentristo.end();
    
    std::deque<Vektor2D<ℤ>> traktotajLokoj;
    
    auto traktuNovanLokon = [&](Vektor2D<ℤ> loko)
    {
        if (loko.x < 0 aŭ loko.y < 0 aŭ loko.x >= bildo.width() aŭ loko.y >= bildo.height()
            aŭ bildo.pixelColor(loko.x, loko.y) == koloro)
            eligu;
        bildo.setPixelColor(loko.x, loko.y, koloro);
        celbildo->setPixelColor(loko.x, loko.y, koloro);
        traktotajLokoj.push_back(loko);
    };
    
    traktuNovanLokon(koordinato);
    
    while (ne traktotajLokoj.empty())
    {
        Vektor2D<ℤ> loko = traktotajLokoj.front();
        traktotajLokoj.pop_front();
        traktuNovanLokon(loko + Vektor2D<ℤ>(0, 1));
        traktuNovanLokon(loko + Vektor2D<ℤ>(1, 0));
        traktuNovanLokon(loko + Vektor2D<ℤ>(0, -1));
        traktuNovanLokon(loko + Vektor2D<ℤ>(-1, 0));
    }
    
    pentristo.end();
}

QPoint BinaraDesegnejo::donuMuslokon() const
{
    eligu mapFromGlobal(QCursor::pos());
}

Vektor2D<ℤ> BinaraDesegnejo::donuBildkoordinatonDe(const QPoint& loko) const
{
    Ortangelo<ℤ> videblaParto = determinuVideblanPartonDeBildo();
    eligu Vektor2D<ℤ>(loko.x(), loko.y()) / zomfaktoro + Vektor2D<ℤ>(videblaParto.x, videblaParto.y);
}

Ortangelo<ℤ> BinaraDesegnejo::determinuVideblanPartonDeBildo() const
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