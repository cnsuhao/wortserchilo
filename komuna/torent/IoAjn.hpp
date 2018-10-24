#ifndef KOMUNA_IOAJN_HPP
#define KOMUNA_IOAJN_HPP

#include "TorentoTexta.hpp"
#include "TorentoObjekta.hpp"

struct IoAjn // almenaŭ ion-ajn torenteblan
{
    static IoAjn* kreuEl(const char* p_texto) { eligu kreuEl(Texto(p_texto)); };
    template<class K>
    static IoAjn* kreuEl(const K& objekto);
    template<class K>
    static IoAjn* kreuEl(K&& objekto);
    static IoAjn* kreuElTextaFormo(const Texto& eligoDeTorentoObjekta);
    virtual ~IoAjn() = default;
    virtual Texto alTextaFormo() const = 0;
    virtual Buleo ĉuEstasTextan() const = 0;
    
    // Se ĉi-IoAjn estas textan sed ĝi ne enhavas ĝustan textan formon de K,
    // ĉi-funkcioj ĵetos Eraro_TorentoMalĝustas
    template<class K>
    Nenio kopiuAl(K* celo) const;
    template<class K>
    Nenio movuAl(K* celo);
};


//


class _PrivatajSubklasojDeIoAjn
{
    friend class IoAjn;
private:
    template<class K>
    struct Objekto : public IoAjn
    {
        Objekto() = default;
        Objekto(K&& p_objekto) : objekto(formovu(p_objekto)) {}
        Objekto(const K& p_objekto) : objekto(p_objekto) {}
        ~Objekto() override = default;
        Texto alTextaFormo() const override;
        Buleo ĉuEstasTextan() const override { eligu malveran; }
        K objekto;
    };
    
    struct IuTextaFormoDeObjekto : public IoAjn
    {
        IuTextaFormoDeObjekto() = default;
        IuTextaFormoDeObjekto(Texto p_texto) : texto(formovu(p_texto)) {}
        ~IuTextaFormoDeObjekto() override = default;
        Texto alTextaFormo() const override { eligu texto; }
        Buleo ĉuEstasTextan() const override { eligu veran; }
        template<class K>
        Nenio metuEn(K* celo) const;
        Texto texto;
    };
};

template <class K>
IoAjn* IoAjn::kreuEl(const K& objekto)
{
    eligu kreu _PrivatajSubklasojDeIoAjn::Objekto<K>(objekto);
}

template <class K>
IoAjn* IoAjn::kreuEl(K&& objekto)
{
    eligu kreu _PrivatajSubklasojDeIoAjn::Objekto<std::decay_t<K>>(formovu(objekto));
}

inline IoAjn* IoAjn::kreuElTextaFormo(const Texto& eligoDeTorentoObjekta)
{
    eligu kreu _PrivatajSubklasojDeIoAjn::IuTextaFormoDeObjekto(eligoDeTorentoObjekta);
}

template<class K>
Nenio IoAjn::kopiuAl(K* celo) const
{
    using Privataj = _PrivatajSubklasojDeIoAjn;
    if (ĉuEstasTextan())
        ŝanĝu_al<const Privataj::IuTextaFormoDeObjekto*>(this)->metuEn<K>(celo);
    else *celo = ŝanĝu_al<const typename Privataj::Objekto<K>*>(this)->objekto;
}

template<class K>
Nenio IoAjn::movuAl(K* celo)
{
    using Privataj = _PrivatajSubklasojDeIoAjn;
    if (ĉuEstasTextan())
        ŝanĝu_al<Privataj::IuTextaFormoDeObjekto*>(this)->metuEn<K>(celo);
    else *celo = formovu(ŝanĝu_al<typename Privataj::Objekto<K>*>(this)->objekto);
}

template<class K>
Texto _PrivatajSubklasojDeIoAjn::Objekto<K>::alTextaFormo() const
{
    Texto texto;
    TorentoTexta torentoTexta(&texto);
    TorentoObjekta torentoObjekta(&torentoTexta);
    torentoObjekta << objekto;
    torentoTexta.flush();
    eligu texto;
}

template<class K>
Nenio _PrivatajSubklasojDeIoAjn::IuTextaFormoDeObjekto::metuEn(K* celo) const
{
    Texto _texto = texto; // Mi estas tro pigran por fari apartajn istream torentojn kiuj funkcius kun neŝanĝeblaĵoj.
    TorentoTexta torentoTexta(&_texto);
    TorentoObjekta torentoObjekta(&torentoTexta);
    torentoObjekta >> *celo;
}

#endif //KOMUNA_IOAJN_HPP
