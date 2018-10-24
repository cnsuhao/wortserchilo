#include <filesystem>
#include <tesseract/genericvector.h>
#include <leptonica/allheaders.h>
#include <tesseract/ocrclass.h>
#include <QtCore/QCoreApplication>
#include "TesseractLeganto.hpp"
#include "komuna/cet/Detruanto.hpp"
#include "komuna/alTexto.hpp"

using namespace tesseract;

TesseractLeganto::TesseractLeganto(UnikaroPara<Texto, Texto> parametroj, const Listo<Texto>& linguoj)
{
    auto serĉrezulto = parametroj.provuTrovi("dosierujo de Tesseract");
    if (ne serĉrezulto.ĉuValidas())
        throw Eraro("Oni ne povas krei Tesseract leganton, ĉar oni mankas la parametron «dosierujo de Tesseract».");
    agorduDosierujonDeTesseract(formovu(serĉrezulto.valoron()));
    reagorduLinguojn(linguoj); // ankaŭ ŝaltas tesseract
}

TesseractLeganto::TesseractLeganto(Texto p_dosierujoDeTesseract, const Listo<Texto>& linguoj)
{
    agorduDosierujonDeTesseract(formovu(p_dosierujoDeTesseract));
    reagorduLinguojn(linguoj); // ankaŭ ŝaltas tesseract
}

RealigoDeBildleganto::Rezulto TesseractLeganto::leguBildon(const Texto& bilddosiero)
{
    Rezulto rezulto;
    rezulto.ĉuEstasValidanRezulton = malveran;
    
    if (provuLegi(bilddosiero))
    {
        rezulto.rezulto = kreuRezulton();
        rezulto.ĉuEstasValidanRezulton = veran;
    }
    else std::cerr << "Tesseract ne povis legi bildon «" << bilddosiero.STL() << "».";
    
    eligu rezulto;
}

Listo<Texto> TesseractLeganto::donuElekteblajnLinguojn() const
{
    Listo<Texto> linguoj;
    GenericVector<STRING> tLinguoj;
    tesseract.GetAvailableLanguagesAsVector(&tLinguoj);
    linguoj.rezervu(tLinguoj.size());
    for (ℕ i = 0; i < tLinguoj.size(); i++)
        linguoj.enmetuNovan(tLinguoj[i].c_str());
    eligu linguoj;
}

Nenio TesseractLeganto::reagorduLinguojn(const Listo<Texto>& linguoj)
{
    Texto linguojEnFormatoDeTesseract = linguoj.ĉuEstasMalplenan() ? "eng" : linguoj[0];
    for (ℕ i = 1; i < linguoj.grandon(); i++)
        linguojEnFormatoDeTesseract += "+" + linguoj[i];
    tesseract.Init(dosierujoDeTesseract.STL().c_str(), linguojEnFormatoDeTesseract.c_str());
}

Nenio TesseractLeganto::kreuBlanknigranVersionDe(const Texto& koloraBildo, const Texto& celdosiero) const
{
    tesseract::TessBaseAPI provizoraTesseract;
    provizoraTesseract.InitForAnalysePage();
    Pix* bildo = pixRead(koloraBildo.c_str());
    provizoraTesseract.SetImage(bildo);
    pixDestroy(&bildo);
    Pix* blanknigraBildo = provizoraTesseract.GetThresholdedImage();
    pixWrite(celdosiero.c_str(), blanknigraBildo, IFF_PNG);
    pixDestroy(&blanknigraBildo);
}

Nenio TesseractLeganto::agorduDosierujonDeTesseract(Texto p_dosierujoDeTesseract)
{
    if (ne std::filesystem::exists(p_dosierujoDeTesseract.STL()))
        throw Eraro("Ŝajnas ke «" + p_dosierujoDeTesseract + "» ne existas.");
    if (ne std::filesystem::is_directory(p_dosierujoDeTesseract.STL()))
        throw Eraro("Tesseract bezonas dosierujon, sed «" + p_dosierujoDeTesseract.STL() + "» ne estas dosierujon.");
    dosierujoDeTesseract = p_dosierujoDeTesseract;
}

