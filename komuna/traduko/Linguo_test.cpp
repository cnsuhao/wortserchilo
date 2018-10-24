#include <boost/test/unit_test.hpp>
#include <filesystem>
#include "Linguo.hpp"

BOOST_AUTO_TEST_CASE (Linguo_Test)
{
    BOOST_TEST(esperanta_linguo.ĉuNiKonasLinguon());
    BOOST_TEST(esperanta_linguo.provuDoniIso639_2().STL() == "eo");
    BOOST_TEST(esperanta_linguo.donuNomon(angla_linguo).STL() == "Esperanto");
    
    Linguo frs("frs");
    BOOST_TEST(frs.ĉuNiKonasLinguon());
    BOOST_TEST(frs.provuDoniIso639_2().STL() == "");
    BOOST_TEST(frs.donuNomon(angla_linguo).STL() == "Eastern Frisian");
    if (std::filesystem::exists(std::string("./nld/iso_639-2.mo")))
        BOOST_TEST(frs.donuNomon(Linguo("nld")).STL() == "Oost-Fries");
    
    Linguo linguo3("ĉi-linguo nature ne existas");
    BOOST_TEST(ne linguo3.ĉuNiKonasLinguon());
    BOOST_TEST(linguo3.provuDoniIso639_2().STL() == "");
    BOOST_TEST(linguo3.donuNomon(angla_linguo).STL() == linguo3.iso639_3.STL());
}