#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QScrollArea>
#include "MenuoDeAgordoj.hpp"

MenuoDeAgordoj::MenuoDeAgordoj(QWidget* patro) : QWidget(patro)
{
    rulanto = kreu QScrollArea(this);
    fDosierujoDeTesseract = kreu QLineEdit(rulanto);
    fKlavligoDeKursoro = kreu QLineEdit(rulanto);
    fKlavligoDePoŝo = kreu QLineEdit(rulanto);
    fRetejoDeParsoid = kreu QLineEdit(rulanto);
    fGrandoDeBildo = kreu QLineEdit(rulanto);
    fLinguoDeFasado = kreu QComboBox(rulanto);
    fĈuPreferasUziKopiitajnTextojn = kreu QCheckBox(rulanto);
    lDosierujoDeTesseract = kreu QLabel(rulanto);
    lKlavligoDeKursoro = kreu QLabel(rulanto);
    lKlavligoDePoŝo = kreu QLabel(rulanto);
    lRetejoDeParsoid = kreu QLabel(rulanto);
    lGrandoDeBildo = kreu QLabel(rulanto);
    lCeteraTexto = kreu QLabel(rulanto);
    lEraro = kreu QLabel(rulanto);
    lCeteraTexto->setObjectName("ceteraInformo");
    
    lDosierujoDeTesseract->setWordWrap(veran);
    lKlavligoDeKursoro->setWordWrap(veran);
    lKlavligoDePoŝo->setWordWrap(veran);
    lRetejoDeParsoid->setWordWrap(veran);
    lGrandoDeBildo->setWordWrap(veran);
    lEraro->setWordWrap(veran);
    lCeteraTexto->setWordWrap(veran);
    
    rulanto->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    lEraro->setObjectName("erarlabelo");
    
    QWidget* enhavoDeRulanto = kreu QWidget;
    QVBoxLayout* krado = kreu QVBoxLayout(enhavoDeRulanto);
    krado->setSpacing(3);
    krado->addWidget(fLinguoDeFasado);
    krado->addSpacing(10);
    krado->addWidget(fKlavligoDeKursoro);
    krado->addWidget(lKlavligoDeKursoro);
    krado->addSpacing(10);
    krado->addWidget(fKlavligoDePoŝo);
    krado->addWidget(lKlavligoDePoŝo);
    krado->addWidget(fĈuPreferasUziKopiitajnTextojn);
    krado->addSpacing(10);
    krado->addWidget(fDosierujoDeTesseract);
    krado->addWidget(lDosierujoDeTesseract);
    krado->addSpacing(10);
    krado->addWidget(fRetejoDeParsoid);
    krado->addWidget(lRetejoDeParsoid);
    krado->addSpacing(10);
    krado->addWidget(fGrandoDeBildo);
    krado->addWidget(lGrandoDeBildo);
    krado->addSpacing(15);
    krado->addWidget(lCeteraTexto);
    krado->addStretch();
    rulanto->setWidget(enhavoDeRulanto);
    rulanto->setWidgetResizable(veran);
    
    QVBoxLayout* kernaKrado = kreu QVBoxLayout(this);
    kernaKrado->addWidget(rulanto, 1);
    kernaKrado->addWidget(lEraro);
    
    lEraro->hide();
    
    auto traktuNovanDosierujonDeTesseract = [this]()
    {
        lEraro->hide();
        agorduDosierujonDeTesseract(fDosierujoDeTesseract->text());
    };
    
    auto traktuNovanKlavligonDeKursoro = [this]()
    {
        lEraro->hide();
        agorduKlavligonDeKursoro(fKlavligoDeKursoro->text());
    };
    
    auto traktuNovanKlavligonDePoŝo = [this]()
    {
        lEraro->hide();
        agorduKlavligonDePoŝo(fKlavligoDePoŝo->text());
    };
    
    auto traktuNovanRetejonDeParsoid = [this]()
    {
        lEraro->hide();
        agorduRetejonDeParsoid(fRetejoDeParsoid->text());
    };
    
    auto traktuNovanGrandonDeBildo = [this]()
    {
        lEraro->hide();
        agorduGrandonDeBildo(fGrandoDeBildo->text());
    };
    
    auto traktuNovanLinguonDeFasado = [this]()
    {
        lEraro->hide();
        ℤ i = fLinguoDeFasado->currentIndex();
        if (i != -1)
            agorduLinguonDeFasado(fLinguoDeFasado->itemData(i).toString());
    };
    
    auto traktuNovanĈuPreferasUziKopiitajnTextojn = [this]()
    {
        lEraro->hide();
        agorduĈuPreferasUziKopiitajnTextojn(fĈuPreferasUziKopiitajnTextojn->isChecked());
    };
    
    connect(fDosierujoDeTesseract, &QLineEdit::editingFinished, traktuNovanDosierujonDeTesseract);
    connect(fDosierujoDeTesseract, &QLineEdit::returnPressed, traktuNovanDosierujonDeTesseract);
    connect(fKlavligoDeKursoro, &QLineEdit::editingFinished, traktuNovanKlavligonDeKursoro);
    connect(fKlavligoDeKursoro, &QLineEdit::returnPressed, traktuNovanKlavligonDeKursoro);
    connect(fKlavligoDePoŝo, &QLineEdit::editingFinished, traktuNovanKlavligonDePoŝo);
    connect(fKlavligoDePoŝo, &QLineEdit::returnPressed, traktuNovanKlavligonDePoŝo);
    connect(fRetejoDeParsoid, &QLineEdit::editingFinished, traktuNovanRetejonDeParsoid);
    connect(fRetejoDeParsoid, &QLineEdit::returnPressed, traktuNovanRetejonDeParsoid);
    connect(fGrandoDeBildo, &QLineEdit::editingFinished, traktuNovanGrandonDeBildo);
    connect(fGrandoDeBildo, &QLineEdit::returnPressed, traktuNovanGrandonDeBildo);
    connect(fLinguoDeFasado, &QComboBox::currentTextChanged, traktuNovanLinguonDeFasado);
    connect(fĈuPreferasUziKopiitajnTextojn, &QCheckBox::stateChanged, traktuNovanĈuPreferasUziKopiitajnTextojn);
    
    preparuTextojn();
}

