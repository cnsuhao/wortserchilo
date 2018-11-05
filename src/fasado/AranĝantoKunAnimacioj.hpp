#ifndef WORTSERCXILO_VERTIKALAKRADOKUNANIMACIOJ_HPP
#define WORTSERCXILO_VERTIKALAKRADOKUNANIMACIOJ_HPP

#include <QtCore/QPointer>
#include <QtWidgets/QWidget>
#include <QtCore/QVariantAnimation>
#include <QtWidgets/QLayout>
#include "../komuna/geom/Vektor.hpp"
#include "../komuna/Listo.hpp"
#include "../komuna/DividataAdres.hpp"

class AranghantoKunAnimacioj : public QWidget
{
Q_OBJECT
public:
    struct Aranĝo
    {
        struct Ano
        {
            Ano() = default;
            Ano(QWidget* widget, Vektor2D<ℚ> loko, Vektor2D<ℚ> grando,
                Vektor2D<ℤ> deiĝo = {0, 0}, Vektor2D<ℤ> deiĝoDeGrando = {0, 0});
            Ano(QWidget* widget, ℚ x, ℚ y, ℚ l, ℚ a, ℤ d_x = 0, ℤ d_y = 0, ℤ d_l = 0, ℤ d_a = 0);
            Nenio agorduWidgeton(QWidget* p_widget) { widget = p_widget; }
            Nenio renovuZonon(Vektor2D<ℤ> grandoDePatro);
            Vektor2D<ℤ> determinuFinanLokon(Vektor2D<ℤ> grandoDePatro) const;
            Vektor2D<ℤ> determinuFinanGrandon(Vektor2D<ℤ> grandoDePatro) const;
            Buleo ĉuWidgetValidas() const { eligu QPointer<const QWidget>(widget); }
            Vektor2D<ℚ> loko;
            Vektor2D<ℤ> deiĝo;
            Vektor2D<ℚ> grando;
            Vektor2D<ℤ> deiĝoDeGrando;
            QWidget* widget;
        };
        
        Aranĝo() = default;
        Aranĝo(std::initializer_list<Ano> p) : anoj(formovu(p)) {}
        Vektor2D<ℤ> determinuMinimumanGrandon() const;
        Vektor2D<ℤ> determinuMaximumanGrandon() const;
        Buleo ĉuĜustas() const;
        Listo<Ano>::NeŝanĝeblaPaŝanto provuTrovi(QWidget* widget) const;
        Buleo ĉuEnhavas(QWidget* widget) const;
        Listo<Ano> anoj;
    };
    
    enum Direkto { supren, suben, dextren, liven };
    
    AranghantoKunAnimacioj(QWidget* patro = nullptr) : QWidget(patro) {}
    Buleo ĉuLudasAnimacion() const { eligu ne ludantajAnimacioj.ĉuEstasMalplenan(); }
    Nenio preterlasuAnimacion(); // la fenestroj saltas al iliaj finaj lokoj
    Nenio haltuAnimacion(); // la fenestroj restas en iliaj nunaj lokoj
    Vektor2D<ℤ> grandon() { eligu {grando.width(), grando.height()}; }
    
    // se iu animacio ankoraŭ ludas te la grandoj kaj lokoj povas ankoraŭ havi interajn valorojn
    const Aranĝo& donuAranĝon() const { eligu aranĝo; }
    
    Nenio agorduAranĝonSenAnimacio(Aranĝo novaAranĝo);
    Nenio agorduAranĝonRulante(Aranĝo novaAranĝo, Direkto direkto = supren,
                               ℕ milisekundoj = 300, QEasingCurve kurbo = QEasingCurve::InOutQuint);
    
    QSize maximumanGrandon() const;
    QSize minimumanGrandon() const;
    QSize sizeHint() const override { eligu minimumSize(); }

protected:
    Nenio resizeEvent(QResizeEvent* okazo) override;
signals:
    // Oni ankaŭ alvokas ĉi-signalon se oni haltis aŭ preterlasis animacion.
    // La aranĝanto ankaŭ haltas la animacion kiam oni agordas novan aranĝon dum ke la aranĝanto ankoraŭ ludas animacion
    Nenio kiamAnimacioFinas();
private:
    Nenio traktuKeAnimacioFinis(QVariantAnimation* finitaAnimacio = nullptr);
    
    struct ŜanĝojEnAranĝo
    {
        Listo<Aranĝo::Ano*> novajAnoj, novajRestantajAnoj;
        Listo<const Aranĝo::Ano*> malnovajRestantajAnoj, malnovajAnoj;
        // novajRestantajAnoj kaj malnovajRestantajAnoj enhavas la novajn kaj malnovajn formojn de restantaj anoj.
    };
    
    static ŜanĝojEnAranĝo determinuŜanĝojnEnAranĝo(Aranĝo& nova, const Aranĝo& malnova);
    
    QSize grando;
    Aranĝo aranĝo;
    Listo<QPointer<QVariantAnimation>> ludantajAnimacioj;
};

typedef AranghantoKunAnimacioj AranĝantoKunAnimacioj;

#endif //WORTSERCXILO_VERTIKALAKRADOKUNANIMACIOJ_HPP
