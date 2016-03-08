#ifndef GAME_H
#define GAME_H

#include "Game/minigameinterface.h"
#include "Game/Grid.h"
#include "Game/swappinganimation.h"
#include "SoundManager/soundmanager.h"

#include <memory>

// Forward declaration
class Canvas;

class Game: public MiniGame
{
public:
    explicit Game(Canvas *parent_);
    ~Game();

    virtual void Initialize() override;
    virtual void Click(float x, float y) override;
    virtual bool IsCompleted() const override;
    virtual void Render() const override;

    void restart();
    void showTip();
    void update();

private:

    int canvasWidth;
    int canvasHeight;
    size_t calcElemPos(float x, float y);
    Canvas *canvas;
    std::auto_ptr<Grid> grid;
    std::vector<size_t> elementsOrder;
    std::size_t sortedElCount;
    int selectedElem;
    int firstSelectedElem;
    int secondSelectedElem;
    SwappingAnimation swapAnimation;
    Rect firsAnimRect, secondAnimRect;
    SoundManager soundManager;
};

#endif // GAME_H
