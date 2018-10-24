#include <QTextCodec>
#include <yaml-cpp/yaml.h>
#include "Wortserchilo.hpp"
#include "TesseractLeganto.hpp"
#include "Ekranbildo.hpp"
#include "komuna/cet/alBuleo.hpp"

using Parametrujo = UnikaroPara<Texto, Texto>;
Q_DECLARE_METATYPE(Difino)
Q_DECLARE_METATYPE(Texto)
Q_DECLARE_METATYPE(Parametrujo)
Q_DECLARE_METATYPE(Linguo)
Q_DECLARE_METATYPE(RezultoDeLegado)
Q_DECLARE_METATYPE(LegitaWorto)
Q_DECLARE_METATYPE(Vektor2D<ℤ>)
Q_DECLARE_METATYPE(Listo<Texto>);
Q_DECLARE_METATYPE(DividataAdres<Promeso<Listo<Texto>>>);

Wortserchilo::~Wortserchilo()
{
    if (ŝarĝantaFadeno.joinable())
        ŝarĝantaFadeno.join();
}

ℤ Wortserchilo::komencu(ℤ nombroDaArgumentoj, char** argumentoj)
{
    programo.reset(kreu QApplication(nombroDaArgumentoj, argumentoj));
    QCoreApplication::setOrganizationName("Mi");
    QCoreApplication::setApplicationName("Wortserĉilo");
    QCoreApplication::setApplicationVersion("0");
    setlocale(LC_ALL, "C");
    qRegisterMetaType<Difino>();
    qRegisterMetaType<Texto>();
    qRegisterMetaType<RezultoDeLegado>();
    qRegisterMetaType<LegitaWorto>();
    qRegisterMetaType<Vektor2D<ℤ>>();
    qRegisterMetaType<Listo<Texto>>();
    qRegisterMetaType<DividataAdres<Promeso<Listo<Texto>>>>();
    
    programo->setStyleSheet(ŝarĝuStilsjablonon().QT());
    
    ĉeffenestro.reset(kreu Cheffenestro());
    wortarestro.reset(kreu Wortarestro("./difinoj.zip"));
    ĉieajKlavligoj = kreu UGlobalHotkeys(ĉeffenestro.get());
    ĉieajKlavligoj->setObjectName("ĉieajKlavligoj");
    ĉieajKlavligoj->hide();
    
    connect(ĉieajKlavligoj, &UGlobalHotkeys::activated, [this](size_t klavnumero)
    {
        if (klavnumero == legu_che_kursoro)
            montruDifinojnDeWortoCheKursoro();
        else if (klavnumero == legu_el_posho)
            montruDifinojnDeWortoEnPosho();
    });
    
    connect(ĉeffenestro.get(), SIGNAL(kiamVolasDifinojnDe(Texto, bool)),
            this, SLOT(determinuDifinojnDe(Texto, bool)));
    connect(ĉeffenestro.get(), SIGNAL(kiamVolasDifinojnDe(Texto, bool, Linguo)),
            this, SLOT(determinuDifinojnDe(Texto, bool, Linguo)));
    connect(ĉeffenestro.get(), SIGNAL(kiamBezonasBlanknigranVersionDeBildo(Texto, Texto)),
            this, SLOT(kreuBlanknigranVersionDeBildo(Texto, Texto)));
    connect(ĉeffenestro.get(), &Cheffenestro::kiamOniShanghasElektitajnWortarojn,
            this, &Wortserchilo::agorduLinguojnDeWortarestro);
    connect(ĉeffenestro.get(), &Cheffenestro::kiamOniShanghasElektitajnWortarojn,
            this, &Wortserchilo::dirivuBildlegantesLinguojnElElektitajWortaroj);
    connect(ĉeffenestro.get(), &Cheffenestro::kiamOniShanghasElektitajnLinguojnDeBildleganto,
            this, &Wortserchilo::agorduLinguojnDeBildleganto);
    connect(ĉeffenestro->menuoDeAgordoj, &MenuoDeAgordoj::kiamShanghasDosierujonDeTesseract,
            this, &Wortserchilo::provuReagordiDosierujonDeTesseract);
    connect(ĉeffenestro->menuoDeAgordoj, &MenuoDeAgordoj::kiamShanghasKlavligonDeKursoro,
            this, &Wortserchilo::provuReagordiKlavligonDeKursoro);
    connect(ĉeffenestro->menuoDeAgordoj, &MenuoDeAgordoj::kiamShanghasKlavligonDePosho,
            this, &Wortserchilo::provuReagordiKlavligonDePosho);
    connect(ĉeffenestro->menuoDeAgordoj, &MenuoDeAgordoj::kiamShanghasRetejonDeParsoid,
            this, &Wortserchilo::provuReagordiRetejonDeParsoid);
    connect(ĉeffenestro->menuoDeAgordoj, &MenuoDeAgordoj::kiamShanghasGrandonDeBildo,
            this, &Wortserchilo::provuReagordiBildlarghon);
    connect(ĉeffenestro->menuoDeAgordoj, &MenuoDeAgordoj::kiamShanghasChuPreferasUziKopiitajnTextojn,
            [this](Buleo novaValoro) { ĉuUzantoPreferasUziKopiitajnTextojn = novaValoro; });
    connect(ĉeffenestro->menuoDeAgordoj, &MenuoDeAgordoj::kiamShanghasLinguonDeFasado,
            this, &Wortserchilo::provuReagordiLinguonDeFasado);
    
    ĉeffenestro->menuoDeAgordoj->agorduElekteblajnLinguojn(kreuListonDeDisponeblajnLinguojn());
    ĉeffenestro->wortaresLinguoj->agorduElekteblajnWortarojn(wortarestro->donuInformonDeĈiujWortaroj());
    enmetuNormajnAgordojn();
    provuŜarĝiAgordojn(dosiero_de_agordoj);
    if (ne QGuiApplication::clipboard()->supportsSelection())
        ĉeffenestro->menuoDeAgordoj->kaŝuĈuPreferasUziKopiitajnTextojn();
    ĉeffenestro->show();
    ℤ eligotaKodo = programo->exec();
    provuKonserviAgordojn(dosiero_de_agordoj);
    eligu eligotaKodo;
}

