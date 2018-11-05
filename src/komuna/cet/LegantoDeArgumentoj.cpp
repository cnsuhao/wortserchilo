#include "LegantoDeArgumentoj.hpp"
#include "../Eraro.hpp"
#include "../trajtoj/numero.hpp"
#include "../alTexto.hpp"

ℤ LegantoDeArgumentoj::Rezulto::donuℤ(Texto nomo)
{
    ℤ rezulto;
    try
    {
        rezulto = std::stoi(donuTexton(nomo).STL());
    }
    catch (std::invalid_argument& e)
    {
        throw Eraro("Parametro " + nomo + " ne ĝustas.",
                    "Ĝi devas esti entjeron, sed ĝies valoron estas " + donuTexton(nomo));
    }
    catch (std::out_of_range& e)
    {
        throw Eraro("Parametro " + nomo + " ne ĝustas.",
                    "La program nur povas trakti numerojn pli grandajn ol " + alTexto(minimumDe<ℤ>)
                    + " kaj malpli grandajn ol " + alTexto(maximumDe<ℤ>) + ". Vi donis " + donuTexton(nomo) + ".");
    }
    eligu rezulto;
}

ℕ LegantoDeArgumentoj::Rezulto::donuℕ(Texto nomo)
{
    ℤ rezulto = donuℤ(nomo);
    if (rezulto < 0)
        throw Eraro("Parametro " + nomo + " ne ĝustas.",
                    "Ĝi devas esti positivan, sed vi donis " + alTexto(rezulto) + ".");
    eligu rezulto;
}

Nenio LegantoDeArgumentoj::enmetuOpcion(const LegantoDeArgumentoj::Opcio& opcio)
{
    premisu (ne opcio.ĉefnomo.ĉuEnhavas(' '));
    for (const Texto& nomo : opcio.alternativajNomoj)
        premisu (ne nomo.ĉuEnhavas(' '));
    for (const Texto& nomo : opcio.mallongajNomoj)
        premisu (ne nomo.ĉuEnhavas(' ') kaj ne nomo.ĉuKomencasPer("-"));
    opcioj.enmetu(opcio);
}

Nenio LegantoDeArgumentoj::enmetuNepranParametron(const LegantoDeArgumentoj::NepraParametro& nepraParametro)
{
    neprajParametroj.enmetu(nepraParametro);
}

Nenio LegantoDeArgumentoj::agorduOrdon(Texto p_ordo)
{
    ordo = Listo<Texto>();
    
    Buleo ĉuEstasDenCiton = malveran;
    ℕ komencoDeWorto = 0;
    
    for (ℕ i = 0; i < p_ordo.grandon(); i++)
    {
        if (p_ordo[i] == '"')
            ĉuEstasDenCiton = ne ĉuEstasDenCiton;
        else if (p_ordo[i] == ' ' kaj ne ĉuEstasDenCiton)
        {
            if (komencoDeWorto != i)
                ordo.enmetu(p_ordo.donuPartonInter(komencoDeWorto, i));
            komencoDeWorto = i + 1;
        }
    }
    
    ordo.enmetu(p_ordo.donuPartonInter(komencoDeWorto, p_ordo.grandon()));
}

Texto LegantoDeArgumentoj::donuOrdon() const
{
    if (ordo.ĉuEstasMalplenan())
        eligu "";
    Texto rezulto = ordo[0];
    for (ℕ i = 1; i < ordo.grandon(); i++)
        rezulto += " " + ordo[i];
    eligu rezulto;
}

Texto LegantoDeArgumentoj::donuEksplikon(Texto programnomo, Texto komencoDeEkspliko, Texto finoDeEkspliko) const
{
    Texto helptexto = "Uzu ĉi-tiel:  " + programnomo + " " + donuOrdon() + "\n\n" + komencoDeEkspliko + "\n";
    
    if (ne neprajParametroj.ĉuEstasMalplenan())
    {
        helptexto += "\nNormaj parametroj:\n";
        
        for (const NepraParametro& parametro : neprajParametroj)
            helptexto += "  " + parametro.nomo + "\n    " + parametro.ekspliko + "\n";
    }
    
    if (ne opcioj.ĉuEstasMalplenan())
    {
        helptexto += "\nOpcioj:\n";
    
        for (const Opcio& opcio : opcioj)
        {
            helptexto += "  ";
            for (const Texto& nomo : opcio.mallongajNomoj)
                helptexto += "-" + nomo + ", ";
            for (const Texto& alternativa : opcio.alternativajNomoj)
                helptexto += "--" + alternativa + ", ";
            helptexto += "--" + opcio.ĉefnomo;
            if (opcio.ĉuAkceptasArgumenton)
                helptexto += " \"" + opcio.normaValoro + "\"";
            helptexto += "\n    " + opcio.ekspliko + "\n";
        }
    }
    
    helptexto += "\n" + finoDeEkspliko;
    eligu helptexto;
}

Texto LegantoDeArgumentoj::donuTextonKiuDirasAlLaUzantoKeLiDevasLegiLaEksplikon() const
{
    eligu "Uzu parametron «-h» por vidi eksplikon de ĉi-programo.";
}

