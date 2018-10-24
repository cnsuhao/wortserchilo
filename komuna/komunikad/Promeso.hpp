#ifndef KOMUNA_PROMESO_HPP
#define KOMUNA_PROMESO_HPP

#include "../esperanta_traduko.hpp"
#include "../Paro.hpp"
#include "../DividataAdres.hpp"
#include "../PropraAdres.hpp"
#include "Semaforo.hpp"
#include "../Eraro.hpp"

struct Eraro_PromesoMortis : public Eraro { Eraro_PromesoMortis() : Eraro("Iu fadeno forgesis ĝies promeson.") {}};

template<class K>
class Promesita
{
    template<class L>
    friend
    class Promeso;
public:
    Promesita() = default;
    Promesita(const Promesita&) = delete;
    Promesita(Promesita&&) noexcept = default;
    Promesita& operator=(const Promesita&) = delete;
    Promesita& operator=(Promesita&&) noexcept = default;
    
    Buleo ĉuOniPlenumisPromeson() const;
    Buleo provuElpreniRezulton(K* celo);
    K elprenuRezulton(); // atendas la rezulton se oni ankoraŭ ne havas la rezulton
private:
    struct Datumo { Datumo() : semaforo(0) {} PropraAdres<K> rezulto; Semaforo semaforo; std::exception_ptr eraro; };
    Promesita(const DividataAdres<Datumo>& p_datumo) : datumo(p_datumo) {}
    DividataAdres<Datumo> datumo;
};

template<class K>
class Promeso
{
public:
    Promeso() = default;
    Promeso(const Promeso&) = delete;
    Promeso(Promeso&&) noexcept = default;
    Promeso& operator=(const Promeso&) = delete;
    Promeso& operator=(Promeso&&) noexcept = default;
    ~Promeso();
    
    static Paro<Promeso<K>, Promesita<K>> kreuPromeson();
    Nenio plenumuPromeson(const K& valoro);
    Nenio plenumuPromeson(K&& valoro);
    Nenio senduEraron(std::exception_ptr eraro);
private:
    Promeso(const DividataAdres<typename Promesita<K>::Datumo>& p_datumo) : datumo(p_datumo) {}
    DividataAdres<typename Promesita<K>::Datumo> datumo;
};

template<class K>
Promeso<K>::~Promeso()
{
    if (datumo != nullptr)
        senduEraron(std::make_exception_ptr(Eraro_PromesoMortis()));
}

template<class K>
Paro<Promeso<K>, Promesita<K>> Promeso<K>::kreuPromeson()
{
    DividataAdres<typename Promesita<K>::Datumo> datumo(kreu typename Promesita<K>::Datumo);
    eligu {Promeso<K>(datumo), Promesita<K>(datumo)};
}

template<class K>
Nenio Promeso<K>::plenumuPromeson(const K& valoro)
{
    premisu (datumo != nullptr);
    datumo->rezulto.reset(kreu K(valoro));
    datumo->semaforo.enmetuSignalon();
    datumo.reset();
}

template<class K>
Nenio Promeso<K>::plenumuPromeson(K&& valoro)
{
    premisu (datumo != nullptr);
    datumo->rezulto.reset(kreu K(formovu(valoro)));
    datumo->semaforo.enmetuSignalon();
    datumo.reset();
}

template<class K>
Nenio Promeso<K>::senduEraron(std::exception_ptr eraro)
{
    premisu (datumo != nullptr);
    datumo->eraro = formovu(eraro);
    datumo->semaforo.enmetuSignalon();
    datumo.reset();
}

template<class K>
Buleo Promesita<K>::ĉuOniPlenumisPromeson() const
{
    premisu (datumo != nullptr);
    eligu datumo->semaforo.ĉuHavasSignalon();
}

template<class K>
Buleo Promesita<K>::provuElpreniRezulton(K* celo)
{
    premisu (datumo != nullptr);
    if (ne datumo->semaforo.provuPreniSignalon())
        eligu malveran;
    if (datumo->eraro)
        std::rethrow_exception(datumo->eraro);
    premisu (datumo->rezulto != nullptr);
    *celo = formovu(*datumo->rezulto);
    datumo.reset();
    eligu veran;
}

template<class K>
K Promesita<K>::elprenuRezulton()
{
    premisu (datumo != nullptr);
    datumo->semaforo.atenduSignalon();
    if (datumo->eraro)
        std::rethrow_exception(datumo->eraro);
    premisu (datumo->rezulto != nullptr);
    PropraAdres<K> rezulto = formovu(datumo->rezulto);
    datumo.reset();
    eligu formovu(*rezulto);
}

#endif //KOMUNA_PROMESO_HPP
