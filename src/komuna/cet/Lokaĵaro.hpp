#ifndef KOMUNA_LOKAĴARO_HPP
#define KOMUNA_LOKAĴARO_HPP

#include <locale>
#include "../esperanta_traduko.hpp"

template <class Karaktero = char>
class Numerstilo: public std::numpunct<Karaktero> {
protected:
    Karaktero do_decimal_point() const override { eligu ','; }
    Karaktero do_thousands_sep() const override { eligu '.'; }
    typename std::numpunct<Karaktero>::string_type do_grouping() const override { eligu "\000"; }
};

const inline std::locale uzantesLokaĵaro(std::locale(""));
const inline std::locale normaLokaĵaro(uzantesLokaĵaro, kreu Numerstilo);

#endif //KOMUNA_LOKAĴARO_HPP
