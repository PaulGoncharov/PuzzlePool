#ifndef SWAPPINGANIMATION_H
#define SWAPPINGANIMATION_H

#include <iostream>
#include <chrono>

#include "Game/minigameinterface.h"

enum StateMachine {
    wait,
    animate
};

struct Point {
    Point() :x(0), y(0) {}
    float x;
    float y;
};

class Timer
{
public:
    Timer();
    void reset();
    float elapsed() const ;

private:
    typedef std::chrono::high_resolution_clock clock_;
    typedef std::chrono::duration<double, std::ratio<1> > second_;
    std::chrono::time_point<clock_> beg_;
};

//Forward declaration
class Timer;

class SwappingAnimation
{
public:
    SwappingAnimation();
    void start(const Rect &rect1, const Rect &rect2);
    bool inProgress() const;
    //lazy evaluation
    void update();
    void getIntermedPoints(Rect& rect1, Rect& rect2);

private:
    void initStartPoints(const Rect& rect1, const Rect& rect2);
    void calcPoints(Rect &rect1, Rect &rect2);
    int currentState;
    Timer timer;

    float angle;
    float module;
    Rect startRect;
    Rect finalRect;
    Point startPoint;
    Point finalPoint;

    bool isStarted;

    static constexpr float animationTime = 0.5;
};

#endif // SWAPPINGANIMATION_H
