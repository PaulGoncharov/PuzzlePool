#ifndef MIXER_H
#define MIXER_H

#include <vector>

using std::vector;

class Mixer
{
public:
    void operator()(vector<std::size_t>& elementsOrder);
};

#endif // MIXER_H