Nenio MenuoDeAgordoj::agorduElekteblajnLinguojn(const Listo<Texto>& elekteblajLinguoj)
{
    fLinguoDeFasado->clear();
    
    for (const Texto& tLinguo : elekteblajLinguoj)
    {
        Linguo linguo(tLinguo);
        Texto nomoDeLinguo = linguo.ĉuNiKonasLinguon() ? linguo.donuNomon(linguo) : linguo.iso639_3;
        fLinguoDeFasado->addItem(nomoDeLinguo.QT(), linguo.iso639_3.QT());
    }
}

Nenio MenuoDeAgordoj::agorduDosierujonDeTesseract(const Texto& novaDosierujo)
{
    if (novaDosierujo == dosierujoDeTesseract)
        eligu;
    
    std::exception_ptr eraro;
    kiamShanghasDosierujonDeTesseract(novaDosierujo, &eraro);
    
    if (eraro)
    {
        metuEraronEnProtokolo(eraro);
        std::exception_ptr eraro2;
        kiamShanghasDosierujonDeTesseract(dosierujoDeTesseract, &eraro2);
    }
    else dosierujoDeTesseract = novaDosierujo;
    
    if (ne fDosierujoDeTesseract->isActiveWindow())
        fDosierujoDeTesseract->setText(dosierujoDeTesseract.QT());
}

Nenio MenuoDeAgordoj::agorduKlavligonDeKursoro(const Texto& novaKlavligo)
{
    if (novaKlavligo == klavligoDeKursoro)
        eligu;
    
    std::exception_ptr eraro;
    kiamShanghasKlavligonDeKursoro(novaKlavligo, &eraro);
    
    if (eraro)
    {
        metuEraronEnProtokolo(eraro);
        std::exception_ptr eraro2;
        kiamShanghasKlavligonDeKursoro(klavligoDeKursoro, &eraro2);
    }
    else klavligoDeKursoro = novaKlavligo;
    
    if (ne fKlavligoDeKursoro->isActiveWindow())
        fKlavligoDeKursoro->setText(klavligoDeKursoro.QT());
}

Nenio MenuoDeAgordoj::agorduKlavligonDePoŝo(const Texto& novaKlavligo)
{
    if (novaKlavligo == klavligoDePoŝo)
        eligu;
    
    std::exception_ptr eraro;
    kiamShanghasKlavligonDePosho(novaKlavligo, &eraro);
    
    if (eraro)
    {
        metuEraronEnProtokolo(eraro);
        std::exception_ptr eraro2;
        kiamShanghasKlavligonDePosho(klavligoDePoŝo, &eraro2);
    }
    else klavligoDePoŝo = novaKlavligo;
    
    if (ne fKlavligoDePoŝo->isActiveWindow())
        fKlavligoDePoŝo->setText(klavligoDePoŝo.QT());
}

