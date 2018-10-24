#ifndef WORTSERCXILO_LINGUOMENUO_HPP
#define WORTSERCXILO_LINGUOMENUO_HPP


#include <QtWidgets/QWidget>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QLabel>
#include "../komuna/esperanta_traduko.hpp"
#include "../InformoDeWortaro.hpp"
#include "../komuna/Paro.hpp"
#include "AranĝantoKunAnimacioj.hpp"

class MenuoDeWortaresLinguoj : public QWidget
{
Q_OBJECT
public:
    MenuoDeWortaresLinguoj(QWidget* patro = nullptr);
    Nenio agorduElekteblajnWortarojn(InformoDeWortaroj p_wortaroj);
    Nenio agorduĈuWortaroEstasElektitan(const Texto& fonto, const Linguo& linguo, Buleo ĉuEstasElektitan);
    const Listo<Paro<Texto, Linguo>>& donuElektitajnWortarojn() const { eligu elektitajWortaroj; }
    Buleo ĉuEnhavasWortaron(const Texto& fonto, const Linguo& l) { eligu wortaroj.provuTrovi(fonto, l) != nullptr; }
    Nenio agorduLinguonDeFasado(Linguo linguo);
    Nenio preparuTextojn();
signals:
    Nenio kiamOniElektisNovanWortaron(const Texto& fonto, const Linguo& linguo);
    Nenio kiamOniMalelektisWortaron(const Texto& fonto, const Linguo& linguo);
protected:
    Nenio resizeEvent(QResizeEvent* okazo) override { regrandiguKolumnojnDeTabeloDeWortaroj(); };
private:
    Nenio rekreuAranĝon();
    Nenio kreuListonDeWortaroj();
    Nenio kreuListonDeElektitajWortaroj();
    Nenio markuWortaron(const Texto& fonto, const Linguo& linguo, Buleo ĉuEstasMarkitan);
    Nenio markuAnon(QTreeWidgetItem* ano, Buleo ĉuEstasMarkitan) const;
    Nenio montruPriskribonDeWortaro(const Texto& fonto, const Linguo& linguo);
    Nenio regrandiguKolumnojnDeTabeloDeWortaroj();
    
    Linguo linguoDeFasado;
    AranĝantoKunAnimacioj* aranĝanto;
    QLabel* kapo;
    QTextEdit* informujo;
    QTreeWidget* fWortaroj;
    QTreeWidget* fElektitajWortaroj;
    InformoDeWortaroj wortaroj;
    Listo<Paro<Texto, Linguo>> elektitajWortaroj;
    Buleo ĉuMontrasFonton;
    
    inline const static QColor elektita_textkoloro = QColor(255, 255, 255);
    inline const static QColor elektita_fonkoloro = QColor(0, 0, 120);
};


#endif //WORTSERCXILO_LINGUOMENUO_HPP
