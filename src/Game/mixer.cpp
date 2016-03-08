#include "Game/Mixer.h"

#include <algorithm>    // std::shuffle
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock

void Mixer::operator()(vector<std::size_t> &elementsOrder)
{
    // obtain a time-based seed:
      unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    std::shuffle (elementsOrder.begin(), elementsOrder.end(),
                    std::default_random_engine(seed));
}

