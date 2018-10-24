#ifndef VORTSERCXILO_WORTARESTRO_HPP
#define VORTSERCXILO_WORTARESTRO_HPP

#include "komuna/Eraro.hpp"
#include "komuna/Texto.hpp"
#include "symspell/symspell.h"
#include "komuna/traduko/Linguo.hpp"
#include "Wortaro_wikitext1.hpp"
#include "zipios/zipfile.hpp"
#include "Difino.hpp"
#include "InformoDeWortaro.hpp"

class Eraro_MankasSugestanton : public Eraro
{
public:
    Eraro_MankasSugestanton(Linguo linguo)
            : Eraro("La program ne povis ŝarĝi wortaron.",
                    "La wortarujo mankas sugestanton dipor la linguon «" + linguo.iso639_3 + "».") {}
};

class Eraro_NeRekonitanSpeconDeWortaro : public Eraro
{
public:
    Eraro_NeRekonitanSpeconDeWortaro(Texto dosieroDeWortaro)
            : Eraro("Wortaro «" + dosieroDeWortaro + "» ne ĝustas.") {}
};

class Wortarestro
{
    // Wortarestro ankoraŭ ne subtenas uzi plurajn fontojn samtempe.
public:
    struct Sugesto
    {
        Linguo linguo;
        Texto worto;
        ℕ distanco;
    };
    
    Wortarestro(Texto dosieroDeWortarujo);
    ~Wortarestro();
    Nenio agorduRetejonDeParsoid(const Texto& p_retejoDeParsoid);
    Nenio agorduVolatajnLinguojn(Listo<Paro<Texto, Linguo>> novajLinguoj); // Eraro_MankasSugestanton
    Listo<Linguo> donuŜarĝitajnLinguojn() const;
    Listo<Sugesto> donuSugestojnPor(const Texto& ebleEraraWorto);
    Listo<Sugesto> donuSugestojnPor(const Texto& ebleEraraWorto, const Linguo& linguo);
    Difino donuDifinonDe(const Texto& worto, Linguo linguo);
    InformoDeWortaroj donuInformonDeĈiujWortaroj();
private:
    struct _Wortaro
    {
        _Wortaro() = default;
        _Wortaro(_Wortaro&&) = default;
        _Wortaro(const Linguo& p_linguo, zipios::ZipFile* wortarujo, const Texto& retejoDeParsoid);
        ~_Wortaro();
        _Wortaro& operator=(_Wortaro&&) = default;
        static Texto donuDosieronDe(const Linguo& linguo);
        Linguo linguo;
        PropraAdres<Wortaro> difinoj;
        SymSpell sugestanto;
    };
    
    Nenio kreuProvizoranDosierujon();
    Nenio forprenuProvizoranDosierujon();
    zipios::ZipFile wortarujo;
    Listo<_Wortaro> wortaroj;
    Texto retejoDeParsoid;
    inline static const Texto dosierujo_de_difinoj = "difinoj/";
    inline static const Texto dosierujo_de_sugestantoj = "sugestantoj/";
    inline static const Texto provizora_dosierujo = "./provizoraj dosieroj/";
};

#endif //VORTSERCXILO_WORTARESTRO_HPP
