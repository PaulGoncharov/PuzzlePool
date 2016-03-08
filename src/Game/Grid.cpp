#include "Game/Grid.h"

#include <iostream>
#include <cassert>

Grid::Grid(const size_t& rowsNum, const size_t& columnsNum)
    :coords(columnsNum*rowsNum)
    ,normCoords(columnsNum*rowsNum)
    ,rowsNum(rowsNum)
    ,columnsNum(columnsNum)
    ,quantumHeight(0)
    ,quantumWidth(0)
{
    assert(coords.size());
}

void Grid::initializeCoords(float canvasHeight, float canvasWidth)
{
    quantumHeight = (canvasHeight/rowsNum), quantumWidth = (canvasWidth/columnsNum);
    size_t currElem = 0;
    for (size_t crow = 0; crow < rowsNum; ++crow)
    {
        for (size_t ccol = 0; ccol < columnsNum; ++ccol)
        {
            currElem = ccol+crow*columnsNum;

            coords[currElem].left = ccol * quantumWidth;
            coords[currElem].bottom = crow * quantumHeight;
            coords[currElem].right = (ccol + 1) * quantumWidth;
            coords[currElem].top = (crow + 1) * quantumHeight;

            Rect &rect = coords[currElem];
            normCoords[currElem].left = rect.left / canvasWidth;
            normCoords[currElem].top = (canvasHeight - rect.top) / canvasHeight;
            normCoords[currElem].right = rect.right / canvasWidth;
            normCoords[currElem].bottom = (canvasHeight - rect.bottom) / canvasHeight;;
        }
    }
}

const Rect& Grid::getCoord(size_t pos) const
{
    assert(pos < coords.size());
    return coords[pos];
}

const Rect &Grid::getNormCoord(std::size_t pos) const
{
    assert(pos < normCoords.size());
    return normCoords[pos];
}