Nenio Wortserchilo::montruDifinojnDeWortoCheKursoro()
{
    const static Texto kolora_bildo = Cheffenestro::kolora_bildo;
    
    QPoint kursorloko = QCursor::pos();
    Ortangelo<ℤ> ortangelo(kursorloko.x() - bildlarĝo / 2, kursorloko.y() - bildalto / 2, bildlarĝo, bildalto);
    
    if (std::filesystem::exists(kolora_bildo.STL()) kaj ne std::filesystem::remove(kolora_bildo.STL()))
        std::cerr << "Dosiero «" + kolora_bildo.STL() + "» jam existas kaj ni ne povas forpreni ĝin." << std::endl;
    else if (ne provuKreiBildonDeEkrano(kolora_bildo, ortangelo))
        std::cerr << "Krei ekranbildon malsukcesis." << std::endl;
    else
    {
        ĉeffenestro->reŝarĝuKoloranBildon();
        ĉeffenestro->show();
        ĉeffenestro->raise();
    }
}

Nenio Wortserchilo::montruDifinojnDeWortoEnPosho()
{
    QClipboard* poŝo = QGuiApplication::clipboard();
    Texto worto;
    Buleo ĉuUzasElektitajnTextojn = poŝo->supportsSelection() kaj ne ĉuUzantoPreferasUziKopiitajnTextojn;
    
    if (ĉuUzasElektitajnTextojn)
        worto = poŝo->text(QClipboard::Selection);
    
    if (ne ĉuUzasElektitajnTextojn aŭ worto.ĉuEstasMalplenan())
        worto = poŝo->text(QClipboard::Clipboard);
    
    ĉeffenestro->montruDifinojnDeWorto(worto);
    ĉeffenestro->show();
    ĉeffenestro->raise();
}

