#include <qevent.h>
#include "AranĝantoKunAnimacioj.hpp"
#include "../komuna/Unikaro.hpp"
#include "komencuAnimacion.hpp"
#include "../komuna/geom/SegmentoDeRekto.hpp"

AranghantoKunAnimacioj::Aranĝo::Ano::Ano
        (QWidget* widget, Vektor2D<ℚ> loko, Vektor2D<ℚ> grando, Vektor2D<ℤ> deiĝo, Vektor2D<ℤ> deiĝoDeGrando)
        : loko(loko), deiĝo(deiĝo), grando(grando), deiĝoDeGrando(deiĝoDeGrando)
{
    agorduWidgeton(widget);
}

AranghantoKunAnimacioj::Aranĝo::Ano::Ano(QWidget* widget, ℚ x, ℚ y, ℚ l, ℚ a, ℤ d_x, ℤ d_y, ℤ d_l, ℤ d_a)
        : loko(x, y), deiĝo(d_x, d_y), grando(l, a), deiĝoDeGrando(d_l, d_a)
{
    agorduWidgeton(widget);
}

Nenio AranghantoKunAnimacioj::Aranĝo::Ano::renovuZonon(Vektor2D<ℤ> grandoDePatro)
{
    Vektor2D<ℤ> loko = determinuFinanLokon(grandoDePatro);
    Vektor2D<ℤ> grando = determinuFinanGrandon(grandoDePatro);
    if (ĉuWidgetValidas())
        widget->setGeometry(loko.x, loko.y, grando.x, grando.y);
}

Vektor2D<ℤ> AranghantoKunAnimacioj::Aranĝo::Ano::determinuFinanLokon(Vektor2D<ℤ> grandoDePatro) const
{
    eligu Vektor2D<ℤ>(std::round(loko.x * grandoDePatro.x), std::round(loko.y * grandoDePatro.y)) + deiĝo;
}

Vektor2D<ℤ> AranghantoKunAnimacioj::Aranĝo::Ano::determinuFinanGrandon(Vektor2D<ℤ> grandoDePatro) const
{
    eligu Vektor2D<ℤ>(std::round(grando.x * grandoDePatro.x), std::round(grando.y * grandoDePatro.y)) + deiĝoDeGrando;
}

Vektor2D<ℤ> AranghantoKunAnimacioj::Aranĝo::determinuMinimumanGrandon() const
{
    ℤ larĝo = 0;
    ℤ alto = 0;
    
    for (const Ano& ano : anoj)
    {
        if (ne ano.ĉuWidgetValidas())
            saltu_al_sekva;
        ℤ ĉiLarĝo = (ano.widget->minimumWidth() - ano.deiĝoDeGrando.x) / ano.grando.x;
        ℤ ĉiAlto = (ano.widget->minimumHeight() - ano.deiĝoDeGrando.y) / ano.grando.y;
        if (ĉiLarĝo > larĝo)
            larĝo = ĉiLarĝo;
        if (ĉiAlto > alto)
            alto = ĉiAlto;
    }
    
    eligu {larĝo, alto};
}

Vektor2D<ℤ> AranghantoKunAnimacioj::Aranĝo::determinuMaximumanGrandon() const
{
    ℤ larĝo = QLAYOUTSIZE_MAX;
    ℤ alto = QLAYOUTSIZE_MAX;
    
    for (const Ano& ano : anoj)
    {
        if (ne ano.ĉuWidgetValidas())
            saltu_al_sekva;
        ℤ ĉiLarĝo = ano.grando.x == 0 ? QLAYOUTSIZE_MAX //-«
           : std::min<ℚ>(QLAYOUTSIZE_MAX, ŝanĝu_al<ℚ>(ano.widget->maximumWidth() - ano.deiĝoDeGrando.x) / ano.grando.x);
        ℤ ĉiAlto = ano.grando.y == 0 ? QLAYOUTSIZE_MAX
          : std::min<ℚ>(QLAYOUTSIZE_MAX, ŝanĝu_al<ℚ>(ano.widget->maximumHeight() - ano.deiĝoDeGrando.y) / ano.grando.y);
        if (ĉiLarĝo < larĝo) //»-
            larĝo = ĉiLarĝo;
        if (ĉiAlto < alto)
            alto = ĉiAlto;
    }
    
    eligu {larĝo, alto};
}

Buleo AranghantoKunAnimacioj::Aranĝo::ĉuĜustas() const
{
    Listo<QWidget*> widgetoj;
    
    for (const Ano& ano : anoj)
        if (ano.ĉuWidgetValidas() kaj widgetoj.ĉuEnhavas(ano.widget))
            eligu malveran;
        else widgetoj.enmetu(ano.widget);
    
    eligu veran;
}

Listo<AranghantoKunAnimacioj::Aranĝo::Ano>::NeŝanĝeblaPaŝanto
AranghantoKunAnimacioj::Aranĝo::provuTrovi(QWidget* widget) const
{
    eligu anoj.provuTrovi(widget, [](const Ano& ano, const QWidget* widget) -> Buleo { eligu ano.widget == widget; });
}

