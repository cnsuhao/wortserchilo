#ifndef WORTSERCXILO_MENUODEOPCIOJ_HPP
#define WORTSERCXILO_MENUODEOPCIOJ_HPP

#include <QtWidgets/QWidget>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include "../komuna/Texto.hpp"
#include "../komuna/traduko/Linguo.hpp"

class MenuoDeAgordoj : public QWidget
{
Q_OBJECT
public:
    MenuoDeAgordoj(QWidget* patro = nullptr);
    Nenio kaŝuĈuPreferasUziKopiitajnTextojn() { fĈuPreferasUziKopiitajnTextojn->hide(); }
    Nenio agorduElekteblajnLinguojn(const Listo<Texto>& elekteblajLinguoj);
    Nenio preparuTextojn();
    
    Nenio agorduDosierujonDeTesseract(const Texto& novaDosierujo);
    Nenio agorduKlavligonDeKursoro(const Texto& novaKlavligo);
    Nenio agorduKlavligonDePoŝo(const Texto& novaKlavligo);
    Nenio agorduRetejonDeParsoid(const Texto& novaRetejo);
    Nenio agorduGrandonDeBildo(const Texto& novaGrando);
    Nenio agorduLinguonDeFasado(const Texto& novaLinguo);
    Nenio agorduĈuPreferasUziKopiitajnTextojn(Buleo novaValoro);
    const Texto& donuDosierujonDeTesseract() const { eligu dosierujoDeTesseract; }
    const Texto& donuKlavligonDeKursoro() const { eligu klavligoDeKursoro; }
    const Texto& donuKlavligonDePoŝo() const { eligu klavligoDePoŝo; }
    const Texto& donuRetejonDeParsoid() const { eligu retejoDeParsoid; }
    const Texto& donuGrandonDeBildo() const { eligu grandoDeBildo; }
    const Linguo& donuLinguon() const { eligu linguoDeFasado; }
    Buleo donuĈuPreferasUziKopiitajnTextojn() const { eligu ĉuPreferasUziKopiitajnTextojn; }
    
    QSize sizeHint() const override { eligu QSize(400, 400); }
signals:
    // Se ŝanĝi la agordon malsukcesas, oni povas nuligi la ŝanĝon per agordi la eraron.
    Nenio kiamShanghasDosierujonDeTesseract(const Texto& novaDosierujo, std::exception_ptr* eraro);
    Nenio kiamShanghasKlavligonDeKursoro(const Texto& novaKlavligo, std::exception_ptr* eraro);
    Nenio kiamShanghasKlavligonDePosho(const Texto& novaKlavligo, std::exception_ptr* eraro);
    Nenio kiamShanghasRetejonDeParsoid(const Texto& novaRetejo, std::exception_ptr* eraro);
    Nenio kiamShanghasGrandonDeBildo(const Texto& novaGrando, std::exception_ptr* eraro);
    Nenio kiamShanghasLinguonDeFasado(const Linguo& novaLinguo, std::exception_ptr* eraro);
    Nenio kiamShanghasChuPreferasUziKopiitajnTextojn(Buleo novaValoro);
private:
    Nenio metuEraronEnProtokolo(std::exception_ptr& eraro);
    Linguo linguoDeFasado;
    Texto dosierujoDeTesseract;
    Texto klavligoDeKursoro;
    Texto klavligoDePoŝo;
    Texto retejoDeParsoid;
    Texto grandoDeBildo;
    Buleo ĉuPreferasUziKopiitajnTextojn;
    QScrollArea* rulanto;
    QLabel* lEraro;
    QLabel* lDosierujoDeTesseract;
    QLabel* lKlavligoDeKursoro;
    QLabel* lKlavligoDePoŝo;
    QLabel* lRetejoDeParsoid;
    QLabel* lGrandoDeBildo;
    QLabel* lCeteraTexto;
    QComboBox* fLinguoDeFasado;
    QLineEdit* fDosierujoDeTesseract;
    QLineEdit* fKlavligoDeKursoro;
    QLineEdit* fKlavligoDePoŝo;
    QLineEdit* fRetejoDeParsoid;
    QLineEdit* fGrandoDeBildo;
    QCheckBox* fĈuPreferasUziKopiitajnTextojn;
};


#endif //WORTSERCXILO_MENUODEOPCIOJ_HPP
