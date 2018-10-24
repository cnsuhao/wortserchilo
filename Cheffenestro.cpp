#include <iostream>
#include <filesystem>
#include <QtCore/QCoreApplication>
#include "Cheffenestro.hpp"
#include "komuna/alTexto.hpp"
#include "Ekranbildo.hpp"
#include "komuna/cet/Glitkomo.hpp"

Cheffenestro::Cheffenestro() : bildlarĝo(400), bildalto(100)
{
    aranĝanto = kreu AranĝantoKunAnimacioj(this);
    aranĝantoDeBildleganto = kreu AranĝantoKunAnimacioj(aranĝanto);
    
    butonoDeLinguoj = kreu QPushButton(aranĝanto);
    butonoDeAgordoj = kreu QPushButton(aranĝanto);
    tajpejo = kreu QLineEdit(aranĝanto);
    difinujo = kreu Difinujo(aranĝanto);
    wortaresLinguoj = kreu MenuoDeWortaresLinguoj(aranĝanto);
    bildlegantesLinguoj = kreu MenuoDeBildlegantesLinguoj(aranĝanto);
    menuoDeAgordoj = kreu MenuoDeAgordoj(aranĝanto);
    QWidget* ujoDeTajpejo = kreu QWidget(aranĝanto);
    
    nigraKolorlisto = kreu Kolorlisto(aranĝantoDeBildleganto);
    blankaKolorlisto = kreu Kolorlisto(aranĝantoDeBildleganto);
    kolorelektejo = kreu Kolorelektejo(aranĝantoDeBildleganto);
    desegnejo = kreu BinaraDesegnejo(aranĝantoDeBildleganto);
    rezultujo = kreu Rezultujo(aranĝantoDeBildleganto);
    
    butonoDeLinguoj->setObjectName("butonoDeLinguoj");
    butonoDeAgordoj->setObjectName("butonoDeAgordoj");
    tajpejo->setObjectName("tajpejo");
    nigraKolorlisto->setObjectName("nigraKolorlisto");
    blankaKolorlisto->setObjectName("blankaKolorlisto");
    kolorelektejo->setObjectName("kolorelektejo");
    desegnejo->setObjectName("desegnejo");
    rezultujo->setObjectName("rezultujo");
    difinujo->setObjectName("difinujo");
    wortaresLinguoj->setObjectName("wortaresLinguoj");
    bildlegantesLinguoj->setObjectName("bildlegantesLinguoj");
    menuoDeAgordoj->setObjectName("menuoDeAgordoj");
    ujoDeTajpejo->setObjectName("ujoDeTajpejo");
    tajpejo->setObjectName("tajpejo");
    
    butonoDeAgordoj->setProperty("aktiva", malveran);
    butonoDeLinguoj->setProperty("aktiva", malveran);
    nigraKolorlisto->agorduFlankkoloron(QColor(91, 91, 91));
    blankaKolorlisto->agorduFlankkoloron(QColor(244, 244, 244));
    
    QHBoxLayout* qAranĝoDeUjoDeTajpejo = kreu QHBoxLayout(ujoDeTajpejo);
    qAranĝoDeUjoDeTajpejo->setSpacing(0);
    qAranĝoDeUjoDeTajpejo->setMargin(0);
    qAranĝoDeUjoDeTajpejo->addWidget(butonoDeLinguoj);
    qAranĝoDeUjoDeTajpejo->addWidget(tajpejo);
    qAranĝoDeUjoDeTajpejo->addWidget(butonoDeAgordoj);
    
    ujoDeTajpejo->hide();
    aranĝantoDeBildleganto->hide();
    nigraKolorlisto->hide();
    blankaKolorlisto->hide();
    kolorelektejo->hide();
    desegnejo->hide();
    rezultujo->hide();
    difinujo->hide();
    wortaresLinguoj->hide();
    bildlegantesLinguoj->hide();
    menuoDeAgordoj->hide();
    
    Vektor2D<ℚ> l(0, 0); // loko
    Vektor2D<ℚ> g(1, 1); // grando
    Vektor2D<ℤ> d1(0, 0); // deiĝo supra
    Vektor2D<ℤ> d2(0, 30); // deiĝo suba
    Vektor2D<ℤ> dg(0, -30); // deiĝo de grando
    Aranĝo::Ano tajpejoSupra = {ujoDeTajpejo, 0, 0, 1, 0, 0, 0, 0, 30};
    Aranĝo::Ano tajpejoSuba = {ujoDeTajpejo, 0, 1, 1, 0, 0, -30, 0, 30};
    
    aranĝoj[Paĝo::bildlegantes_linguoj] = {tajpejoSuba, {bildlegantesLinguoj, l, g, d1, dg}};
    aranĝoj[Paĝo::bildleganto] = {tajpejoSuba, {aranĝantoDeBildleganto, l, g, d1, dg}};
    aranĝoj[Paĝo::agordoj_supraj] = {tajpejoSuba, {menuoDeAgordoj, l, g, d1, dg}};
    aranĝoj[Paĝo::wortares_linguoj] = {tajpejoSupra, {wortaresLinguoj, l, g, d2, dg}};
    aranĝoj[Paĝo::difinoj] = {tajpejoSupra, {difinujo, l, g, d2, dg}};
    aranĝoj[Paĝo::agordoj_subaj] = {tajpejoSupra, {menuoDeAgordoj, l, g, d2, dg}};
    
    rekreuInternanAranghonDeBildleganto();
    preparuTextojn();
    resize(400, 400);
    setMinimumSize(400, 400);
    setMaximumWidth(400);
    
    setCentralWidget(aranĝanto);
    
    aranĝanto->agorduAranĝonSenAnimacio(aranĝoj[Paĝo::agordoj_subaj]);
    aktivaPaĝo = Paĝo::agordoj_subaj;
    prokrastitaPaĝo = Paĝo::neniu_paĝo;
    
    tajpejo->installEventFilter(this);
    
    connect(aranĝanto, &AranĝantoKunAnimacioj::kiamAnimacioFinas, [this]()
    { 
        if (prokrastitaPaĝo == Paĝo::neniu_paĝo aŭ aranĝanto->ĉuLudasAnimacion())
            eligu;
        Paĝo paĝo = prokrastitaPaĝo;
        prokrastitaPaĝo = Paĝo::neniu_paĝo;
        iruAlPaĝo(paĝo);
    });
    connect(difinujo, SIGNAL(kiamUzantoKlakasAlLigilo(Texto)), this, SLOT(traktuKlakonAlLigilo(Texto)));
    connect(tajpejo, SIGNAL(editingFinished()), this, SLOT(traktuShanghitanTajplinion()));//-«
    connect(tajpejo, &QLineEdit::returnPressed, [this] { iruAlPaĝo(Paĝo::difinoj); traktuShanghitanTajplinion(); });//»-
    
    connect(rezultujo, &Rezultujo::kiamUzantoKlakasAlWorto, //-«
            [this](const LegitaWorto& worto) { iruAlPaĝo(Paĝo::difinoj); shanghuWortonAl(worto); }); //»-
    connect(rezultujo, &Rezultujo::kiamKursoroShwebasSuper, this, &Cheffenestro::shanghuEmfazatanWortonAl);
    connect(rezultujo, &Rezultujo::kiamKursoroNeShwebasSuperIoAjn,
            [this]() { shanghuEmfazatanWortonAl(LegitaWorto()); });
    
    connect(kolorelektejo, SIGNAL(kiamOniShanghasCentranLokon(Vektor2D<ℤ>)),
            desegnejo, SLOT(agorduCentranLokon(Vektor2D<ℤ>)));
    connect(kolorelektejo, SIGNAL(kiamOniShanghasZomfaktoron(int)),
            desegnejo, SLOT(agorduZomfaktoron(int)));
    connect(kolorelektejo, &Kolorelektejo::kiamUzantoLiveKlakasAlKoloro, this, &Cheffenestro::enmetuNigranKoloron);
    connect(kolorelektejo, &Kolorelektejo::kiamUzantoDextreKlakasAlKoloro, this, &Cheffenestro::enmetuBlankanKoloron);
    
    auto forprenuKoloron = [this](const QColor& koloro)
    {
        kolorfiltrilo.forprenuKoloron(koloro);
        nigraKolorlisto->forprenuKoloron(koloro);
        blankaKolorlisto->forprenuKoloron(koloro);
        traktuNovanKoloranBildon();
    };
    
    connect(nigraKolorlisto, &Kolorlisto::kiamUzantoKlakasAlKoloro, forprenuKoloron);
    connect(blankaKolorlisto, &Kolorlisto::kiamUzantoKlakasAlKoloro, forprenuKoloron);
    connect(nigraKolorlisto, &Kolorlisto::kiamIghasMalplenan,
            this, &Ĉeffenestro::rekreuInternanAranghonDeBildleganto);
    connect(nigraKolorlisto, &Kolorlisto::kiamIghasNePluMalplenan,
            this, &Ĉeffenestro::rekreuInternanAranghonDeBildleganto);
    connect(blankaKolorlisto, &Kolorlisto::kiamIghasMalplenan,
            this, &Ĉeffenestro::rekreuInternanAranghonDeBildleganto);
    connect(blankaKolorlisto, &Kolorlisto::kiamIghasNePluMalplenan,
            this, &Ĉeffenestro::rekreuInternanAranghonDeBildleganto);
    
    connect(desegnejo, SIGNAL(kiamOniShanghasCentranLokon(Vektor2D<ℤ>)),
            kolorelektejo, SLOT(agorduCentranLokon(Vektor2D<ℤ>)));
    connect(desegnejo, SIGNAL(kiamOniShanghasZomfaktoron(int)),
            kolorelektejo, SLOT(agorduZomfaktoron(int)));
    
    connect(desegnejo, &BinaraDesegnejo::kiamUzantoFinisDesegniIon, [this]()
    {
        desegnejo->konservuBildon(blanknigra_bildo);
        kiamVolasTextonEnBildo(blanknigra_bildo);
    });
    
    connect(bildlegantesLinguoj, &MenuoDeBildlegantesLinguoj::kiamOniElektisNovajnLinguojnPorBildleganto,
            [this]() { ĉuOniElektisNovajnLinguojnDeBildleganto = veran; });
    connect(wortaresLinguoj, &MenuoDeWortaresLinguoj::kiamOniElektisNovanWortaron,
            [this]() { ĉuOniElektisNovajnWortarojn = veran; });
    connect(wortaresLinguoj, &MenuoDeWortaresLinguoj::kiamOniMalelektisWortaron,
            [this]() { ĉuOniElektisNovajnWortarojn = veran; });
    
    connect(butonoDeLinguoj, &QPushButton::pressed, [this]()
    {
        if (aktivaPaĝo == Paĝo::bildlegantes_linguoj)
            iruAlPaĝo(Paĝo::bildleganto);
        else if (aktivaPaĝo == Paĝo::wortares_linguoj)
            iruAlPaĝo(Paĝo::difinoj);
        else if (ĉuPaĝoEstasEnSubaDuono(aktivaPaĝo))
            iruAlPaĝo(Paĝo::wortares_linguoj);
        else iruAlPaĝo(Paĝo::bildlegantes_linguoj);
    });
    
    connect(butonoDeAgordoj, &QPushButton::pressed, [this]()
    {
        if (aktivaPaĝo == Paĝo::agordoj_supraj)
            iruAlPaĝo(Paĝo::bildleganto);
        else if (aktivaPaĝo == Paĝo::agordoj_subaj)
            iruAlPaĝo(Paĝo::difinoj);
        else if (ĉuPaĝoEstasEnSubaDuono(aktivaPaĝo))
            iruAlPaĝo(Paĝo::agordoj_subaj);
        else iruAlPaĝo(Paĝo::agordoj_supraj);
    });
}

