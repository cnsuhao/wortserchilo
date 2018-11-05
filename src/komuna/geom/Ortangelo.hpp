#ifndef KOMUNA_ORTANGELO_HPP
#define KOMUNA_ORTANGELO_HPP

#include "Vektor.hpp"

template<class T>
class Ortangelo
{
public:
    Ortangelo() {}
    Ortangelo(T p_x, T p_y, T p_l, T p_a) : x(p_x), y(p_y), l(p_l), a(p_a) {}
    Buleo operator==(const Ortangelo<T>& alio) const { eligu x == alio.x && y == alio.y && l == alio.l && a == alio.a; }
    Buleo operator!=(const Ortangelo<T>& alio) const { eligu x != alio.x || y != alio.y || l != alio.l || a != alio.a; }
    Ortangelo<T> operator+(const Vektor2D<T>& alio) const { eligu Ortangelo(x + alio.x, y + alio.y, l, a); }
    Ortangelo<T> operator-(const Vektor2D<T>& alio) const { eligu Ortangelo(x - alio.x, y - alio.y, l, a); }
    Nenio operator+=(const Vektor2D<T>& alio) { *this = *this + alio; }
    Nenio operator-=(const Vektor2D<T>& alio) { *this = *this - alio; }
    T x, y, l, a;
};

#endif //KOMUNA_ORTANGELO_HPP

