#ifndef WORTSERCHILO_MONTRUERARON_HPP
#define WORTSERCHILO_MONTRUERARON_HPP

#include <QtWidgets/QMessageBox>
#include "komuna/Texto.hpp"

inline Nenio montruEraron(const Texto& texto)
{
    QMessageBox::critical(nullptr, "Eraro", texto.QT());
    std::cerr << texto.STL() << std::endl;
}

#endif //WORTSERCHILO_MONTRUERARON_HPP
