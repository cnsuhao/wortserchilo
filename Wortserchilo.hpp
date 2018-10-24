#ifndef WORTSERCXILO_WORTSERĈILO_HPP
#define WORTSERCXILO_WORTSERĈILO_HPP

#include <QApplication>
#include <uglobalhotkeys.h>
#include "komuna/DividataAdres.hpp"
#include "Cheffenestro.hpp"
#include "Difino.hpp"
#include "PrenantoDeDifinoj.hpp"
#include "Bildleganto.hpp"
#include "komuna/UnikaroPara.hpp"
#include "komuna/alTexto.hpp"

class Wortserchilo : public QObject
{
Q_OBJECT
public:
    ~Wortserchilo();
    ℤ komencu(ℤ nombroDaArgumentoj, char** argumentoj);
    inline const static Texto neniu_bildleganto = "neniu bildleganto";
private slots:
    Nenio montruDifinojnDeWortoCheKursoro();
    Nenio montruDifinojnDeWortoEnPosho();
    
    // Eligas erarojn. Se ĉio ĝustas la rezulto estas malplenan.
    Texto provuReagordiBildleganton(Texto nomo, UnikaroPara<Texto, Texto> parametroj = {});
    Texto donuNomonDeBildleganto();
    Nenio determinuDifinojnDe(Texto worto, bool ĉuEstasExaktan);
    Nenio determinuDifinojnDe(Texto worto, bool ĉuEstasExaktan, Linguo linguo);
    Nenio traktuKePreniDifinojnFinis();
    Nenio kreuBlanknigranVersionDeBildo(Texto fontdosiero, Texto celdosiero);
    Nenio agorduLinguojnDeWortarestro(const Listo<Paro<Texto, Linguo>>& linguoj);
    Nenio agorduLinguojnDeBildleganto(const Listo<Texto>& linguoj);
    Nenio provuReagordiDosierujonDeTesseract(const Texto& novaDosierujo, std::exception_ptr* eraro);
    Nenio provuReagordiKlavligonDeKursoro(const Texto& novaKlavligo, std::exception_ptr* eraro);
    Nenio provuReagordiKlavligonDePosho(const Texto& novaKlavligo, std::exception_ptr* eraro);
    Nenio provuReagordiRetejonDeParsoid(const Texto& novaRetejo, std::exception_ptr* eraro);
    Nenio provuReagordiBildlarghon(const Texto& novaGrando, std::exception_ptr* eraro);
    Nenio provuReagordiLinguonDeFasado(const Linguo& novaLinguo, std::exception_ptr* eraro);
    Nenio dirivuBildlegantesLinguojnElElektitajWortaroj(const Listo<Paro<Texto, Linguo>>& linguoj);
private:
    enum Klavligo : size_t
    {
        legu_che_kursoro = 262242,
        legu_el_posho = 797141,
    };
    
    Texto ŝarĝuStilsjablonon();
    Listo<Texto> kreuListonDeDisponeblajnLinguojn();
    Nenio enmetuNormajnAgordojn();
    Nenio provuŜarĝiAgordojn(const Texto& dosiero);
    Nenio provuKonserviAgordojn(const Texto& dosiero);
    Nenio provuReagordiKlavligon(const Texto& novaKlavligo, std::exception_ptr* eraro, Klavligo klavligo);
    Nenio ŝarĝuLinguon(Linguo linguo);
    
    PropraAdres<Cheffenestro> ĉeffenestro;
    
    PropraAdres<QApplication> programo;
    PropraAdres<PrenantoDeDifinoj> prenanto;
    PropraAdres<Bildleganto> bildleganto;
    PropraAdres<Wortarestro> wortarestro;
    std::mutex mutex_wortarestro;
    UGlobalHotkeys* ĉieajKlavligoj;
    
    Texto prokrastitaWorto;
    Buleo prokrastitaĈuEstasExaktan;
    Linguo prokrastitaLinguo;
    
    PropraAdres<QTranslator> tradukanto;
    
    Buleo ĉuUzantoPreferasUziKopiitajnTextojn;
    ℕ bildlarĝo;
    ℕ bildalto;
    
    std::thread ŝarĝantaFadeno;
    inline static const Texto dosiero_de_agordoj = "./agordoj.txt";
};

#endif //WORTSERCXILO_WORTSERĈILO_HPP