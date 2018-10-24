#ifndef WORTSERCXILO_MENUODEWORTARESLINGUOJ_HPP
#define WORTSERCXILO_MENUODEWORTARESLINGUOJ_HPP

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

class MenuoDeBildlegantesLinguoj : public QWidget
{
Q_OBJECT
public:
    MenuoDeBildlegantesLinguoj(QWidget* patro = nullptr);
    Nenio agorduElekteblajnLinguojnPorBildleganto(Listo<Texto> p_linguoj);
    Nenio agorduĈuLinguoDeBildlegantoEstasElektitan(const Texto& nomo, Buleo ĉuEstasElektitan);
    const Listo<Texto>& donuElektitajnLinguojnPorBildleganto() const { eligu elektitajLinguojDeBildleganto; }
    const Listo<Texto>& donuĈiujnLinguojnPorBildleganto() const { eligu linguojDeBildleganto; }
    Nenio agorduLinguonDeFasado(Linguo linguo);
    Nenio preparuTextojn();
signals:
    Nenio kiamOniElektisNovajnLinguojnPorBildleganto();
private:
    Nenio rekreuAranĝon();
    Nenio kreuListonDeLinguojDeBildleganto();
    Nenio kreuListonDeElektitajLinguojDeBildleganto();
    Nenio markuLinguonDeBildleganto(const Texto& nomo, Buleo ĉuEstasMarkitan);
    Nenio markuAnon(QTreeWidgetItem* ano, Buleo ĉuEstasMarkitan) const;
    
    Linguo linguoDeFasado; // todo
    AranĝantoKunAnimacioj* aranĝanto;
    QLabel* kapo;
    QTreeWidget* fLinguojDeBildleganto;
    QTreeWidget* fElektitajLinguojDeBildleganto;
    Listo<Texto> linguojDeBildleganto;
    Listo<Texto> elektitajLinguojDeBildleganto;
    
    inline const static QColor elektita_textkoloro = QColor(255, 255, 255);
    inline const static QColor elektita_fonkoloro = QColor(0, 0, 120);
};

#endif //WORTSERCXILO_MENUODEWORTARESLINGUOJ_HPP