Nenio Cheffenestro::traktuŜanĝitajnLinguajnAgordojn()
{
    if (ĉuOniElektisNovajnWortarojn)
    {
        ĉuOniElektisNovajnWortarojn = malveran;
        kiamOniShanghasElektitajnWortarojn(wortaresLinguoj->donuElektitajnWortarojn());
    }
    
    if (ĉuOniElektisNovajnLinguojnDeBildleganto)
    {
        ĉuOniElektisNovajnLinguojnDeBildleganto = malveran;
        kiamOniShanghasElektitajnLinguojnDeBildleganto(bildlegantesLinguoj->donuElektitajnLinguojnPorBildleganto());
    }
}

Nenio Cheffenestro::reŝarĝuKoloranBildon()
{
    kolorelektejo->ŝarĝuBildon(kolora_bildo);
    traktuNovanKoloranBildon();
}

Nenio Cheffenestro::montruDifinojnDeWorto(const Texto& worto)
{
    if (worto != nomoDeWorto)
        ŝanĝuWortonAl(worto);
    tajpejo->setText(worto.QT());
    iruAlPaĝo(Paĝo::difinoj);
}

Nenio Cheffenestro::iruAlPaĝo(Paĝo paĝo)
{
    if (aranĝanto->ĉuLudasAnimacion())
        prokrastitaPaĝo = paĝo;
    else if (ĉuPaĝoEstasEnSubaDuono(paĝo) kaj ne ĉuPaĝoEstasEnSubaDuono(aktivaPaĝo))
        iruAlPaĝo(paĝo, Direkto::supren);
    else if (ne ĉuPaĝoEstasEnSubaDuono(paĝo) kaj ĉuPaĝoEstasEnSubaDuono(aktivaPaĝo))
        iruAlPaĝo(paĝo, Direkto::suben);
    else if (aktivaPaĝo == Paĝo::wortares_linguoj aŭ aktivaPaĝo == Paĝo::bildlegantes_linguoj)
        iruAlPaĝo(paĝo, Direkto::liven);
    else if (paĝo == Paĝo::agordoj_subaj aŭ paĝo == Paĝo::agordoj_supraj)
        iruAlPaĝo(paĝo, Direkto::liven);
    else iruAlPaĝo(paĝo, Direkto::dextren);
}

