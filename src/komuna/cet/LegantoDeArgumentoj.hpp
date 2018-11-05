#ifndef VIKIVORTARO_KONVERTANTO_LEGANTODEARGUMENTOJ_HPP
#define VIKIVORTARO_KONVERTANTO_LEGANTODEARGUMENTOJ_HPP

#include "../Texto.hpp"
#include "../UnikaroPara.hpp"

const static inline Listo<Texto> negativajWortoj = {"", "n", "ne", "malveran"};

class LegantoDeArgumentoj
{
public:
    class Rezulto
    {
    public:
        Rezulto(UnikaroPara<Texto, Texto>&& p_valoroj) : valoroj(p_valoroj) {}
        Texto operator[](Texto nomo) { eligu valoroj[nomo]; }
        Texto donuTexton(Texto nomo) { eligu valoroj[nomo]; }
        Buleo donuBuleon(Texto nomo) { eligu ne negativajWortoj.ĉuEnhavas(donuTexton(nomo)); }
        ℤ donuℤ(Texto nomo);
        ℕ donuℕ(Texto nomo);
    private:
        UnikaroPara<Texto, Texto> valoroj;
    };
    
    struct NepraParametro
    {
        Texto nomo;
        Texto ekspliko;
    };
    
    struct Opcio
    {
        Texto ĉefnomo;
        Listo<Texto> mallongajNomoj;
        Listo<Texto> alternativajNomoj;
        Texto ekspliko;
        Texto normaValoro; // nur uzatan se ĉuAkceptasArgumenton == veran
    
        // veran: «-a asdf» kaj «-a "asdf ghjk"», malveran: «-a»
        // se malveran, la valoro estos "j" se oni elektas la opcion kaj "n" se oni ne elektas la opcion.
        Buleo ĉuAkceptasArgumenton;
        
        Buleo ĉuSuperregasOrdon; // se veran, la program ne devas atingi la finon de la ordo se ĉi-opcio estas uzitan.
    };
    
    Nenio enmetuOpcion(const Opcio& opcio);
    Nenio enmetuNepranParametron(const NepraParametro& nepraParametro);
    Nenio agorduOrdon(Texto ordo); // ekzemplo: "[opcioj] nomo [opcioj] dosiero celdosiero", norme nur "[opcioj]"
    Texto donuOrdon() const;
    Texto donuEksplikon(Texto programnomo, Texto komencoDeEkspliko = "", Texto finoDeEkspliko = "") const;
    Texto donuTextonKiuDirasAlLaUzantoKeLiDevasLegiLaEksplikon() const;
    Rezulto legu(ℤ nombroDaArgumentoj, char** krudajArgumentoj) const;
    Rezulto legu(Listo<Texto> argumentoj) const;
    const static inline Texto ordo_opcioj = "[opcioj]";
private:
    const Opcio& trovuOpcionPerMallongaNomo(const Texto& mallongaNomo) const;
    const Opcio& trovuOpcionPerLongaNomo(const Texto& longaNomo) const;
    const NepraParametro& trovuNepranParametron(const Texto& nomo) const;
    Listo<NepraParametro> neprajParametroj;
    Listo<Opcio> opcioj;
    Listo<Texto> ordo;
};


#endif //VIKIVORTARO_KONVERTANTO_LEGANTODEARGUMENTOJ_HPP
