#ifndef WORTSERCXILO_EKRANBILDO_HPP
#define WORTSERCXILO_EKRANBILDO_HPP

#include <filesystem>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDesktopWidget>
#include "komuna/Texto.hpp"
#include "komuna/Eraro.hpp"
#include "komuna/alTexto.hpp"
#include "komuna/geom/Ortangelo.hpp"

inline Nenio kreuBildonDeEkrano(const Texto& celdosiero, Ortangelo<ℤ> ortangelo)
{
    QPixmap bildo = QApplication::primaryScreen()->grabWindow(QApplication::desktop()->winId(),
            ortangelo.x, ortangelo.y, ortangelo.l, ortangelo.a);
    if (ne bildo.save(celdosiero.QT()))
        throw Eraro("Konservi ekranbildon al «" + celdosiero + "» malsukcesis.");
}

#endif //WORTSERCXILO_EKRANBILDO_HPP
