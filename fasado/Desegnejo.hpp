#ifndef WORTSERCXILO_DESEGNEJO_HPP
#define WORTSERCXILO_DESEGNEJO_HPP

#include <QtWidgets/QWidget>
#include "../komuna/Texto.hpp"
#include "../komuna/geom/Vektor.hpp"
#include "../komuna/geom/Ortangelo.hpp"

class BinaraDesegnejo : public QWidget
{
Q_OBJECT
public:
    enum Broŝo { nigra_broŝo, blanka_broŝo, wiŝilo, nigra_inundanto, blanka_inundanto };
    BinaraDesegnejo(QWidget* patro = nullptr);
    Nenio ŝarĝuBildon(Texto dosiero);
    Nenio konservuBildon(Texto dosiero);
    Nenio enmetuEmfazon(Ortangelo<ℤ> zono);
    Nenio forprenuEmfazon(Ortangelo<ℤ> zono); // se la emfazo aperas multfoje, oni nur forprenas ĝin unufoje
    QSize sizeHint() const override { eligu QSize(400, 100); }
public slots:
    Nenio agorduBroshgrandon(int p_broshgrando);
    Nenio agorduCentranLokon(Vektor2D<ℤ> novaCentraLoko);
    Nenio agorduZomfaktoron(int p_zomfaktoro);
signals:
    Nenio kiamUzantoFinisDesegniIon();
    Nenio kiamOniShanghasCentranLokon(Vektor2D<ℤ> novaCentraLoko);
    Nenio kiamOniShanghasZomfaktoron(int novaZomfaktoro);
protected:
    Nenio mousePressEvent(QMouseEvent* okazo) override;
    Nenio mouseReleaseEvent(QMouseEvent* okazo) override;
    Nenio mouseMoveEvent(QMouseEvent* okazo) override;
    Nenio wheelEvent(QWheelEvent* okazo) override;
    Nenio paintEvent(QPaintEvent* okazo) override;
    Nenio enterEvent(QEvent* okazo) override;
    Nenio leaveEvent(QEvent* okazo) override;
private:
    using system_clock = std::chrono::system_clock;
    using ms = std::chrono::milliseconds;
    
    Buleo ĉuOniPremasIunMusklavon(const QMouseEvent* musokazo) const;
    Nenio aplikuBroŝojn(QMouseEvent* okazo);
    Nenio aplikuBroŝon(Broŝo broŝo, Vektor2D<ℤ> koordinato, QImage* celbildo);
    static Nenio aplikuNormanBroŝon(Broŝo broŝo, Vektor2D<ℤ> koordinato, ℤ broŝgrando, QImage* celbildo);
    static Nenio inundu(Vektor2D<ℤ> koordinato, QColor koloro,
                        const QImage* bildo1, const QImage* bildo2, QImage* celbildo);
    QPoint donuMuslokon() const;
    Vektor2D<ℤ> donuBildkoordinatonDe(const QPoint& loko) const;
    Ortangelo<ℤ> determinuVideblanPartonDeBildo() const;
    Listo<Ortangelo<ℤ>> emfazoj;
    Vektor2D<ℤ> centraLoko;
    Broŝo livaBroŝo;
    QImage surmetaBildo;
    QImage fontbildo;
    ℤ broŝgrando;
    ℤ zomfaktoro;
    Buleo ĉuDesegnisIonEkdeKursoroEnirisFasadano;
    Buleo ĉuMusoEstasEnFasadano;
    Buleo ĉuPentrasIon;
    system_clock::time_point tempoDeLastaAkceptitaMusradrulo;
    const static inline system_clock::duration daŭro_dum_kiu_ni_ankoraŭ_akceptas_musradruloj_sen_efekto = ms(100);
    static constexpr ℤ maximuma_broŝgrando = 30;
    static constexpr ℤ minimuma_broŝgrando = 1;
    static constexpr ℤ maximuma_zomfaktoro = 5;
    static constexpr ℤ minimuma_zomfaktoro = 1;
};


#endif //WORTSERCXILO_DESEGNEJO_HPP