Buleo AranghantoKunAnimacioj::Aranĝo::ĉuEnhavas(QWidget* widget) const
{
    eligu provuTrovi(widget).ĉuValidas();
}

Nenio AranghantoKunAnimacioj::preterlasuAnimacion()
{
    if (ne ĉuLudasAnimacion())
        eligu;
    
    for (QPointer<QVariantAnimation> animacio : ludantajAnimacioj)
    {
        if (ne animacio)
            saltu_al_sekva;
        animacio->valueChanged(animacio->endValue());
        animacio->stop();
    }
    
    traktuKeAnimacioFinis();
}

Nenio AranghantoKunAnimacioj::haltuAnimacion()
{
    if (ne ĉuLudasAnimacion())
        eligu;
    for (QPointer<QVariantAnimation> animacio : ludantajAnimacioj)
        if (animacio)
            animacio->stop();
    traktuKeAnimacioFinis();
}

Nenio AranghantoKunAnimacioj::agorduAranĝonSenAnimacio(Aranĝo novaAranĝo)
{
    premisu (novaAranĝo.ĉuĜustas());
    
    if (ĉuLudasAnimacion())
        haltuAnimacion();
    
    for (Aranĝo::Ano& ano : aranĝo.anoj)
        if (ano.ĉuWidgetValidas())
            ano.widget->hide();
    
    aranĝo = formovu(novaAranĝo);
    setMinimumSize(minimumanGrandon());
    setMaximumSize(maximumanGrandon());
    
    for (Aranĝo::Ano& ano : aranĝo.anoj)
    {
        ano.renovuZonon(grandon());
        if (ano.ĉuWidgetValidas())
            ano.widget->show();
    }
}

Nenio AranghantoKunAnimacioj::agorduAranĝonRulante(Aranĝo novaAranĝo, Direkto dir, ℕ milisekundoj, QEasingCurve kurbo)
{
    premisu (novaAranĝo.ĉuĜustas());
    
    if (ĉuLudasAnimacion())
        haltuAnimacion();
    
    Aranĝo malnovaAranĝo = formovu(aranĝo);
    aranĝo = formovu(novaAranĝo);
    setMinimumSize(minimumanGrandon());
    setMaximumSize(maximumanGrandon());
    
    auto[novajAnoj, novajRestantajAnoj, malnovajRestantajAnoj, malnovajAnoj] //-«
         = determinuŜanĝojnEnAranĝo(aranĝo, malnovaAranĝo); //»-
    
    for (ℕ i = 0; i < novajRestantajAnoj.grandon(); i++)
    {
        Aranĝo::Ano* nova = novajRestantajAnoj[i];
        const Aranĝo::Ano* malnova = malnovajRestantajAnoj[i];
        SegmentoDeRekto2D<ℚ> Δloko(malnova->loko, nova->loko - malnova->loko);
        SegmentoDeRekto2D<ℤ> Δdeiĝo(malnova->deiĝo, nova->deiĝo - malnova->deiĝo);
        SegmentoDeRekto2D<ℚ> Δgrando(malnova->grando, nova->grando - malnova->grando);
        SegmentoDeRekto2D<ℤ> ΔdeiĝoDeGrando(malnova->deiĝoDeGrando, nova->deiĝoDeGrando - malnova->deiĝoDeGrando);
        
        QVariantAnimation* a = kreuAnimacion(nova->widget, 0.0, 1.0, milisekundoj, kurbo,
                                             [this, nova, Δloko, Δdeiĝo, Δgrando, ΔdeiĝoDeGrando](const QVariant& q)//-«
        { //»-
            ℚ s = q.toDouble();
            nova->loko = Δloko.ĉe(s);
            nova->deiĝo = Δdeiĝo.ĉe(s);
            nova->grando = Δgrando.ĉe(s);
            nova->deiĝoDeGrando = ΔdeiĝoDeGrando.ĉe(s);
            nova->renovuZonon(this->grandon());
        });
        
        connect(a, &QVariantAnimation::destroyed, [this, a]() { traktuKeAnimacioFinis(a); });
        ludantajAnimacioj.enmetu(a);
        a->start(QVariantAnimation::DeleteWhenStopped);
    }
    
    QPointF loko0 = {0.0, 0.0};
    QPointF loko1;
    
    if (dir == Direkto::supren)
        loko1 = {0.0, -1.0};
    else if (dir == Direkto::suben)
        loko1 = {0.0, 1.0};
    else if (dir == Direkto::liven)
        loko1 = {-1.0, 0.0};
    else if (dir == Direkto::dextren)
        loko1 = {1.0, 0.0};
    else kraŝu_ĉar("Direkto ne existas.");
    
    struct TraktuValoron
    {
        TraktuValoron(AranghantoKunAnimacioj* a) : aranĝanto(a) {}
        TraktuValoron(const TraktuValoron&) = delete;
        TraktuValoron(TraktuValoron&&) = default;
        TraktuValoron& operator=(const TraktuValoron&) = delete;
        TraktuValoron& operator=(TraktuValoron&&) = default;
        
        ~TraktuValoron()
        {
            for (Aranĝo::Ano& ano : malnovajAnoj)
                if (ano.ĉuWidgetValidas()
                    // povas okazi ke ni jam havas novan aranĝon kiu ja enhavas ĉi-widgeton
                    kaj ne aranĝanto->donuAranĝon().ĉuEnhavas(ano.widget))
                    ano.widget->hide();
        }
        
        Nenio operator()(const QVariant& q)
        {
            Vektor2D<ℚ> loko = q.toPointF();
            
            for (Aranĝo::Ano* ano : novajAnoj)
                traktuAnon(ano, loko);
            for (Aranĝo::Ano& ano : malnovajAnoj)
                traktuAnon(&ano, loko);
            
            malseqŭaLoko = loko;
        }
        
        Nenio traktuAnon(Aranĝo::Ano* ano, Vektor2D<ℚ> novaLoko)
        {
            ano->loko = (ano->loko - malseqŭaLoko) + novaLoko; // ĉi-tiel ni ne akumulas la glitkoman eraron
            // qŭankam la glitkoma eraro verŝajne estus tre malgrandan
            ano->renovuZonon(aranĝanto->grandon());
        }
        
        Listo<Aranĝo::Ano*> novajAnoj;
        Listo<Aranĝo::Ano> malnovajAnoj;
        AranghantoKunAnimacioj* aranĝanto;
        Vektor2D<ℚ> malseqŭaLoko;
    };
    
    TraktuValoron traktuValoron(this);
    traktuValoron.novajAnoj = formovu(novajAnoj);
    traktuValoron.malnovajAnoj.rezervu(malnovajAnoj.grandon());
    
    for (const Aranĝo::Ano* malnovaAno : malnovajAnoj)
        traktuValoron.malnovajAnoj.enmetu(*malnovaAno);
    
    traktuValoron.malseqŭaLoko = {0.0, 0.0};
    
    for (Aranĝo::Ano* novaAno : traktuValoron.novajAnoj)
    {
        novaAno->loko -= loko1;
        novaAno->renovuZonon(grandon());
        if (novaAno->ĉuWidgetValidas())
            novaAno->widget->show();
    }
    
    QVariantAnimation* a = kreuAnimacion(this, loko0, loko1, milisekundoj, kurbo, formovu(traktuValoron));
    connect(a, &QVariantAnimation::destroyed, [this, a]() { traktuKeAnimacioFinis(a); });
    ludantajAnimacioj.enmetu(a);
    a->start(QVariantAnimation::DeleteWhenStopped);
}

