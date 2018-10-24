#ifndef WORTSERCXILO_KOLORFILTRILO_HPP
#define WORTSERCXILO_KOLORFILTRILO_HPP

#undef ne
#include <QtGui>
#define ne not
#include "komuna/Texto.hpp"

class Kolorfiltrilo
{
public:
    Nenio kreuBlanknigranBildon(const Texto& fontdosiero, const Texto& celdosiero) const;
    
    Buleo ĉuEnhavasKolorojn() const { eligu !nigrajKoloroj.ĉuEstasMalplenan() aŭ !blankajKoloroj.ĉuEstasMalplenan(); }
    Nenio enmetuNigranKoloron(const QColor& k) { if (ne nigrajKoloroj.ĉuEnhavas(k)) nigrajKoloroj.enmetu(k); }
    Nenio enmetuBlankanKoloron(const QColor& k) { if (ne blankajKoloroj.ĉuEnhavas(k)) blankajKoloroj.enmetu(k); } //-«
    Nenio malplenigu() { nigrajKoloroj.malplenigu(); blankajKoloroj.malplenigu(); } //»-
    Nenio forprenuKoloron(const QColor& koloro)
    {
        nigrajKoloroj.forprenuĈiun(koloro);
        blankajKoloroj.forprenuĈiun(koloro);
    }
    
    const Listo<QColor>& nigrajnKolorojn() const { eligu nigrajKoloroj; }
    const Listo<QColor>& blankajnKolorojn() const { eligu blankajKoloroj; }

private:
    Listo<QColor> nigrajKoloroj;
    Listo<QColor> blankajKoloroj;
};

#endif //WORTSERCXILO_KOLORFILTRILO_HPP