Nenio Cheffenestro::iruAlPaĝo(Paĝo paĝo, Direkto direkto)
{
    premisu (aranĝoj.ĉuEnhavas(paĝo));
    
    if (paĝo == aktivaPaĝo)
        eligu;
    
    aranĝanto->agorduAranĝonRulante(aranĝoj[paĝo], direkto, 300, QEasingCurve::InOutQuad);
    aktivaPaĝo = paĝo;
    
    tempojDeRuloj.clear();
    butonoDeLinguoj->setProperty("aktiva", aktivaPaĝo == Paĝo::bildlegantes_linguoj
                                           aŭ aktivaPaĝo == Paĝo::wortares_linguoj);
    butonoDeAgordoj->setProperty("aktiva", aktivaPaĝo == Paĝo::agordoj_supraj aŭ aktivaPaĝo == Paĝo::agordoj_subaj);
    traktuŜanĝitajnLinguajnAgordojn();
}

Buleo Cheffenestro::ĉuPaĝoEstasEnSubaDuono(Cheffenestro::Paĝo paĝo)
{
    static const Listo<Paĝo> paĝoj_en_suba_duono = {Paĝo::wortares_linguoj, Paĝo::difinoj, Paĝo::agordoj_subaj};
    eligu paĝoj_en_suba_duono.ĉuEnhavas(paĝo);
}

