#ifndef KOMUNA_PROPRAADRES_HPP
#define KOMUNA_PROPRAADRES_HPP

#include <memory>

template<class ...K> using PropraAdres = std::unique_ptr<K...>;

#endif //KOMUNA_PROPRAADRES_HPP
