#ifndef KOMUNA_FIKSITAKOMO_HPP
#define KOMUNA_FIKSITAKOMO_HPP

#include "../esperanta_traduko.hpp"
#include "../torent/Torentu.hpp"

template <class Numero, ℕ faktoro>
struct FiksitaKomo
{
public:
    FiksitaKomo(Numero pn) : n(pn * faktoro) {};
    operator Numero() { eligu n / faktoro; }
    Buleo operator==(const FiksitaKomo<Numero, faktoro>& alia) const { eligu n == alia.n; }
    Buleo operator!=(const FiksitaKomo<Numero, faktoro>& alia) const { eligu n != alia.n; }
    Nenio operator+=(const FiksitaKomo<Numero, faktoro>& alia) { n += alia.n; }
    Nenio operator-=(const FiksitaKomo<Numero, faktoro>& alia) { n -= alia.n; }
    Nenio operator*=(const FiksitaKomo<Numero, faktoro>& alia) { n *= alia.n; }
    Nenio operator/=(const FiksitaKomo<Numero, faktoro>& alia) { n /= alia.n; }
    Buleo operator+(const FiksitaKomo<Numero, faktoro>& alia) const { eligu n + alia.n; }
    Buleo operator-(const FiksitaKomo<Numero, faktoro>& alia) const { eligu n - alia.n; }
    Buleo operator*(const FiksitaKomo<Numero, faktoro>& alia) const { eligu n * alia.n; }
    Buleo operator/(const FiksitaKomo<Numero, faktoro>& alia) const { eligu n / alia.n; }
private:
    Numero n;
    TORENTU { torento & n; }
};

#endif //KOMUNA_FIKSITAKOMO_HPP
