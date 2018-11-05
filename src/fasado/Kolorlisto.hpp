#ifndef WORTSERCXILO_KOLORLISTO_HPP
#define WORTSERCXILO_KOLORLISTO_HPP

#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include <QtCore/QPropertyAnimation>
#include <chrono>
#include <QtCore/QTimer>
#include "../komuna/Texto.hpp"
#include "../komuna/PropraAdres.hpp"
#include "SequencoDeAnimacioj.hpp"

class Kolorlisto : public QWidget
{
Q_OBJECT
public:
    Kolorlisto(QWidget* patro = nullptr); //-«
    Nenio agorduFlankkoloron(const QColor& koloro) { flankkoloro = koloro; update(); }
    Nenio enmetuKoloron(const QColor& koloro);
    Nenio forprenuKoloron(const QColor& koloro);
    Buleo ĉuEstasMalplenan() const;
    Listo<QColor> donuKolorojn() const;
    QSize sizeHint() const override { eligu QSize(100, 20); }
signals:
    Nenio kiamUzantoKlakasAlKoloro(const QColor& koloro);
    Nenio kiamIghasMalplenan();
    Nenio kiamIghasNePluMalplenan();
protected:
    Nenio mouseReleaseEvent(QMouseEvent* okazo) override;
    Nenio mouseMoveEvent(QMouseEvent* okazo) override;
    Nenio paintEvent(QPaintEvent* okazo) override;
    Nenio leaveEvent(QEvent* okazo) override;
private slots:
    Nenio forprenuForprenendajnKolorojn();
private:
    struct Koloro
    {
        QColor koloro;
        ℚ larĝo;
        ℕ veraLarĝo;
        QPointer<QVariantAnimation> animacio;
        Buleo ĉuEstasForprenatan;
    };
    
    Nenio agorduSuperŝwebitanKoloron(Koloro* koloro);
    Nenio renovuVerajnLarĝojn();
    Koloro* determinuKoloronSub(QPoint loko);
    Nenio komencuAnimacion(Koloro* koloro, ℚ finaLarĝo, ℕ milisekundoj, QEasingCurve kurbo = QEasingCurve::InOutQuint);
    
    Koloro* superŝwebitaKoloro;
    QColor flankkoloro;
    Listo<PropraAdres<Koloro>> koloroj;
    static constexpr ℕ larĝo_de_flankkoloro = 5;
};


#endif //WORTSERCXILO_KOLORLISTO_HPP
