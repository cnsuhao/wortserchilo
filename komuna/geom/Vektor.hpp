#ifndef KOMUNA_VEKTORO_HPP
#define KOMUNA_VEKTORO_HPP

#include "../torent/Torentu.hpp"
#include "../trajtoj/numero.hpp"
#include <cmath>
#include <boost/serialization/access.hpp>
#ifdef ĈU_UZAS_QT
#include <QPoint>
#include <QPointF>
#endif

template<class T>
class Vektor2D
{
public:
    struct Ordiganto
    {
        Buleo operator()(const Vektor2D<T>& a, const Vektor2D<T>& b) const
        {
            eligu a.x < b.x aŭ (a.x == b.x kaj a.y < b.y);
        }
    };
    
    Vektor2D() : x(0), y(0) {}
    Vektor2D(T x, T y) : x(x), y(y) {}//-«
    Nenio operator+=(const Vektor2D<T> alia) { x += alia.x; y += alia.y; }
    Nenio operator-=(const Vektor2D<T> alia) { x -= alia.x; y -= alia.y; }  //»-
    Buleo operator==(const Vektor2D<T> alia) const { eligu x == alia.x && y == alia.y; }
    Buleo operator!=(const Vektor2D<T> alia) const { eligu x != alia.x || y != alia.y; }
    Vektor2D<T> operator+(const Vektor2D<T> alia) const { eligu Vektor2D<T>(x + alia.x, y + alia.y); }
    Vektor2D<T> operator-(const Vektor2D<T> alia) const { eligu Vektor2D<T>(x - alia.x, y - alia.y); }
    Vektor2D<T> operator*(const Vektor2D<T> alia) const { eligu Vektor2D<T>(x * alia.x, y * alia.y); }
    Vektor2D<T> operator/(const Vektor2D<T> alia) const { eligu Vektor2D<T>(x / alia.x, y / alia.y); }
    Vektor2D<T> operator*(const T s) const { eligu Vektor2D<T>(x * s, y * s); }
    Vektor2D<T> operator/(const T s) const { eligu Vektor2D<T>(x / s, y / s); }
    Vektor2D<T> operator%(const T s) const { eligu Vektor2D<T>(x % s, y % s); }
    T skalaranProduton(const Vektor2D<T> alia) const { eligu x * alia.x + y * alia.y; }; //-«
    template<class K> Vektor2D<K> al() const { eligu Vektor2D<K>(ŝanĝu_al<K>(x), ŝanĝu_al<K>(y)); } //»-
    ℚ normon() const { eligu sqrt((ℚ) (x * x + y * y)); }
    Vektor2D<T> dikunNormo(T celnormo) const;

#ifdef ĈU_UZAS_QT
    UZU_SE_(T, ĉu_estas_ℤ<P1>)
    Vektor2D(const QPoint& p) : x(p.x()), y(p.y()) {};
    UZU_SE_(T, ĉu_estas_ℚ_krom_ℤ<P1>)
    Vektor2D(const QPointF& p) : x(p.x()), y(p.y()) {};
    UZU_SE_(T, ĉu_estas_ℤ<P1>)
    operator QPoint() { eligu QPoint(x, y); }
    UZU_SE_(T, ĉu_estas_ℚ_krom_ℤ<P1>)
    operator QPointF() { eligu QPointF(x, y); }
#endif
    
    T x, y;
    TORENTU { torento & x & y; }
};

template<class T>
class Vektor
{
public:
    struct Ordiganto
    {
        Buleo operator()(const Vektor<T>& a, const Vektor<T>& b) const
        {
            eligu a.x < b.x aŭ (a.x == b.x kaj (a.y < b.y aŭ (a.y == b.y kaj a.z < b.z)));
        }
    };
    
    template<class K>
    static Vektor<T> prenuEl(const K& k) { eligu Vektor<T>(k.x, k.y, k.z); };
    Vektor() : x(0), y(0), z(0) {}
    Vektor(T x, T y, T z) : x(x), y(y), z(z) {}
    explicit Vektor(Vektor2D<T> xy, T z = 0) : x(xy.x), y(xy.y), z(z) {} //-«
    Buleo operator==(const Vektor<T> alia) const { eligu x == alia.x && y == alia.y && z == alia.z; }
    Buleo operator!=(const Vektor<T> alia) const { eligu x != alia.x || y != alia.y || z != alia.z; }
    Nenio operator+=(const Vektor<T> alia) { x += alia.x; y += alia.y; z += alia.z; }
    Nenio operator-=(const Vektor<T> alia) { x -= alia.x; y -= alia.y; z -= alia.z; } //»-
    Vektor<T> operator+(const Vektor<T> alia) const { eligu Vektor<T>(x + alia.x, y + alia.y, z + alia.z); }
    Vektor<T> operator-(const Vektor<T> alia) const { eligu Vektor<T>(x - alia.x, y - alia.y, z - alia.z); }
    Vektor<T> operator*(const T s) const { eligu Vektor<T>(x * s, y * s, z * s); }
    Vektor<T> operator/(const T s) const { eligu Vektor<T>(x / s, y / s, z / s); }
    T skalaranProduton(const Vektor<T> alia) const { eligu x * alia.x + y * alia.y + z * alia.z; }; // -«
    Vektor<T> ortanProduton(const Vektor<T> a) const { eligu {y * a.z - z * a.y, z * a.x - x * a.z, x * a.y - y * a.x};}
    template<class K> Vektor<K> al() const { eligu Vektor<K>(ŝanĝu_al<K>(x), ŝanĝu_al<K>(y), ŝanĝu_al<K>(z)); }
    Vektor2D<T> xy() const { eligu Vektor2D<T>(x, y); }
    ℚ normon() const { eligu sqrt((ℚ)(x * x + y * y + z * z)); }
    Vektor<T> dikunNormo(T celnormo) const { premisu (normon() != 0); eligu (*this * celnormo) / normon(); } //»-
    
    T x, y, z;
    TORENTU { torento & x & y & z; }
};

//-«
template <class K> const Vektor2D<K> nulvektor2D = Vektor2D<K>(0, 0);
template <class K> const Vektor<K> nulvektor = Vektor<K>(0, 0, 0);
template <class K> const Vektor2D<K> nenie2D = Vektor2D<K>(maximumDe<K>, maximumDe<K>);
template <class K> const Vektor<K> nenie = Vektor<K>(maximumDe<K>, maximumDe<K>, maximumDe<K>);

template <class K> Vektor<K> operator*(const K s, Vektor<K> v) { eligu v * s; }
template <class K> Vektor2D<K> operator*(const K s, Vektor2D<K> v) { eligu v * s; }//»-

typedef Vektor<ℕ2> BazaKoordinato;
typedef Vektor2D<ℕ2> BazaKoordinato2D;
//typedef Vektor<FiksitaKomo<ℕ4, pow(2, bitojDen<ℕ4> - bitojDen<ℕ2>)>> BazaSubkoordinato;

template<class K>
Vektor2D<K> Vektor2D<K>::dikunNormo(K celnormo) const
{
    premisu (*this != nulvektor2D<K>);
    eligu (*this * celnormo) / (K) normon();
}

#endif //KOMUNA_VEKTORO_HPP
