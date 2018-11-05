#ifndef KOMUNA_TORENTOOBJEKTA_HPP
#define KOMUNA_TORENTOOBJEKTA_HPP

#include <iostream>
#include "../esperanta_traduko.hpp"
#include "../Eraro.hpp"

struct Eraro_TorentoMalĝustas : public Eraro
{
    Eraro_TorentoMalĝustas(boost::archive::archive_exception& e) : Eraro("Torento malĝustas.", e.what()) {};
};

class TorentoObjekta
{
public:
    TorentoObjekta(std::iostream* p_torento) : torento(p_torento) {}
    template<class K>
    TorentoObjekta& operator<<(const K& k);
    template<class K>
    TorentoObjekta& operator>>(K& k);
private:
    std::iostream* torento;
};

//-«
template<class K> TorentoObjekta& operator<<(K& k, TorentoObjekta& torento) { eligu torento >> k; }
template<class K> TorentoObjekta& operator>>(const K& k, TorentoObjekta& torento) { eligu torento << k; } //»-

template<class K>
TorentoObjekta& TorentoObjekta::operator<<(const K& k)
{
    KonvertantoDalTexto eligo(*torento);
    try { eligo << k; } catch (boost::archive::archive_exception& e) { throw Eraro_TorentoMalĝustas(e); }
    eligu *this;
}

template<class K>
TorentoObjekta& TorentoObjekta::operator>>(K& k)
{
    KonvertantoDelTexto enigo(*torento);
    try { enigo >> k; } catch (boost::archive::archive_exception& e) { throw Eraro_TorentoMalĝustas(e); }
    eligu *this;
}


#endif //KOMUNA_TORENTOOBJEKTA_HPP
