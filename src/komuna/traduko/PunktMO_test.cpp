#include <boost/test/unit_test.hpp>
#include "PunktMO.hpp"

BOOST_AUTO_TEST_CASE (PunktMO_Test)
{
    UnikaroPara<Texto, Texto> valoroj = leguTutanPunktMODosieron("./test/iso_639-2.mo");
    BOOST_TEST(valoroj.grandon() > 100);
    
    for (auto& paro : valoroj)
    {
        BOOST_TEST(ne paro.second.ĉuEstasMalplenan());
        Texto celo;
        BOOST_TEST(provuPreniTradukonElPunktMO("./test/iso_639-2.mo", paro.first, &celo));
        BOOST_TEST((celo == paro.second));
    }
}