Texto Wortserchilo::provuReagordiBildleganton(Texto nomo, UnikaroPara<Texto, Texto> parametroj)
{
    PropraAdres<RealigoDeBildleganto> novaRealigo;
    
    try
    {
        if (nomo == TesseractLeganto::nomo)
            novaRealigo.reset(kreu TesseractLeganto(formovu(parametroj), {}));
    }
    catch (Eraro& eraro)
    {
        eligu eraro.tutaTexto;
    }
    
    if (ne novaRealigo)
        eligu "Ni ne konas iun-ajn leganton kun la nomo «" + nomo + "».";
    
    try
    {
        ĉeffenestro->bildlegantesLinguoj->agorduElekteblajnLinguojnPorBildleganto(
                novaRealigo->donuElekteblajnLinguojn());
        novaRealigo->reagorduLinguojn(ĉeffenestro->bildlegantesLinguoj->donuElektitajnLinguojnPorBildleganto());
    }
    catch (Eraro& eraro)
    {
        eligu "Agordi elekteblajn linguojn de nova Bildleganto malsukcesis: " + eraro.tutaTexto;
    }
    
    bildleganto.reset(); // ĉi-tiel nur unu bildleganto existas samtempe, por ŝpari memoron (qŭankam ni malŝparas memoron alie)
    bildleganto.reset(kreu Bildleganto(formovu(novaRealigo)));
    
    connect(bildleganto.get(), SIGNAL(kiamHavasRezulton(RezultoDeLegado)),
            ĉeffenestro.get(), SLOT(traktuRezultonDeLegado(RezultoDeLegado)));
    connect(ĉeffenestro.get(), SIGNAL(kiamVolasTextonEnBildo(Texto)),
            bildleganto.get(), SLOT(leguDosieron(Texto)));
    connect(ĉeffenestro.get(), SIGNAL(kiamNePluVolasTextonEnBildo()),
            bildleganto.get(), SLOT(nuligu()));
    
    eligu Texto();
}

Texto Wortserchilo::donuNomonDeBildleganto()
{
    if (bildleganto)
        eligu bildleganto->nomon();
    eligu neniu_bildleganto;
}

Nenio Wortserchilo::determinuDifinojnDe(Texto worto, Buleo ĉuEstasExaktan)
{
    determinuDifinojnDe(worto, ĉuEstasExaktan, neniu_linguo);
}

Nenio Wortserchilo::determinuDifinojnDe(Texto worto, Buleo ĉuEstasExaktan, Linguo linguo)
{
    if (prenanto)
    {
        prokrastitaWorto = worto;
        prokrastitaĈuEstasExaktan = ĉuEstasExaktan;
        prokrastitaLinguo = linguo;
    }
    else
    {
        ĉeffenestro->difinujo->komencuTorentonDeDifinoj();
        prenanto.reset(kreu PrenantoDeDifinoj(worto, wortarestro.get(), &mutex_wortarestro, ĉuEstasExaktan, linguo));
        connect(prenanto.get(), SIGNAL(traktuNovanDifinon(Difino)), ĉeffenestro->difinujo, SLOT(enmetuDifinon(Difino)));
        connect(prenanto.get(), SIGNAL(kiamFinis()), this, SLOT(traktuKePreniDifinojnFinis()));
        connect(ĉeffenestro->difinujo, SIGNAL(kiamBezonasPliDifinojn()), prenanto.get(), SLOT(rekomencu()));
        connect(ĉeffenestro->difinujo, SIGNAL(kiamNeBezonasPliDifinojn()), prenanto.get(), SLOT(maldaureHaltu()));
        connect(ĉeffenestro.get(), SIGNAL(kiamNePluVolasDifinojn()), prenanto.get(), SLOT(nuligu()));
        prenanto->komencu();
    }
}

Nenio Wortserchilo::traktuKePreniDifinojnFinis()
{
    prenanto.reset();
    if (prokrastitaLinguo != neniu_linguo)
        determinuDifinojnDe(prokrastitaWorto, prokrastitaĈuEstasExaktan, prokrastitaLinguo);
    else if (ne prokrastitaWorto.ĉuEstasMalplenan())
        determinuDifinojnDe(prokrastitaWorto, prokrastitaĈuEstasExaktan);
    else ĉeffenestro->difinujo->finuTorentonDeDifinoj();
    
    prokrastitaLinguo = neniu_linguo;
    prokrastitaWorto.malplenigu();
}

Nenio Wortserchilo::kreuBlanknigranVersionDeBildo(Texto fontdosiero, Texto celdosiero)
{
    if (bildleganto)
        bildleganto->kreuBlanknigranVersionDe(fontdosiero, celdosiero);
    else kreuBlanknigranVersionDe(fontdosiero, celdosiero);
}

Nenio Wortserchilo::agorduLinguojnDeWortarestro(const Listo<Paro<Texto, Linguo>>& linguoj)
{
    if (prenanto)
        prenanto->nuligu();
    
    if (ŝarĝantaFadeno.joinable())
        ŝarĝantaFadeno.join();
    
    ŝarĝantaFadeno = formovu(std::thread([this, linguoj]() //-«
    { //»-
        std::lock_guard ŝloso(mutex_wortarestro);
        wortarestro->agorduVolatajnLinguojn(linguoj);
    }));
}

