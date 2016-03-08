#include "Game/Mixer.h"

#include <cstdlib>
#include <ctime>

void Mixer::operator()(vector<std::size_t> &elementsOrder)
{
    std::srand(std::time(nullptr));
    vector<size_t>::iterator begin = elementsOrder.begin();
    std::size_t size = elementsOrder.size();

    for (std::size_t i = 0; i < elementsOrder.size()-1; ++i) {
        std::iter_swap(begin+i, begin+(std::rand() % size));
    }
}

