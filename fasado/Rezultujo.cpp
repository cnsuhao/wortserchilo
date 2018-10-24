#include "Rezultujo.hpp"
#include "../komuna/alTexto.hpp"

Rezultujo::Rezultujo(QWidget* patro) : QWidget(patro)
{
    paĝo = kreu QTextBrowser(this);
    paĝo->setObjectName("paĝo");
    paĝo->setFrameShape(QFrame::NoFrame);
    paĝo->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    paĝo->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    paĝo->setUndoRedoEnabled(malveran);
    paĝo->setOpenLinks(malveran);
    paĝo->setAlignment(Qt::AlignCenter);
    paĝo->document()->setDefaultStyleSheet(
            ".worto a { color: #252525; text-decoration: none; }"
            ".malcerta { color: #7a7a7a; }"
            //".malcerta { background-color: #555555; color: #ffffff; }"
            );
    
    QVBoxLayout* krado = kreu QVBoxLayout(this);
    krado->setSpacing(0);
    krado->setContentsMargins(0, 0, 0, 0);
    krado->addWidget(paĝo);
    
    connect(paĝo, SIGNAL(anchorClicked(const QUrl&)), this, SLOT(traktuKeUzantoKlakisAl(const QUrl&)));
    connect(paĝo, SIGNAL(highlighted(const QUrl&)), this, SLOT(traktuKeKursoroShwebasSuper(const QUrl&)));
}

Nenio Rezultujo::agorduWortojn(RezultoDeLegado p_rezulto, ℕ p_elektitaFrazaro, ℕ p_elektitaWorto)
{
    rezulto = p_rezulto;
    elektitaFrazaro = p_elektitaFrazaro;
    elektitaWorto = p_elektitaWorto;
    rekreuListon();
}

Nenio Rezultujo::agorduElektitanWorton(ℕ frazaro, ℕ worto)
{
    elektitaFrazaro = frazaro;
    elektitaWorto = worto;
    rekreuListon();
}

Nenio Rezultujo::traktuKeUzantoKlakisAl(const QUrl& ligilo)
{
    Paro<ℕ, ℕ> wortnumero = donuWortnumeronEnLigilo(ligilo);
    const LegitaWorto& worto = rezulto.frazaroj[wortnumero.first].wortoj[wortnumero.second];
    kiamUzantoKlakasAlWorto(worto, wortnumero.first, wortnumero.second);
}

Nenio Rezultujo::traktuKeKursoroShwebasSuper(const QUrl& ligilo)
{
    if (ligilo.isEmpty())
        kiamKursoroNeShwebasSuperIoAjn();
    else
    {
        Paro<ℕ, ℕ> wortnumero = donuWortnumeronEnLigilo(ligilo);
        kiamKursoroShwebasSuper(rezulto.frazaroj[wortnumero.first].wortoj[wortnumero.second]);
    }
}

Nenio Rezultujo::rekreuListon()
{
    QString html;
    
    for (ℕ numeroDeFrazaro = 0; numeroDeFrazaro < rezulto.frazaroj.grandon(); numeroDeFrazaro++)
    {
        const LegitaFrazaro& frazaro = rezulto.frazaroj[numeroDeFrazaro];
        
        html += "<center><div class=\"frazaro\">";
        
        for (ℕ numeroDeWorto = 0; numeroDeWorto < frazaro.wortoj.grandon(); numeroDeWorto++)
        {
            const LegitaWorto& worto = frazaro.wortoj[numeroDeWorto];
            
            html += "<span class=\"worto";
            if (numeroDeFrazaro == elektitaFrazaro kaj numeroDeWorto == elektitaWorto)
                html += " elektita";
            html += "\"><a href=\"" + (alTexto(numeroDeFrazaro) + apartiganto + alTexto(numeroDeWorto)).QT() + "\">";
            
            for (const LegitaLitero& litero : worto.literoj)
            {
                QString qLitero = litero.verŝajnimajKarakteroj[0].QT();
                if (qLitero == "<")
                    qLitero = "&lt;";
                else if (qLitero == ">")
                    qLitero = "&gt;";
                
                if (litero.certecoj[0] < malgrandima_bona_certeco)
                    html += "<span class=\"malcerta\">" + qLitero + "</span>";
                else html += qLitero;
            }
            
            html += "</a></span> ";
        }
        
        html += "</div></center>";
    }
    
    paĝo->setHtml(html);
}

Paro<ℕ, ℕ> Rezultujo::donuWortnumeronEnLigilo(const QUrl& ligilo)
{
    Texto textajNumeroj = ligilo.toString();
    auto serĉrezulto = textajNumeroj.provuTrovi(apartiganto);
    premisu (serĉrezulto.ĉuValidas());
    ℕ numeroDeFrazaro = textajNumeroj.donuPartonInter(0, serĉrezulto.donuLokon()).alℕ();
    ℕ numeroDeWorto = textajNumeroj.donuPartonInter(serĉrezulto.donuLokon() + 1, textajNumeroj.grandon()).alℕ();
    eligu {numeroDeFrazaro, numeroDeWorto};
}
