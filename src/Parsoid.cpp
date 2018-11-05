
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>
#include "Parsoid.hpp"
#include "komuna/torent/TorentoTexta.hpp"
#include "komuna/Eraro.hpp"

Texto Parsoid::konvertuWikitextonAlHtml(Texto servilo, Texto wikitexto, Texto nomoDePaĝo, bool ĉuDevasNormigi)
{   //-«
    premisu (ne wikitexto.ĉuEnhavas('\"'));
    premisu (ne nomoDePaĝo.ĉuEnhavas('\"'));
    premisu (ne nomoDePaĝo.ĉuEnhavas('\n'));
    
    Texto wikitextoDisenLinifinoj;
    wikitextoDisenLinifinoj.rezervu(wikitexto.grandon() + 32);
    
    for (ℕ i = 0; i < wikitexto.grandon(); i++)
        if (wikitexto[i] == '\n')
            wikitextoDisenLinifinoj += "\\n";
        else wikitextoDisenLinifinoj.enmetu(wikitexto[i]);
        
    Texto postparametro = "{\"wikitext\":\"" + wikitextoDisenLinifinoj + "\",\"body_only\":true,"
                            "\"original\":{\"title\":\"" + nomoDePaĝo + "\"}}"; //»-
    
    if (servilo.ĉuEnhavas("rest_v1")) // malneta, sed labori al ĉi-programo enuigas min, do mi lasas ĝin ĉi-tiel
        servilo += (servilo.ĉuFinasPer("/") ? "" : "/") + nomoDePaĝo;
    
    curlpp::Easy peto;
    std::list<std::string> kapo;
    kapo.push_back("Content-Type: application/json");
    peto.setOpt(new curlpp::options::Url(servilo.STL()));
    peto.setOpt(new curlpp::options::HttpHeader(kapo));
    peto.setOpt(new curlpp::options::PostFields(postparametro.STL()));
    peto.setOpt(new curlpp::options::PostFieldSize(postparametro.grandon()));
    Texto html;
    TorentoTexta torento(&html);
    
    try
    {
        torento << peto << std::endl;
    }
    catch (curlpp::RuntimeError& e)
    {
        throw Eraro("Konverti wikitexton «" + wikitexto + "» al HTML malsukcesis.", e.what());
    }
    
    if (ĉuDevasNormigi)
        for (const auto& esprimo : esprimoj)
            html = html.ŝanĝuTextonPerRegex(esprimo.first, esprimo.second);
        
    eligu html;
}

Nenio Parsoid::pravalorizuEsprimojn()
{
    esprimoj =
            {{std::regex("\n"),                                                                               " "},
             {std::regex("(<h[1-6].*?) id=\"[^\"]*\"([^>]*>)"),                                               "$1$2"},
             {std::regex("<\\/?(?:meta|link)(?: [^\\0-\\cZ\\s\"'>\\/=]+(?:=(?:\"[^\"]*\"|'[^']*'))?)*\\/?>"), ""},
             {std::regex(" (data-mw|data-parsoid|resource|rel|prefix|about|rev|datatype|inlist|"
                         "property|vocab|content|class)=\"[^\"]*\""),                                         ""},
             {std::regex(" (data-mw|data-parsoid|resource|rel|prefix|about|rev|datatype|inlist|"
                         "property|vocab|content|class)=\'[^\']*\'"),                                         ""},
             {std::regex(" typeof=\"[^\"]*\""),                                                               ""},
             {std::regex(" id=\"mw((t\\d+)|([\\w-]{2,}))\""),                                                 ""},
             {std::regex("<span[^>]+about=\"[^\"]*\"[^>]*>"),                                                 ""},
             {std::regex("(\\s)<span>\\s*<\\/span>\\s*"),                                                     "$1"},
             {std::regex("<span>\\s*<\\/span>"),                                                              ""},
             {std::regex("<span>\\s*<\\/span>"),                                                              ""},
             {std::regex("(href=\")(?:\\.?\\.\\/)+"),                                                         "$1"},
             {std::regex("(src=\"[^\"]*?)\\/thumb(\\/[0-9a-f]\\/[0-9a-f]{2}\\/[^\\/]+)\\/[0-9]+px-[^\"\\/]+(?=\")"),
                                                                                                              "$1$2"}};
}