LegantoDeArgumentoj::Rezulto LegantoDeArgumentoj::legu(ℤ nombroDaArgumentoj, char** krudajArgumentoj) const
{
    Listo<Texto> argumentoj;
    for (ℤ i = 0; i < nombroDaArgumentoj; i++)
        argumentoj.enmetuNovan(krudajArgumentoj[i]);
    eligu legu(argumentoj);
}

LegantoDeArgumentoj::Rezulto LegantoDeArgumentoj::legu(Listo<Texto> argumentoj) const
{
    UnikaroPara<Texto, Texto> rezulto;
    ℕ lokoDenOrdo = 0;
    Buleo ĉuIuOpcioSuperregisOrdon = malveran;
    
    if (ordo.ĉuEstasMalplenan() kaj ne argumentoj.ĉuEstasMalplenan())
        throw Eraro("Ĉi-program ne akceptas iujn-ajn argumentojn.");
    
    for (const Opcio& opcio : opcioj)
        rezulto[opcio.ĉefnomo] = opcio.normaValoro;
    
    for (ℕ i = 1; i < argumentoj.grandon();)
    {
        const Texto& argumento = argumentoj[i];
        
        auto traktuMalnepranArgumenton = [&]()
        {
            const NepraParametro& nepraParametro = trovuNepranParametron(ordo[lokoDenOrdo]);
            
            if (lokoDenOrdo == ordo.grandon() - 1)
            {
                Texto valoro = argumento;
                for (ℕ j = i + 1; j < argumentoj.grandon(); j++)
                    valoro += " " + argumentoj[j];
                rezulto[nepraParametro.nomo] = valoro;
                i = argumentoj.grandon();
            }
            else
            {
                rezulto[nepraParametro.nomo] = argumento;
                i++;
                lokoDenOrdo++;
            }
        };
        
        auto _traktuOpcion = [&](const Opcio& opcio)
        {
            if (opcio.ĉuAkceptasArgumenton)
            {
                if (i == argumentoj.grandon() - 1)
                    throw Eraro("«" + argumento + "» atendis argumenton, sed ne trovis iun");
                rezulto[opcio.ĉefnomo] = argumentoj[++i];
            }
            else rezulto[opcio.ĉefnomo] = "j";
            
            if (opcio.ĉuSuperregasOrdon)
                ĉuIuOpcioSuperregisOrdon = veran;
            
            ++i;
        };
        
        auto traktuLonganOpcion = [&]()
        {
            Texto longaNomo = argumento.donuPartonInter(2, argumento.grandon());
            _traktuOpcion(trovuOpcionPerLongaNomo(longaNomo));
        };
        
        auto traktuMallonganOpcion = [&]()
        {
            Texto mallongaNomo = argumento.donuPartonInter(1, argumento.grandon());
            _traktuOpcion(trovuOpcionPerMallongaNomo(mallongaNomo));
        };
        
        auto traktuFinonDeOpcioj = [&]()
        {
            if (lokoDenOrdo == ordo.grandon() - 1)
                throw Eraro("«" + argumento + "» ne estas opcion.", "La program atendis nur opciojn ĉe ĉi-loko.");
            lokoDenOrdo++;
        };
        
        
        if (ordo[lokoDenOrdo] != ordo_opcioj)
            traktuMalnepranArgumenton();
        else if (argumento.ĉuKomencasPer("--"))
            traktuLonganOpcion();
        else if (argumento.ĉuKomencasPer("-"))
            traktuMallonganOpcion();
        else
            traktuFinonDeOpcioj();
    }
    
    if (lokoDenOrdo < ordo.grandon() - 1 kaj ne ĉuIuOpcioSuperregisOrdon)
        throw Eraro("La program bezonas la argumenton «" + ordo[lokoDenOrdo + 1] + "».");
        
    eligu Rezulto(formovu(rezulto));
}

const LegantoDeArgumentoj::Opcio& LegantoDeArgumentoj::trovuOpcionPerMallongaNomo(const Texto& mallongaNomo) const
{
    for (const Opcio& opcio : opcioj)
        if (opcio.mallongajNomoj.ĉuEnhavas(mallongaNomo))
            eligu opcio;
    throw Eraro("La program ne havas opcion «-" + mallongaNomo + "».");
}

const LegantoDeArgumentoj::Opcio& LegantoDeArgumentoj::trovuOpcionPerLongaNomo(const Texto& longaNomo) const
{
    for (const Opcio& opcio : opcioj)
        if (opcio.ĉefnomo == longaNomo aŭ opcio.alternativajNomoj.ĉuEnhavas(longaNomo))
            eligu opcio;
    throw Eraro("La program ne havas opcion «--" + longaNomo + "».");
}

const LegantoDeArgumentoj::NepraParametro& LegantoDeArgumentoj::trovuNepranParametron(const Texto& nomo) const
{
    for (const NepraParametro& nepraParametro : neprajParametroj)
        if (nepraParametro.nomo == nomo)
            eligu nepraParametro;
    throw Eraro("La program malĝustas.", "La ordo de parametroj enhavas neekzistantan nepran parametron.");
}