Nenio Cheffenestro::traktuRezultonDeLegado(RezultoDeLegado rezulto)
{
    // ĉi-tio ne ĝustas se la bildo estas ĉe la flanko de la ekrano, sed mi estas tro pigran por ĝuste fari ĝin
    Vektor2D<ℤ> mezpunkto(bildlarĝo / 2, bildalto / 2);
    Paro<ℕ, ℕ> proximimaWorto = trovuWortonProximimanAl(mezpunkto, rezulto);
    
    rezultujo->agorduWortojn(rezulto, proximimaWorto.first, proximimaWorto.second);
    if (ne rezulto.frazaroj.ĉuEstasMalplenan())
        shanghuWortonAl(rezulto.frazaroj[proximimaWorto.first].wortoj[proximimaWorto.second]);
}

Nenio Cheffenestro::enmetuNigranKoloron(const QColor& koloro)
{
    kolorfiltrilo.enmetuNigranKoloron(koloro);
    nigraKolorlisto->enmetuKoloron(koloro);
    traktuNovanKoloranBildon();
}

Nenio Cheffenestro::enmetuBlankanKoloron(const QColor& koloro)
{
    kolorfiltrilo.enmetuBlankanKoloron(koloro);
    blankaKolorlisto->enmetuKoloron(koloro);
    traktuNovanKoloranBildon();
}

