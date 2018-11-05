#ifndef WORTSERCXILO_REZULTUJO_HPP
#define WORTSERCXILO_REZULTUJO_HPP

#include <QtWidgets/QPushButton>
#include <QtCore/QEvent>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QTextBrowser>
#include "../komuna/Listo.hpp"
#include "../komuna/Texto.hpp"
#include "../komuna/Paro.hpp"
#include "../LegitaWorto.hpp"

class Rezultujo : public QWidget
{
Q_OBJECT
public:
    Rezultujo(QWidget* patro = nullptr);
    QSize sizeHint() const override { eligu paĝo->sizeHint(); }
    
    static constexpr ℕ malgrandima_bona_certeco = 240;
public slots:
    Nenio agorduWortojn(RezultoDeLegado p_rezulto, unsigned p_elektitaFrazaro, unsigned p_elektitaWorto);
    Nenio agorduElektitanWorton(unsigned frazaro, unsigned worto);
signals:
    Nenio kiamKursoroShwebasSuper(LegitaWorto worto);
    Nenio kiamKursoroNeShwebasSuperIoAjn();
    Nenio kiamUzantoKlakasAlWorto(LegitaWorto worto, unsigned numeroDeFrazaro, unsigned numeroDeWorto);
private slots:
    Nenio traktuKeUzantoKlakisAl(const QUrl& ligilo);
    Nenio traktuKeKursoroShwebasSuper(const QUrl& ligilo);
protected:
    Nenio leaveEvent(QEvent* okazo) override { kiamKursoroNeShwebasSuperIoAjn(); }
private:
    Nenio rekreuListon();
    Paro<ℕ, ℕ> donuWortnumeronEnLigilo(const QUrl& ligilo);
    
    ℕ elektitaFrazaro;
    ℕ elektitaWorto;
    RezultoDeLegado rezulto;
    QTextBrowser* paĝo;
    
    static constexpr char apartiganto = '_';
};


#endif //WORTSERCXILO_REZULTUJO_HPP