Nenio Wortserchilo::agorduLinguojnDeBildleganto(const Listo<Texto>& linguoj)
{
    if (bildleganto)
        bildleganto->reagorduLinguojn(linguoj);
}

Nenio Wortserchilo::provuReagordiDosierujonDeTesseract(const Texto& novaDosierujo, std::exception_ptr* eraro)
{
    if (*eraro)
        eligu;
    
    try
    {
        Texto _eraro = provuReagordiBildleganton("Tesseract", {{"dosierujo de Tesseract", novaDosierujo}});
        if (ne _eraro.ĉuEstasMalplenan())
            *eraro = std::make_exception_ptr(Eraro(_eraro));
    }
    catch (...)
    {
        *eraro = std::current_exception();
    }
}

Nenio Wortserchilo::provuReagordiKlavligonDeKursoro(const Texto& novaKlavligo, std::exception_ptr* eraro)
{
    provuReagordiKlavligon(novaKlavligo, eraro, legu_che_kursoro);
}

Nenio Wortserchilo::provuReagordiKlavligonDePosho(const Texto& novaKlavligo, std::exception_ptr* eraro)
{
    provuReagordiKlavligon(novaKlavligo, eraro, legu_el_posho);
}

Nenio Wortserchilo::provuReagordiRetejonDeParsoid(const Texto& novaRetejo, std::exception_ptr* eraro)
{
    if (*eraro)
        eligu;
    
    try
    {
        std::lock_guard ŝloso(mutex_wortarestro);
        wortarestro->agorduRetejonDeParsoid(novaRetejo);
    }
    catch (...)
    {
        *eraro = std::current_exception();
    }
}

Texto Wortserchilo::ŝarĝuStilsjablonon()
{
    std::ifstream torento("./stilo.qss");
    Texto stilo;
    
    for (char karaktero; torento.get(karaktero).good();)
        stilo += karaktero;
    
    eligu stilo;
}

Listo<Texto> Wortserchilo::kreuListonDeDisponeblajnLinguojn()
{
    Listo<Texto> linguoj;
    for (auto& dosiero : std::filesystem::directory_iterator("./tradukoj"))
        if (dosiero.is_regular_file() kaj dosiero.path().extension().string() == ".qm")
            linguoj.enmetu(dosiero.path().stem().string());
    eligu linguoj;
}

Nenio Wortserchilo::enmetuNormajnAgordojn()
{
    MenuoDeAgordoj* celo = ĉeffenestro->menuoDeAgordoj;
    celo->agorduLinguonDeFasado("epo");
    celo->agorduRetejonDeParsoid("https://en.wiktionary.org/api/rest_v1/transform/wikitext/to/html/");
    celo->agorduKlavligonDeKursoro("Alt+X");
    celo->agorduKlavligonDePoŝo("Alt+C");
    celo->agorduDosierujonDeTesseract("./tessdata");
    celo->agorduGrandonDeBildo("400x100");
    celo->agorduĈuPreferasUziKopiitajnTextojn(malveran);
}

Nenio Wortserchilo::provuŜarĝiAgordojn(const Texto& dosiero)
{
    MenuoDeAgordoj* celo = ĉeffenestro->menuoDeAgordoj;
    
    try
    {
        YAML::Node nodo = YAML::LoadFile(dosiero.STL());
        celo->agorduLinguonDeFasado(nodo["linguo"].as<std::string>());
        celo->agorduRetejonDeParsoid(nodo["retejo de parsoid"].as<std::string>());
        celo->agorduKlavligonDeKursoro(nodo["klavligoj"]["legu ĉe kursoro"].as<std::string>());
        celo->agorduKlavligonDePoŝo(nodo["klavligoj"]["legu el poŝo"].as<std::string>());
        celo->agorduDosierujonDeTesseract(nodo["dosierujo de tesseract"].as<std::string>());
        celo->agorduGrandonDeBildo(nodo["grando de bildo"].as<std::string>());
        celo->agorduĈuPreferasUziKopiitajnTextojn(alBuleo(nodo["ĉu preferas uzi kopiitajn textojn"].as<std::string>()));
        
        for (YAML::Node elektitaWortaro : nodo["elektitaj wortaroj"])
        {
            Texto fonto = elektitaWortaro["fonto"].as<std::string>();
            Linguo linguo(elektitaWortaro["linguo"].as<std::string>());
            if (ĉeffenestro->wortaresLinguoj->ĉuEnhavasWortaron(fonto, linguo))
                ĉeffenestro->wortaresLinguoj->agorduĈuWortaroEstasElektitan(fonto, linguo, veran);
        }
        
        for (YAML::Node subnodo : nodo["elektitaj linguoj de bildleganto"])
        {
            Texto linguo = subnodo.as<std::string>();
            if (ĉeffenestro->bildlegantesLinguoj->donuĈiujnLinguojnPorBildleganto().ĉuEnhavas(linguo))
                ĉeffenestro->bildlegantesLinguoj->agorduĈuLinguoDeBildlegantoEstasElektitan(linguo, veran);
        }
        
        for (YAML::Node koloro : nodo["nigraj koloroj"])
        {
            QColor qKoloro(koloro.as<std::string>().c_str());
            if (qKoloro.isValid())
                ĉeffenestro->enmetuNigranKoloron(qKoloro);
        }
        
        for (YAML::Node koloro : nodo["blankaj koloroj"])
        {
            QColor qKoloro(koloro.as<std::string>().c_str());
            if (qKoloro.isValid())
                ĉeffenestro->enmetuBlankanKoloron(qKoloro);
        }
        
        ĉeffenestro->traktuŜanĝitajnLinguajnAgordojn();
    }
    catch (YAML::Exception& eraro)
    {
        std::cerr << "Ŝarĝi agordojn el «" << dosiero.STL() << "» malsukcesis: " << eraro.what() << std::endl;
    }
}