Nenio MenuoDeAgordoj::agorduRetejonDeParsoid(const Texto& novaRetejo)
{
    if (novaRetejo == retejoDeParsoid)
        eligu;
    
    std::exception_ptr eraro;
    kiamShanghasRetejonDeParsoid(novaRetejo, &eraro);
    
    if (eraro)
    {
        metuEraronEnProtokolo(eraro);
        std::exception_ptr eraro2;
        kiamShanghasRetejonDeParsoid(retejoDeParsoid, &eraro2);
    }
    else retejoDeParsoid = novaRetejo;
    
    if (ne fRetejoDeParsoid->isActiveWindow())
        fRetejoDeParsoid->setText(retejoDeParsoid.QT());
}

Nenio MenuoDeAgordoj::agorduGrandonDeBildo(const Texto& novaGrando)
{
    if (novaGrando == grandoDeBildo)
        eligu;
    
    std::exception_ptr eraro;
    kiamShanghasGrandonDeBildo(novaGrando, &eraro);
    
    if (eraro)
    {
        metuEraronEnProtokolo(eraro);
        std::exception_ptr eraro2;
        kiamShanghasGrandonDeBildo(grandoDeBildo, &eraro2);
    }
    else grandoDeBildo = novaGrando;
    
    if (ne fGrandoDeBildo->isActiveWindow())
        fGrandoDeBildo->setText(grandoDeBildo.QT());
}

Nenio MenuoDeAgordoj::agorduLinguonDeFasado(const Texto& novaLinguo)
{
    if (novaLinguo == linguoDeFasado.iso639_3)
        eligu;
    Linguo _novaLinguo(novaLinguo);
    
    std::exception_ptr eraro;
    kiamShanghasLinguonDeFasado(_novaLinguo, &eraro);
    
    if (eraro)
    {
        metuEraronEnProtokolo(eraro);
        std::exception_ptr eraro2;
        kiamShanghasLinguonDeFasado(_novaLinguo, &eraro2);
    }
    else
    {
        linguoDeFasado = _novaLinguo;
    
        ℤ i = fLinguoDeFasado->currentIndex();
        if (i == -1 aŭ fLinguoDeFasado->itemData(i).toString() != linguoDeFasado.iso639_3.QT())
            for (ℕ i = 0; i < fLinguoDeFasado->count(); i++)
                if (fLinguoDeFasado->itemData(i).toString() == linguoDeFasado.iso639_3.QT())
                    fLinguoDeFasado->setCurrentIndex(i);
    }
}

Nenio MenuoDeAgordoj::agorduĈuPreferasUziKopiitajnTextojn(Buleo novaValoro)
{
    if (novaValoro == ĉuPreferasUziKopiitajnTextojn)
        eligu;
    kiamShanghasChuPreferasUziKopiitajnTextojn(novaValoro);
    ĉuPreferasUziKopiitajnTextojn = novaValoro;
}

Nenio MenuoDeAgordoj::preparuTextojn()
{
    lDosierujoDeTesseract->setText(tr("La dosierujo kiu enhavas la datumdosierojn de Tesseract, "
                                      "kiujn ni bezonas por rekoni literojn."));
    lKlavligoDeKursoro->setText(tr("Kiam vi premas ĉi-klavligon, la programo provas "
                                   "doni la difinojn de la worto sub la kursoro."));
    lKlavligoDePoŝo->setText(tr("Kiam vi premas ĉi-klavligon, la programo donas la difinojn de iu kopiita worto."));
    lRetejoDeParsoid->setText(tr("La ret-adreso de la Parsoid servilo, kiu ŝanĝas Wikitext al HTML. "
                                 "Se ĉi-agordo estas malplenan aŭ malĝustan te ni montras la Wikitexton."));
    lGrandoDeBildo->setText(tr("La grando de la ekranbildoj. Legi grandorajn bildojn daŭras longore."));
    fĈuPreferasUziKopiitajnTextojn->setText(tr("Ĉu oni devas uzi kopiitajn textojn anstataŭ "
                                               "elektitaj textoj."));
    lCeteraTexto->setText(tr("© 2018 Zowie van Dillen\n"
                             "uzas «gears» kaj «language» piktogramojn de Milky"));
}

Nenio MenuoDeAgordoj::metuEraronEnProtokolo(std::exception_ptr& eraro)
{
    try
    {
        std::rethrow_exception(eraro);
    }
    catch (const std::exception& e)
    {
        lEraro->setText(e.what());
        lEraro->show();
        std::cerr << e.what() << std::endl;
    }
    catch (...)
    {
        lEraro->setText(tr("Io fiaskis."));
        lEraro->show();
        std::cerr << "Nerekonata eraro." << std::endl;
    }
}