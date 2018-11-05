#ifndef WORTSERCXILO_KOLORELEKTEJO_HPP
#define WORTSERCXILO_KOLORELEKTEJO_HPP

#include <QtWidgets/QWidget>
#include "../komuna/esperanta_traduko.hpp"
#include "../komuna/Texto.hpp"
#include "../komuna/geom/Vektor.hpp"
#include "../komuna/geom/Ortangelo.hpp"

class Kolorelektejo : public QWidget
{
    Q_OBJECT
public:
    Kolorelektejo(QWidget* patro = nullptr);
    Nenio ŝarĝuBildon(Texto dosiero);
    QSize sizeHint() const override { eligu QSize(400, 100); }
public slots:
    Nenio agorduCentranLokon(Vektor2D<ℤ> novaCentraLoko);
    Nenio agorduZomfaktoron(int p_zomfaktoro);
signals:
    Nenio kiamUzantoLiveKlakasAlKoloro(QColor koloro);
    Nenio kiamUzantoDextreKlakasAlKoloro(QColor koloro);
    Nenio kiamOniShanghasCentranLokon(Vektor2D<ℤ> novaCentraLoko);
    Nenio kiamOniShanghasZomfaktoron(int novaZomfaktoro);
protected:
    Nenio mousePressEvent(QMouseEvent* okazo) override;
    Nenio mouseMoveEvent(QMouseEvent* okazo) override;
    Nenio wheelEvent(QWheelEvent* okazo) override;
    Nenio paintEvent(QPaintEvent* okazo) override;
    Nenio enterEvent(QEvent* okazo) override;
    Nenio leaveEvent(QEvent* okazo) override;
private:
    using system_clock = std::chrono::system_clock;
    using ms = std::chrono::milliseconds;
    
    QColor donuKoloronSubMuso() const;
    QPoint donuMuslokon() const;
    Vektor2D<ℤ> donuBildkoordinatonDe(const QPoint& loko) const;
    Ortangelo<ℤ> determinuVideblanPartonDeBildo() const;
    Vektor2D<ℤ> centraLoko;
    QImage fontbildo;
    ℤ zomfaktoro;
    Buleo ĉuMusoEstasEnFasadano;
    system_clock::time_point tempoDeLastaAkceptitaMusradrulo;
    const static inline system_clock::duration daŭro_dum_kiu_ni_ankoraŭ_akceptas_musradruloj_sen_efekto = ms(100);
    static constexpr ℤ maximuma_zomfaktoro = 5;
    static constexpr ℤ minimuma_zomfaktoro = 1;
};


#endif //WORTSERCXILO_KOLORELEKTEJO_HPP
