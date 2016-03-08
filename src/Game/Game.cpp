#include "Game/Game.h"
#include "Game/Mixer.h"
#include "Canvas/Canvas.h"

#include <iostream>
#include <iterator>



MiniGame::~MiniGame(){}

Game::Game(Canvas *parent_)
    :canvas (parent_)
    ,grid(new Grid(cRows, cColumns))
    ,elementsOrder(cRows*cColumns, 0)
    ,sortedElCount(0)
    ,selectedElem(-1)
    ,firstSelectedElem(-1)
    ,secondSelectedElem(-1)
{

}

Game::~Game()
{

}

void Game::Initialize()
{
    canvas->getCanvasSize(canvasWidth,canvasHeight);
    grid->initializeCoords(canvasHeight, canvasWidth);

    for (size_t i = 0; i < elementsOrder.size(); ++i) {
        elementsOrder[i] = i;
    }
    // Mix elements
    Mixer mix;
    mix(elementsOrder);

    std::cout << "elementsOrder after mix" << std::endl;
    copy(elementsOrder.begin(), elementsOrder.end(), std::ostream_iterator<size_t>(std::cout, " "));
    std::cout << std::endl;

    // check if we have sortered elements after mixing
    for (size_t i = 0; i < elementsOrder.size(); ++i) {
        if(elementsOrder[i] == i) {
            sortedElCount++;
        }
    }

    std::cout << "Number of sorted elements " << sortedElCount << std::endl;

    soundManager.play(sounds::startGame);

}

void Game::Click(float x, float y)
{
    size_t elemPos = calcElemPos(x, y);
    std::cout << "elemPos" << elemPos << std::endl;

    // this element are already at its position
    if (elemPos == elementsOrder[elemPos])
    {
        // Do nothing
        return;
    }

    if(swapAnimation.inProgress()) {
        return;
    }

    // if no one element is selected
    if (selectedElem == -1)
    {
        selectedElem = elemPos;
        return;
    }

    // swap elements
    if(static_cast<size_t>(selectedElem) != elemPos) {

        firstSelectedElem = selectedElem;
        secondSelectedElem = elemPos;

        size_t tmp = elementsOrder[elemPos];
        elementsOrder[elemPos] = elementsOrder[selectedElem];
        elementsOrder[selectedElem] = tmp;

        //check additional correctly positioned elements
        if(elementsOrder[elemPos] == elemPos) {sortedElCount++;}
        if(elementsOrder[selectedElem] == static_cast<size_t>(selectedElem)) {sortedElCount++;}

        if(IsCompleted()) {
            soundManager.play(sounds::endGame);
        }

        // we have already swapped elements
        swapAnimation.start(grid->getCoord(secondSelectedElem), grid->getCoord(firstSelectedElem));
    }
    selectedElem = -1;
}

bool Game::IsCompleted() const
{
    return (sortedElCount == elementsOrder.size());
}

void Game::Render() const
{
    Rect screenCoords;
    Rect textureCoords;

    size_t gridSize = grid->getSize();
    int frameBorder = 3;
    int textureId = static_cast<int>(canvas->getTextureID());

    for (size_t i = 0; i < gridSize; ++i)
    {
        // if animate cnange, skip changing parts
        if(swapAnimation.inProgress()) {
            if((static_cast<size_t>(firstSelectedElem) == i) ||
                    (static_cast<size_t>(secondSelectedElem) == i)) {
                continue;
            }
        }

        screenCoords = grid->getCoord(i);
        textureCoords = grid->getNormCoord(elementsOrder[i]);

        if(selectedElem!= -1 && static_cast<size_t>(selectedElem) == i) {
            screenCoords.bottom+=frameBorder;
            screenCoords.top-=frameBorder;
            screenCoords.left+=frameBorder;
            screenCoords.right-=frameBorder;
        }

        ::DrawRect(screenCoords, textureId, textureCoords);

    }

    //draw animated parts
    if(swapAnimation.inProgress()) {
        ::DrawRect(firsAnimRect, textureId,
                   grid->getNormCoord(elementsOrder[firstSelectedElem]));
        ::DrawRect(secondAnimRect, textureId,
                   grid->getNormCoord(elementsOrder[secondSelectedElem]));
    }
}

void Game::restart()
{
    Initialize();
}

void Game::showTip()
{
    // did not have enough time
    soundManager.play(sounds::showTip);
}

void Game::update()
{
    swapAnimation.update();
    swapAnimation.getIntermedPoints(firsAnimRect, secondAnimRect);
}

size_t Game::calcElemPos(float x, float y)
{
    size_t row(0), column(0);
    row = int(y / grid->getQuantumHeight());
    column = int(x / grid->getQuantumWidth());
    return column + row * cColumns;
}

