#include "Difinujo.hpp"
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QVBoxLayout>

Difinujo::Difinujo(QWidget* patro) : QWidget(patro), ĉuĴusBezonisPliDifinojn(malveran), ĉuTorentoDeDifinojFinis(veran)
{
    paĝo = kreu QTextBrowser(this);
    paĝo->setObjectName("paĝo");
    paĝo->setFrameShape(QFrame::NoFrame);
    paĝo->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    paĝo->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    paĝo->setUndoRedoEnabled(malveran);
    paĝo->setOpenLinks(malveran);
    paĝo->document()->setDefaultStyleSheet("ol { margin: 0px; } p { margin: 0px; } "
                                           ".difino { margin-bottom: 6px; } a { color: black; } "
                                           ".kapo { background-color: #fafafa; padding-left: 10px; } "
                                           ".fino { color: #999; } ");
    
    QVBoxLayout* krado = kreu QVBoxLayout(this);
    krado->setSpacing(0);
    krado->setContentsMargins(0, 0, 0, 0);
    krado->addWidget(paĝo);
    
    preparuTextojn();
    //-«
    connect(paĝo, SIGNAL(anchorClicked(const QUrl&)), this, SLOT(traktuLigilon(const QUrl&))); //»-
    connect(paĝo->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(elsenduChuBezonasPliDifinojn()));
}

Buleo Difinujo::provuAgordiTransliteranton(const Texto& nomo)
{
#ifdef ĈU_UZAS_ICU_UNICODE
    UErrorCode eraro = UErrorCode::U_ZERO_ERROR;
    
    PropraAdres<Transliterator> novaTransliteranto
            (Transliterator::createInstance(nomo.ICU(), UTransDirection::UTRANS_FORWARD, eraro));
    
    if (U_FAILURE(eraro))
    {
        std::cerr << "Krei transliteranton «" << nomo.STL() << "» malsukcesis: "
                  << std::string(u_errorName(eraro)) << std::endl;
        eligu malveran;
    }
    
    transliteranto = formovu(novaTransliteranto);
#endif
    eligu veran;
}

Nenio Difinujo::komencuTorentonDeDifinoj()
{
    difinoj.malplenigu();
    ĉuTorentoDeDifinojFinis = malveran;
    rekreuPaĝonKajIruAlKomencoDePaĝo();
}

Nenio Difinujo::enmetuDifinon(Difino difino)
{
    difinoj.enmetu(difino);
    rekreuPaĝonKajRestuEnLaSamaLoko();
    elsenduChuBezonasPliDifinojn();
}

Nenio Difinujo::finuTorentonDeDifinoj()
{
    ĉuTorentoDeDifinojFinis = veran;
    rekreuPaĝonKajRestuEnLaSamaLoko();
}

Nenio Difinujo::elsenduChuBezonasPliDifinojn()
{
    Buleo _ĉuBezonasPliDifinojn = ĉuBezonasPliDifinojn();
    if (_ĉuBezonasPliDifinojn kaj ne ĉuĴusBezonisPliDifinojn)
        kiamBezonasPliDifinojn();
    if (ne _ĉuBezonasPliDifinojn kaj ĉuĴusBezonisPliDifinojn)
        kiamNeBezonasPliDifinojn();
    ĉuĴusBezonisPliDifinojn = _ĉuBezonasPliDifinojn;
}

Nenio Difinujo::traktuLigilon(const QUrl& nomo)
{
    kiamUzantoKlakasAlLigilo(nomo.toString());
}

Nenio Difinujo::preparuTextojn()
{
    texto_ŝarĝante = tr("Ŝarĝante...");
    texto_ne_trovis_difinojn = tr("Oni ne trovis iun-ajn difinon.");
    rekreuPaĝonKajRestuEnLaSamaLoko();
}

Buleo Difinujo::ĉuBezonasPliDifinojn() const
{
    ℤ restantaSpaco = paĝo->verticalScrollBar()->maximum() - paĝo->verticalScrollBar()->value();
    eligu restantaSpaco < paĝo->height() + 1000; // «1000» estas arbitran
}

Nenio Difinujo::rekreuPaĝonKajIruAlKomencoDePaĝo()
{
    rekreuPaĝon();
    paĝo->verticalScrollBar()->setValue(0);
}

Nenio Difinujo::rekreuPaĝonKajRestuEnLaSamaLoko()
{
    ℤ y = paĝo->verticalScrollBar()->value();
    rekreuPaĝon();
    paĝo->verticalScrollBar()->setValue(y);
}

Nenio Difinujo::rekreuPaĝon()
{
    QString html = "";
    
    for (const Difino& difino : difinoj)
    {
        html += "<div class=\"dif\"><div class=\"kapo\">" + difino.linguo.iso639_3.QT()
                + " <b>" + difino.worto.QT() + "</b>";
        
#ifdef ĈU_UZAS_ICU_UNICODE
        if (transliteranto)
        {
            UnicodeString transliteritaWorto = difino.worto.ICU();
            transliteranto->transliterate(transliteritaWorto);
            if (transliteritaWorto != difino.worto.ICU())
                html += "  <i>" + Texto(transliteritaWorto).QT() + "</i>";
        }
#endif
        
        html += "</div><div>" + difino.htmlDifino.QT() + "</div></div>";
    }
    
    if (ne ĉuTorentoDeDifinojFinis)
        html += "<center><div class=\"fino\">" + texto_ŝarĝante + "</div></center>";
    else if (difinoj.ĉuEstasMalplenan())
        html += "<center><div class=\"fino\">" + texto_ne_trovis_difinojn + "</div></center>";
    
    paĝo->setHtml(html);
}