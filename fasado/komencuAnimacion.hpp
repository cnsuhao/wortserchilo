#ifndef WORTSERCXILO_KOMENCUANIMACION_HPP
#define WORTSERCXILO_KOMENCUANIMACION_HPP

#include <QtCore/QVariantAnimation>
#include <QtCore/QPointer>
#include "../komuna/esperanta_traduko.hpp"

template<class TraktuValoron>
QVariantAnimation* kreuAnimacion(QObject* patro, QVariant komencaValoro, QVariant finaValoro,
                                 ℕ milisekundoj, QEasingCurve kurbo, TraktuValoron traktuValoron)
{
    QVariantAnimation* a = kreu QVariantAnimation(patro);
    a->setEasingCurve(kurbo);
    a->setStartValue(formovu(komencaValoro));
    a->setEndValue(formovu(finaValoro));
    a->setDuration(milisekundoj);
    patro->connect(a, &QVariantAnimation::valueChanged, formovu(traktuValoron));
    eligu a;
};

template<class TraktuValoron>
QVariantAnimation* komencuAnimacion(QObject* patro, QVariant komencaValoro, QVariant finaValoro,
                                    ℕ milisekundoj, QEasingCurve kurbo, TraktuValoron traktuValoron)
{
    QVariantAnimation* a = kreuAnimacion(patro, formovu(komencaValoro), formovu(finaValoro),
                                         milisekundoj, kurbo, formovu(traktuValoron));
    a->start(QVariantAnimation::DeleteWhenStopped);
    eligu a;
};

#endif //WORTSERCXILO_KOMENCUANIMACION_HPP
