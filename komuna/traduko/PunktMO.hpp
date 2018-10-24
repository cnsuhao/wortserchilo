#ifndef WORTSERCXILO_PUNKTMO_HPP
#define WORTSERCXILO_PUNKTMO_HPP

#include "../Texto.hpp"
#include "../Eraro.hpp"
#include "../UnikaroPara.hpp"

// Kutime ĉi-funkcioj ĵetos eraron se la .mo dosiero malĝustas, sed ne ĉiam.
// Exemple se la textparto de la dosiero mankas, ili ne raportos ĝin kaj donos malĝustan rezulton.
Buleo provuPreniTradukonElPunktMO(const Texto& dosiero, const Texto& ŝlosilo, Texto* celo);
UnikaroPara<Texto, Texto> leguTutanPunktMODosieron(const Texto& dosiero);

#endif //WORTSERCXILO_PUNKTMO_HPP