Nenio Cheffenestro::traktuShanghitanTajplinion()
{
    Texto novaWorto = tajpejo->text();
    tajpejo->clearFocus();
    if (novaWorto == nomoDeWorto)
        eligu;
    ŝanĝuWortonAl(novaWorto);
}

Nenio Cheffenestro::traktuKlakonAlLigilo(Texto ligilo)
{
    for (Texto::Ano& karaktero : ligilo)
        if (karaktero == '_')
            karaktero = ' ';
    
    tajpejo->setText(ligilo.QT());
    ŝanĝuWortonAl(ligilo);
}

Nenio Cheffenestro::shanghuWortonAl(LegitaWorto worto)
{
    desegnejo->forprenuEmfazon(elektitaWorto.zono);
    elektitaWorto = worto;
    desegnejo->enmetuEmfazon(elektitaWorto.zono);
    Texto texto = worto.texton();
    tajpejo->setText(texto.QT());
    if (nomoDeWorto != texto)
        ŝanĝuWortonAl(texto);
}

Nenio Cheffenestro::shanghuEmfazatanWortonAl(LegitaWorto worto)
{
    desegnejo->forprenuEmfazon(emfazataWorto.zono);
    emfazataWorto = worto;
    desegnejo->enmetuEmfazon(emfazataWorto.zono);
}

Nenio Cheffenestro::rekreuInternanAranghonDeBildleganto()
{
    static constexpr ℕ a_kl = 20; // alto de kolorlisto
    ℕ y = 0;
    Aranĝo aranĝo;
    ℕ alto_de_bildes_fenestranoj = std::min<ℕ>(100, std::max<ℕ>(bildalto, height() / 5));
    
    if (ne nigraKolorlisto->ĉuEstasMalplenan())
    {
        aranĝo.anoj.enmetuNovan(nigraKolorlisto, 0, 0, 1, 0, 0, y, 0, a_kl);
        y += a_kl;
    }
    else aranĝo.anoj.enmetuNovan(nigraKolorlisto, 0, 0, 1, 0, 0, y, 0, 0);
    
    if (ne blankaKolorlisto->ĉuEstasMalplenan())
    {
        aranĝo.anoj.enmetuNovan(blankaKolorlisto, 0, 0, 1, 0, 0, y, 0, a_kl);
        y += a_kl;
    }
    else aranĝo.anoj.enmetuNovan(blankaKolorlisto, 0, 0, 1, 0, 0, y, 0, 0);
    
    aranĝo.anoj.enmetuNovan(kolorelektejo, 0, 0, 1, 0, 0, y, 0, alto_de_bildes_fenestranoj);
    y += alto_de_bildes_fenestranoj;
    aranĝo.anoj.enmetuNovan(desegnejo, 0, 0, 1, 0, 0, y, 0, alto_de_bildes_fenestranoj);
    y += alto_de_bildes_fenestranoj;
    aranĝo.anoj.enmetuNovan(rezultujo, 0, 0, 1, 1, 0, y, 0, -y);
    
    aranĝantoDeBildleganto->agorduAranĝonRulante(aranĝo, Direkto::supren, 200);
}

