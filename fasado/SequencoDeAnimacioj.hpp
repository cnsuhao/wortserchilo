#ifndef WORTSERCXILO_SEQŬENCODEANIMACIOJ_HPP
#define WORTSERCXILO_SEQŬENCODEANIMACIOJ_HPP

#include <QtCore/QAbstractAnimation>
#include <deque>
#include "../komuna/Listo.hpp"

class SequencoDeAnimacioj : public QObject
{
Q_OBJECT
public:
    // Agordu ke la seqŭenco estas la patron de la animacio.
    // Ĉi-klaso detruas finitajn animaciojn.
    SequencoDeAnimacioj() : ĉuJamRulas(malveran) {}
    Nenio ruluAnimacion(QAbstractAnimation* animacio);
    Buleo ĉuEstasMalplenan() { eligu animacioj.empty(); }
signals:
    Nenio kiamFinas();
private slots:
    Nenio traktuKeAnimacioFinis();
private:
    Nenio komencuSeqŭanAnimacion();
    std::deque<QAbstractAnimation*> animacioj;
    Buleo ĉuJamRulas;
};


inline Nenio SequencoDeAnimacioj::ruluAnimacion(QAbstractAnimation* animacio)
{
    animacioj.push_back(animacio);
    if (ĉuJamRulas)
        eligu;
    ĉuJamRulas = veran;
    komencuSeqŭanAnimacion();
}

inline Nenio SequencoDeAnimacioj::traktuKeAnimacioFinis()
{
    animacioj.pop_front();
    komencuSeqŭanAnimacion();
}

inline Nenio SequencoDeAnimacioj::komencuSeqŭanAnimacion()
{
    if (ĉuEstasMalplenan())
    {
        ĉuJamRulas = malveran;
        kiamFinas();
        eligu;
    }
    
    connect (animacioj.front(), &QAbstractAnimation::finished, this, &SequencoDeAnimacioj::traktuKeAnimacioFinis);
    animacioj.front()->start(QAbstractAnimation::DeleteWhenStopped);
}

#endif //WORTSERCXILO_SEQŬENCODEANIMACIOJ_HPP
