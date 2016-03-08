#ifndef MIXER_H
#define MIXER_H

#include <vector>

using std::vector;

class Mixer
{
public:
    void operator()(vector<std::size_t>& elementsOrder);
private:
    void swap(vector<std::size_t>::iterator lhs, vector<std::size_t>::iterator rhs);
};

#endif // MIXER_H
