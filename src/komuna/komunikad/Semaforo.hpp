#ifndef WORTSERCXILO_SEMAFORO_HPP
#define WORTSERCXILO_SEMAFORO_HPP

#include <mutex>
#include <condition_variable>
#include "../esperanta_traduko.hpp"

class Semaforo
{
public:
    Semaforo(ℕ p_signaloj = 0) : signaloj(p_signaloj) {}
    
    Nenio atenduSignalon()
    {
        std::unique_lock _ŝloso(ŝloso);
        while (signaloj == 0)
            avertanto.wait(_ŝloso);
        signaloj--;
    }
    
    Buleo provuPreniSignalon()
    {
        std::lock_guard _ŝloso(ŝloso);
        if (ne signaloj)
            eligu malveran;
        signaloj--;
        eligu veran;
    }
    
    Nenio enmetuSignalon()
    {
        std::lock_guard _ŝloso(ŝloso);
        signaloj++;
        avertanto.notify_one();
    }
    
    Buleo ĉuHavasSignalon() const
    {
        std::lock_guard _ŝloso(ŝloso);
        eligu signaloj != 0;
    }
    
private:
    mutable std::mutex ŝloso;
    std::condition_variable avertanto;
    ℕ signaloj = 0;
};

#endif //WORTSERCXILO_SEMAFORO_HPP