QSize AranghantoKunAnimacioj::maximumanGrandon() const
{
    Vektor2D<ℤ> maximumaGrando = aranĝo.determinuMaximumanGrandon();
    eligu {maximumaGrando.x, maximumaGrando.y};
}

QSize AranghantoKunAnimacioj::minimumanGrandon() const
{
    Vektor2D<ℤ> minimumaGrando = aranĝo.determinuMinimumanGrandon();
    eligu {minimumaGrando.x, minimumaGrando.y};
}

Nenio AranghantoKunAnimacioj::resizeEvent(QResizeEvent* okazo)
{
    grando = okazo->size();
    Vektor2D<ℤ> grando = grandon();
    for (Aranĝo::Ano& ano : aranĝo.anoj)
        ano.renovuZonon(grando);
}

Nenio AranghantoKunAnimacioj::traktuKeAnimacioFinis(QVariantAnimation* finitaAnimacio)
{
    for (const QPointer<QVariantAnimation>& animacio : ludantajAnimacioj)
        if (animacio kaj animacio != finitaAnimacio)
            eligu;
    ludantajAnimacioj.malplenigu();
    kiamAnimacioFinas();
}

AranghantoKunAnimacioj::ŜanĝojEnAranĝo AranghantoKunAnimacioj::determinuŜanĝojnEnAranĝo
        (Aranĝo& nova, const Aranĝo& malnova)
{
    using Ano = Aranĝo::Ano;
    
    ŜanĝojEnAranĝo ŝ;
    
    for (Ano& ano : nova.anoj)
    {
        auto paŝanto = malnova.provuTrovi(ano.widget);
        
        if (paŝanto.ĉuValidas())
        {
            ŝ.novajRestantajAnoj.enmetu(&ano);
            ŝ.malnovajRestantajAnoj.enmetu(&*paŝanto);
        }
        else ŝ.novajAnoj.enmetu(&ano);
    }
    
    for (const Ano& ano : malnova.anoj)
        if (ne ŝ.malnovajRestantajAnoj.ĉuEnhavas(&ano))
            ŝ.malnovajAnoj.enmetu(&ano);
    
    eligu formovu(ŝ);
}