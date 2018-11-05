#ifndef WORTSERCXILO_DIFINUJO_HPP
#define WORTSERCXILO_DIFINUJO_HPP

#ifdef ĈU_UZAS_ICU_UNICODE
#include <unicode/translit.h>
#endif
#include <QtWidgets/QTextBrowser>
#include <QtCore/QEvent>
#include "../komuna/traduko/Linguo.hpp"
#include "../Difino.hpp"
#include "../komuna/PropraAdres.hpp"

class Difinujo : public QWidget
{
Q_OBJECT
public:
    Difinujo(QWidget* patro = nullptr);
    QSize sizeHint() const override { return paĝo->sizeHint(); }
    Buleo provuAgordiTransliteranton(const Texto& nomo);
    Nenio preparuTextojn();
public slots:
    Nenio komencuTorentonDeDifinoj();
    Nenio enmetuDifinon(Difino difino);
    Nenio finuTorentonDeDifinoj();
signals:
    Nenio kiamUzantoKlakasAlLigilo(Texto celo);
    Nenio kiamBezonasPliDifinojn();
    Nenio kiamNeBezonasPliDifinojn();
protected:
    Nenio changeEvent(QEvent* okazo) override { if (okazo->type() == QEvent::LanguageChange) preparuTextojn(); } //-«
    Nenio resizeEvent(QResizeEvent* okazo) override { elsenduChuBezonasPliDifinojn(); QWidget::resizeEvent(okazo); }//»-
private slots:
    Nenio elsenduChuBezonasPliDifinojn();
    Nenio traktuLigilon(const QUrl& nomo);
private:
    Buleo ĉuBezonasPliDifinojn() const;
    Nenio rekreuPaĝonKajIruAlKomencoDePaĝo();
    Nenio rekreuPaĝonKajRestuEnLaSamaLoko();
    Nenio rekreuPaĝon();
    
    Buleo ĉuĴusBezonisPliDifinojn;
    Buleo ĉuTorentoDeDifinojFinis;
    Listo<Difino> difinoj;
#ifdef ĈU_UZAS_ICU_UNICODE
    PropraAdres<Transliterator> transliteranto;
#endif
    
    QTextBrowser* paĝo;
    
    QString texto_ŝarĝante;
    QString texto_ne_trovis_difinojn;
};


#endif //WORTSERCXILO_DIFINUJO_HPP