Nenio Wortserchilo::provuKonserviAgordojn(const Texto& dosiero)
{
    MenuoDeAgordoj* fonto = ĉeffenestro->menuoDeAgordoj;
    
    try
    {
        YAML::Node nodo;
        nodo["linguo"] = fonto->donuLinguon().iso639_3.STL();
        nodo["retejo de parsoid"] = fonto->donuRetejonDeParsoid().STL();
        nodo["klavligoj"]["legu ĉe kursoro"] = fonto->donuKlavligonDeKursoro().STL();
        nodo["klavligoj"]["legu el poŝo"] = fonto->donuKlavligonDePoŝo().STL();
        nodo["dosierujo de tesseract"] = fonto->donuDosierujonDeTesseract().STL();
        nodo["grando de bildo"] = fonto->donuGrandonDeBildo().STL();
        nodo["ĉu preferas uzi kopiitajn textojn"] = fonto->donuĈuPreferasUziKopiitajnTextojn() ? "veran" : "malveran";
        
        YAML::Node elektitajWortaroj = nodo["elektitaj wortaroj"];
        YAML::Node nigrajKoloroj = nodo["nigraj koloroj"];
        YAML::Node elektitajLinguojDeBildleganto = nodo["elektitaj linguoj de bildleganto"];
        YAML::Node blankajKoloroj = nodo["blankaj koloroj"];
        
        for (const Paro<Texto, Linguo>& wortaro : ĉeffenestro->wortaresLinguoj->donuElektitajnWortarojn())
        {
            YAML::Node nodoDeWortaro;
            nodoDeWortaro["linguo"] = wortaro.second.iso639_3.STL();
            nodoDeWortaro["fonto"] = wortaro.first.STL();
            elektitajWortaroj.push_back(nodoDeWortaro);
        }
        
        for (const Texto& linguo : ĉeffenestro->bildlegantesLinguoj->donuElektitajnLinguojnPorBildleganto())
            elektitajLinguojDeBildleganto.push_back(linguo.STL());
        
        for (const QColor& koloro : ĉeffenestro->nigraKolorlisto->donuKolorojn())
            nigrajKoloroj.push_back(koloro.name(QColor::NameFormat::HexRgb).toStdString());
        for (const QColor& koloro : ĉeffenestro->blankaKolorlisto->donuKolorojn())
            blankajKoloroj.push_back(koloro.name(QColor::NameFormat::HexRgb).toStdString());
        
        std::ofstream torento(dosiero.STL());
        torento.exceptions(std::ios::badbit | std::ios::failbit);
        torento << nodo;
    }
    catch (YAML::Exception& eraro)
    {
        std::cerr << "Konservi agordojn en «" << dosiero.STL() << "» malsukcesis: " << eraro.what() << std::endl;
    }
}