Nenio Cheffenestro::wheelEvent(QWheelEvent* okazo)
{
    using namespace std::chrono;
    static constexpr ℕ minimuma_nombro_da_okazoj = 5;
    static const system_clock::duration maximuma_daŭro = 500ms;
    
    Buleo ĉuRulisSuben = okazo->delta() < 0;
    
    if (ĉuRulisSuben == ĉuPaĝoEstasEnSubaDuono(aktivaPaĝo))
        tempojDeRuloj.clear();
    else
    {
        system_clock::time_point tempo = system_clock::now();
        
        if (tempojDeRuloj.size() >= minimuma_nombro_da_okazoj)
        {
            if (tempo - tempojDeRuloj.front() < maximuma_daŭro)
            {
                if (aktivaPaĝo == Paĝo::wortares_linguoj)
                    iruAlPaĝo(Paĝo::bildlegantes_linguoj);
                else if (aktivaPaĝo == Paĝo::bildlegantes_linguoj)
                    iruAlPaĝo(Paĝo::wortares_linguoj);
                else if (ĉuRulisSuben)
                    iruAlPaĝo(Paĝo::difinoj);
                else iruAlPaĝo(Paĝo::bildleganto);
                
                tempojDeRuloj.clear();
            }
            else
            {
                tempojDeRuloj.pop_front();
                tempojDeRuloj.push_back(tempo);
            }
        }
        else tempojDeRuloj.push_back(tempo);
    }
}

Nenio Cheffenestro::preparuTextojn()
{
    setWindowTitle(tr("Wortserĉilo"));
    tajpejo->setPlaceholderText(tr("skribu ĉi-tie"));
}

Nenio Cheffenestro::ŝanĝuWortonAl(Texto novaWorto)
{
    auto provuElpreniLinguon = [](Texto texto) -> Linguo // eble_todo movu alien
    {
        texto = texto.minuskligitan();
        
        if (texto == "english")
            eligu angla_linguo;
        if (texto == "esperanto")
            eligu esperanta_linguo;
        if (Linguo(texto).ĉuNiKonasLinguon())
            eligu Linguo(texto);
        eligu neniu_linguo;
    };
    
    auto ĉuEgalas = [](const Paro<Texto, Linguo>& a, const Linguo& b) { eligu a.second == b; };
    
    if (aktivaPaĝo != Paĝo::bildleganto)
        iruAlPaĝo(Paĝo::difinoj);
    
    novaWorto.forprenuEksteranBlankanSpacon();
    if (novaWorto.ĉuEstasMalplenan())
        eligu;
    
    kiamNePluVolasDifinojn();
    nomoDeWorto = novaWorto;
    Texto::Paŝanto paŝanto = nomoDeWorto.provuTrovi('#');
    
    if (ne paŝanto.ĉuValidas())
        kiamVolasDifinojnDe(nomoDeWorto, malveran);
    else
    {
        Texto partoPostKrado = nomoDeWorto.donuPartonInter(paŝanto.donuLokon() + 1, nomoDeWorto.grandon());
        Linguo linguo = provuElpreniLinguon(partoPostKrado);
        Texto worto = nomoDeWorto.donuPartonInter(0, paŝanto.donuLokon());
        if (linguo == neniu_linguo aŭ ne wortaresLinguoj->donuElektitajnWortarojn().ĉuEnhavas(linguo, ĉuEgalas))
            kiamVolasDifinojnDe(worto, malveran); // todo averto por «ne linguoj.ĉuEnhavas(linguo)»
        else
            kiamVolasDifinojnDe(worto, malveran, linguo);
    }
}

Nenio Cheffenestro::traktuNovanKoloranBildon()
{
    if (kolorfiltrilo.ĉuEnhavasKolorojn())
        kolorfiltrilo.kreuBlanknigranBildon(kolora_bildo, blanknigra_bildo);
    else kiamBezonasBlanknigranVersionDeBildo(kolora_bildo, blanknigra_bildo);
    
    desegnejo->ŝarĝuBildon(blanknigra_bildo);
    kiamVolasTextonEnBildo(blanknigra_bildo);
}
