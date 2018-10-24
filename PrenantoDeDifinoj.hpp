#ifndef WORTSERCXILO_PRENANTODEDIFINOJ_HPP
#define WORTSERCXILO_PRENANTODEDIFINOJ_HPP

#include <QtCore/QThread>
#include "Wortarestro.hpp"

class PrenantoDeDifinoj : public QObject
{
Q_OBJECT
public:
    PrenantoDeDifinoj(Texto worto, Wortarestro* wortarestro, std::mutex* mutex_wortarestro,
                      Buleo ĉuWortoEstasExaktan, Linguo volataLinguo = neniu_linguo);
    ~PrenantoDeDifinoj() override;
signals:
    Nenio traktuNovanDifinon(Difino difino);
    Nenio kiamFinis();
public slots:
    Nenio komencu() { QMetaObject::invokeMethod(this, "_komencu"); };
    Nenio rekomencu() { QMetaObject::invokeMethod(this, "_rekomencu"); }
    Nenio maldaureHaltu() { QMetaObject::invokeMethod(this, "_maldaureHaltu"); }
    Nenio nuligu() { QMetaObject::invokeMethod(this, "_nuligu"); }
private slots:
    Nenio _komencu();
    Nenio _rekomencu();
    Nenio _maldaureHaltu() { ĉuVolasPliDifinojn = malveran; }
    Nenio _nuligu();
private:
    Nenio kreuListonDeSugestoj();
    Texto worto;
    Linguo volataLinguo;
    Wortarestro* wortarestro;
    std::mutex* mutex_wortarestro;
    Listo<Wortarestro::Sugesto> sugestoj;
    ℕ aktivaSugesto;
    Buleo ĉuVolasPliDifinojn;
    Buleo ĉuWortoEstasExaktan;
    Buleo ĉuNuligis;
    Buleo ĉuEstasEnLuso;
    QThread fadeno;
};

#endif //WORTSERCXILO_PRENANTODEDIFINOJ_HPP
