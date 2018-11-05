#ifndef KOMUNA_TORENTOTEXTA_HPP
#define KOMUNA_TORENTOTEXTA_HPP

#include <boost/iostreams/concepts.hpp>
#include <boost/iostreams/stream.hpp>
#include "../Texto.hpp"
#include "../trajtoj/specoj.hpp"
#include "../PropraAdres.hpp"

class AperatoTexta : public boost::iostreams::device<boost::iostreams::seekable, Texto::Ano>
{
    using stream_offset = boost::iostreams::stream_offset;
public:
    AperatoTexta(Texto* texto, ℕ unuaLoko = 0) : texto(texto), loko(unuaLoko) {};
    std::streamsize read(char* celo, std::streamsize maximumaNombro);
    std::streamsize write(const char* fonto, std::streamsize maximumaNombro);
    stream_offset seek(stream_offset diferenco, std::ios::seekdir komenco);
    Texto* texto;
    ℕ loko;
};

using TorentoTexta = boost::iostreams::stream<AperatoTexta>;

#endif //KOMUNA_TORENTOTEXTA_HPP
