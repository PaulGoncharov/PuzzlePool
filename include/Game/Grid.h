#ifndef GRID_H
#define GRID_H

#include <vector>
#include "Game/minigameinterface.h"

using std::size_t;

class Grid
{
public:
    Grid(const size_t& columnsNum, const size_t& rowsNum);
    void initializeCoords(float canvasHeight, float canvasWidth);
    const Rect& getCoord(size_t pos) const;
    const Rect& getNormCoord(size_t pos) const;
    size_t getQuantumHeight() const{return quantumHeight;}
    size_t getQuantumWidth() const{return quantumWidth;}
    size_t getSize() const{ return coords.size();}
private:
    std::vector<Rect> coords;
    std::vector<Rect> normCoords;
    size_t rowsNum;
    size_t columnsNum;
    float quantumHeight;
    float quantumWidth;

    Rect normalizeCoord(const Rect& rect);

};

#endif // GRID_H