Nenio Wortserchilo::provuReagordiBildlarghon(const Texto& novaGrando, std::exception_ptr* eraro)
{
    try
    {
        Texto::Paŝanto paŝanto = novaGrando.provuTrovi("x");
        if (ne paŝanto.ĉuValidas())
            throw Eraro("Formato de nova grando malĝustas.");
        ℕ novaLarĝo = novaGrando.donuPartonInter(0, paŝanto.donuLokon()).alℕ();
        ℕ novaAlto = novaGrando.donuPartonInter(paŝanto.donuLokon() + 1, novaGrando.grandon()).alℕ();
        bildlarĝo = novaLarĝo;
        bildalto = novaAlto;
        ĉeffenestro->agorduBildgrandon(bildlarĝo, bildalto);
    }
    catch (...)
    {
        *eraro = std::current_exception();
    }
}

Nenio Wortserchilo::provuReagordiLinguonDeFasado(const Linguo& novaLinguo, std::exception_ptr* eraro)
{
    try
    {
        ŝarĝuLinguon(novaLinguo);
        ĉeffenestro->preparuTextojn();
        ĉeffenestro->difinujo->preparuTextojn();
        ĉeffenestro->menuoDeAgordoj->preparuTextojn();
        ĉeffenestro->bildlegantesLinguoj->preparuTextojn();
        ĉeffenestro->wortaresLinguoj->preparuTextojn();
        ĉeffenestro->bildlegantesLinguoj->agorduLinguonDeFasado(novaLinguo);
        ĉeffenestro->wortaresLinguoj->agorduLinguonDeFasado(novaLinguo);
        ĉeffenestro->difinujo->provuAgordiTransliteranton(tr("Any-Latn")); // vi povas preterlasi traduki ĉi-tion
    }
    catch (...)
    {
        *eraro = std::current_exception();
    }
}

Nenio Wortserchilo::dirivuBildlegantesLinguojnElElektitajWortaroj(const Listo<Paro<Texto, Linguo>>& linguoj)
{
    const Listo<Texto>& bildlegantesLinguoj = ĉeffenestro->bildlegantesLinguoj->donuĈiujnLinguojnPorBildleganto();
    Listo<Texto> elektitajLinguojDeBildleganto;
    
    for (const Paro<Texto, Linguo>& linguo : linguoj)
        if (bildlegantesLinguoj.ĉuEnhavas(linguo.second.iso639_3))
            elektitajLinguojDeBildleganto.enmetu(linguo.second.iso639_3);
    
    for (const Texto& antaŭeElektitaLinguo : ĉeffenestro->bildlegantesLinguoj->donuElektitajnLinguojnPorBildleganto())
        ĉeffenestro->bildlegantesLinguoj->agorduĈuLinguoDeBildlegantoEstasElektitan(antaŭeElektitaLinguo, malveran);
    for (const Texto& noveElektitaLinguo : elektitajLinguojDeBildleganto)
        ĉeffenestro->bildlegantesLinguoj->agorduĈuLinguoDeBildlegantoEstasElektitan(noveElektitaLinguo, veran);
    
    if (linguoj.ĉuEnhavas("zho", [](const Paro<Texto, Linguo>& a, const Texto& b) { eligu a.second == b; })
        kaj bildlegantesLinguoj.ĉuEnhavas("chi_sim"))
        ĉeffenestro->bildlegantesLinguoj->agorduĈuLinguoDeBildlegantoEstasElektitan("chi_sim", veran);
    
    ĉeffenestro->traktuŜanĝitajnLinguajnAgordojn();
}

Nenio Wortserchilo::provuReagordiKlavligon(const Texto& novaKlavligo, std::exception_ptr* eraro,
                                           Wortserchilo::Klavligo klavligo)
{
    if (*eraro)
        eligu;
    
    try
    {
        ĉieajKlavligoj->unregisterHotkey(klavligo);
        if (ne novaKlavligo.ĉuEstasMalplenan())
            ĉieajKlavligoj->registerHotkey(novaKlavligo.QT(), klavligo);
    }
    catch (...)
    {
        *eraro = std::current_exception();
    }
}

Nenio Wortserchilo::ŝarĝuLinguon(Linguo linguo)
{
    PropraAdres<QTranslator> novaTradukanto(kreu QTranslator);
    QString dosiero = "./tradukoj/" + linguo.iso639_3.QT() + ".qm";
    if (ne novaTradukanto->load(dosiero))
        throw Eraro("Ŝarĝi " + dosiero + " malsukcesis.");
    if (ne programo->installTranslator(novaTradukanto.get()))
        throw Eraro("Instali tradukanton de " + dosiero + " malsukcesis.");
    programo->removeTranslator(tradukanto.get());
    tradukanto = formovu(novaTradukanto);
}