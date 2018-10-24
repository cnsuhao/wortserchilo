#include <ios>
#include "TorentoTexta.hpp"

std::streamsize AperatoTexta::read(char* celo, std::streamsize maximumaNombro)
{
    std::streamsize rezulto = std::min<std::streamsize>(maximumaNombro, texto->grandon() - loko);
    if (rezulto == 0)
        eligu -1;
    for (ℕ i = 0; i < rezulto; i++)
        celo[i] = (*texto)[loko + i];
    loko += rezulto;
    eligu rezulto;
}

std::streamsize AperatoTexta::write(const char* fonto, std::streamsize maximumaNombro)
{
    ℕ anstataŭigotaNombro = std::min<ℕ>(texto->grandon() - loko, maximumaNombro);
    for (ℕ i = 0; i < anstataŭigotaNombro; i++)
        (*texto)[i + loko] = fonto[i];
    texto->enmetuAntaŭ(texto->postlastan(), fonto + anstataŭigotaNombro, fonto + maximumaNombro);
    loko += maximumaNombro;
    eligu maximumaNombro;
}

AperatoTexta::stream_offset AperatoTexta::seek(AperatoTexta::stream_offset diferenco, std::ios::seekdir komenco)
{
    if (komenco == std::ios_base::cur)
        loko += diferenco;
    else if (komenco == std::ios_base::end)
        loko = diferenco + texto->grandon();
    else if (komenco == std::ios_base::beg)
        loko = diferenco;
    eligu loko;
}