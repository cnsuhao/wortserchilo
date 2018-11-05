#ifndef VORTSERCXILO_ĈEFFENESTRO_HPP
#define VORTSERCXILO_ĈEFFENESTRO_HPP
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLineEdit>
#include "komuna/Texto.hpp"
#include "LegitaWorto.hpp"
#include "fasado/Difinujo.hpp"
#include "fasado/Rezultujo.hpp"
#include "fasado/Desegnejo.hpp"
#include "fasado/Kolorelektejo.hpp"
#include "Kolorfiltrilo.hpp"
#include "fasado/Kolorlisto.hpp"
#include "fasado/MenuoDeWortaresLinguoj.hpp"
#include "fasado/MenuoDeAgordoj.hpp"
#include "fasado/MenuoDeBildlegantesLinguoj.hpp"
#include "fasado/AranĝantoKunAnimacioj.hpp"
#include "komuna/UnikaroPara.hpp"

class Cheffenestro : public QMainWindow // bedaŭrinde QT ne akceptas literojn ne en ascii
{
Q_OBJECT
public:
    enum class Paĝo
    {
        bonvenanta_paĝo, bildleganto, difinoj, wortares_linguoj, bildlegantes_linguoj, agordoj_supraj, agordoj_subaj,
        neniu_paĝo
    };
    
    Cheffenestro();
    Nenio traktuŜanĝitajnLinguajnAgordojn(); // alvoku ĉi-tion post ŝanĝi iun menuon de linguoj
    Nenio reŝarĝuKoloranBildon();
    Nenio montruDifinojnDeWorto(const Texto& worto); //-«
    Nenio agorduBildgrandon(ℕ larĝo, ℕ alto) { bildlarĝo = larĝo; bildalto = alto; } //»-
    Nenio preparuTextojn();
    
    Nenio iruAlPaĝo(Paĝo paĝo); // se paĝŝanĝes animacio ankoraŭ ludas, ĉi-funkcio prokrastas la paĝŝanĝon
    Nenio iruAlPaĝo(Paĝo paĝo, AranĝantoKunAnimacioj::Direkto direkto); // ĉi-funkcio ĉiam tuj iras al la nova paĝo
    static Buleo ĉuPaĝoEstasEnSubaDuono(Paĝo paĝo);
    
    QPushButton* butonoDeLinguoj;
    QPushButton* butonoDeAgordoj;
    QLineEdit* tajpejo;
    Difinujo* difinujo;
    Rezultujo* rezultujo;
    Kolorelektejo* kolorelektejo;
    BinaraDesegnejo* desegnejo;
    Kolorlisto* nigraKolorlisto;
    Kolorlisto* blankaKolorlisto;
    MenuoDeWortaresLinguoj* wortaresLinguoj;
    MenuoDeBildlegantesLinguoj* bildlegantesLinguoj;
    MenuoDeAgordoj* menuoDeAgordoj;
    
    inline const static Texto kolora_bildo = "./kolora_bildo.png";
    inline const static Texto blanknigra_bildo = "./blanknigra_bildo.png";
public slots:
    Nenio traktuRezultonDeLegado(RezultoDeLegado rezulto);
    Nenio enmetuNigranKoloron(const QColor& koloro);
    Nenio enmetuBlankanKoloron(const QColor& koloro);
signals:
    Nenio kiamOniShanghasElektitajnWortarojn(const Listo<Paro<Texto, Linguo>>& linguoj);
    Nenio kiamOniShanghasElektitajnLinguojnDeBildleganto(const Listo<Texto>& linguoj);
    
    Nenio kiamVolasDifinojnDe(Texto worto, bool ĉuWortoEstasExaktan);
    Nenio kiamVolasDifinojnDe(Texto worto, bool ĉuWortoEstasExaktan, Linguo linguo);
    Nenio kiamNePluVolasDifinojn();
    
    // atendas ke la celdosiero estas plenigitan kiam la alvoko finas
    Nenio kiamBezonasBlanknigranVersionDeBildo(Texto bilddosiero, Texto celdosiero);
    Nenio kiamVolasTextonEnBildo(Texto bilddosiero);
    Nenio kiamNePluVolasTextonEnBildo();
    Nenio kiamVolasNomonDeBildleganto(Texto* celo); // atendas ke la celo estas plenigitan kiam la alvoko finas
private slots:
    Nenio traktuShanghitanTajplinion();
    Nenio traktuKlakonAlLigilo(Texto ligilo);
    Nenio shanghuWortonAl(LegitaWorto worto);
    Nenio shanghuEmfazatanWortonAl(LegitaWorto worto); // emfazata worto estas markitan en desegnejo
    Nenio rekreuInternanAranghonDeBildleganto();
protected:
    Nenio wheelEvent(QWheelEvent* okazo);
private:
    using Direkto = AranĝantoKunAnimacioj::Direkto;
    using Aranĝo = AranĝantoKunAnimacioj::Aranĝo;
    
    Nenio ŝanĝuWortonAl(Texto novaWorto);
    Nenio traktuNovanKoloranBildon();
    
    AranĝantoKunAnimacioj* aranĝanto;
    AranĝantoKunAnimacioj* aranĝantoDeBildleganto;
    UnikaroPara<Paĝo, Aranĝo> aranĝoj;
    Paĝo aktivaPaĝo;
    Paĝo prokrastitaPaĝo;
    
    Kolorfiltrilo kolorfiltrilo; // todo movu al Wortserchilo
    Texto nomoDeWorto;
    LegitaWorto emfazataWorto;
    LegitaWorto elektitaWorto;
    
    Buleo ĉuOniElektisNovajnWortarojn; // rilatas al linguomenuo
    Buleo ĉuOniElektisNovajnLinguojnDeBildleganto;
    
    std::deque<std::chrono::system_clock::time_point> tempojDeRuloj;
    
    ℕ bildlarĝo;
    ℕ bildalto;
};

typedef Cheffenestro Ĉeffenestro;

#endif //VORTSERCXILO_ĈEFFENESTRO_HPP