Buleo TesseractLeganto::provuLegi(const Texto& bilddosiero)
{
    static TesseractLeganto* aktiva_leganto;
    static std::mutex mutex_aktiva_leganto;
    
    auto _ĉuDevasHalti = [](Nenio*, ℤ) -> Buleo
    {
        QCoreApplication::processEvents();
        eligu aktiva_leganto->ĉuNuligis();
    };
    
    auto _raportuProgreson = [](ℤ p_progreso, ℤ, ℤ, ℤ, ℤ) -> Buleo
    {
        aktiva_leganto->raportuProgreson(ŝanĝu_al<float>(p_progreso) / 100);
        eligu veran;
    };
    
    std::lock_guard<std::mutex> ŝloso(mutex_aktiva_leganto);
    aktiva_leganto = this;
    
    ETEXT_DESC revizanto;
    revizanto.cancel = _ĉuDevasHalti;
    revizanto.progress_callback = _raportuProgreson;
    Pix* bildo = pixRead(bilddosiero.c_str());
    tesseract.SetImage(bildo);
    pixDestroy(&bildo);
    tesseract.SetSourceResolution(70);
    tesseract.SetPageSegMode(tesseract::PSM_SPARSE_TEXT);
    eligu
            tesseract.Recognize(&revizanto) == 0;
}

RezultoDeLegado TesseractLeganto::kreuRezulton()
{
    RezultoDeLegado rezulto;
    PropraAdres<ResultIterator> iter(tesseract.GetIterator());
    
    // GetGlyphConfidences donas al ni malplenan strukturon. Bedaŭrinde mi ne povas demandi kiun parametron ĝi bezonas
    // ĉar la diskutejo de Tesseract bezonas Google konton, kiun mi ne povas fari ĉar tio bezonas telefonnumeron.
    /*do
    {
        std::vector<std::vector<std::pair<const char*, float>>>* certecoj = iter->GetGlyphConfidences();
        char* worto = iter->GetUTF8Text(RIL_WORD);
        Detruanto detruanto([&]() { delete[] worto; });
        std::cout << "WORD " << std::string(worto) << std::endl;
        
        if (certecoj == nullptr)
            saltu_al_sekva;
        
        for (const std::vector<std::pair<const char*, float>>& litero : *certecoj)
        {
            for (const std::pair<const char*, float>& kandidato : litero)
                std::cout << std::string(kandidato.first) << " " << alTexto(kandidato.second).STL();
            std::cout << "-----------" << std::endl;
        }
    } while (iter->Next(RIL_WORD));*/
    
    if (ne iter->IsAtBeginningOf(RIL_WORD))
        eligu rezulto; // Tesseract legis nenion.
    
    do
    {
        if (iter->IsAtBeginningOf(RIL_BLOCK))
            rezulto.frazaroj.enmetuNovan();
        
        LegitaFrazaro& frazaro = *rezulto.frazaroj.lastan();
        
        if (iter->IsAtBeginningOf(RIL_WORD))
        {
            LegitaWorto worto;
            iter->BoundingBox(RIL_WORD, &worto.zono.x, &worto.zono.y, &worto.zono.l, &worto.zono.a);
            worto.zono.l -= worto.zono.x;
            worto.zono.a -= worto.zono.y;
            frazaro.wortoj.enmetu(worto);
        }
        
        LegitaWorto& worto = *frazaro.wortoj.lastan();
        LegitaLitero litero;
        char* utf8 = iter->GetUTF8Text(RIL_SYMBOL);
        litero.verŝajnimajKarakteroj[0] = utf8;
        delete[] utf8;
        litero.certecoj[0] = std::min(255u, ŝanĝu_al<ℕ>(iter->Confidence(RIL_SYMBOL) * (255.f / 100.f)));
        worto.literoj.enmetu(litero);
    } while (iter->Next(RIL_SYMBOL));
    
    eligu rezulto;
}