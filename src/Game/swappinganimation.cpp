#include "Game/swappinganimation.h"
#include <cmath>
//--------------------------------------------------//
//const float SwappingAnimation::rotateTime = 0.5;
//const float SwappingAnimation::movementTime = 0.5;

// Animation
SwappingAnimation::SwappingAnimation()
    :currentState(StateMachine::wait)
    ,angle(0)
    ,module(0)
    ,isStarted(false)
{

}

void SwappingAnimation::start(const Rect &rect1, const Rect &rect2)
{
    timer.reset();
    currentState = StateMachine::animate;
    initStartPoints(rect1,rect2);
    isStarted = true;
}

void SwappingAnimation::initStartPoints(const Rect &rect1, const Rect &rect2)
{
    startRect = rect1; finalRect = rect2;
    startPoint.y = (rect1.top + rect1.bottom)/2;
    startPoint.x = (rect1.left + rect1.right)/2;

    finalPoint.y = (rect2.top + rect2.bottom)/2;
    finalPoint.x = (rect2.left + rect2.right)/2;

    // angle, module
    module = std::sqrt(std::pow((finalPoint.x - startPoint.x),2) +
                    std::pow((finalPoint.y - startPoint.y),2));
    angle = std::atan2(finalPoint.y - startPoint.y, finalPoint.x - startPoint.x);
}

bool SwappingAnimation::inProgress() const
{
    return isStarted;
}

void SwappingAnimation::getIntermedPoints(Rect &rect1, Rect &rect2)
{
    calcPoints(rect1, rect2);
}

void SwappingAnimation::update()
{
    float t = timer.elapsed();

    if(t > animationTime) {
        currentState = StateMachine::wait;
        isStarted = false;
    }
}

void SwappingAnimation::calcPoints(Rect &rect1, Rect &rect2)
{
    float normalizedCoef, currentModule = 0;
    switch(currentState) {
        case StateMachine::wait:
            return;
            break;
        case StateMachine::animate:
            {
                normalizedCoef = (timer.elapsed())/animationTime;
                currentModule = module*normalizedCoef;
                break;
            }
    }
    Point newCentarlPoint1, newCentarlPoint2;

    float x_offset = currentModule*std::cos(angle);
    float y_offset =currentModule*std::sin(angle);

    newCentarlPoint1.x = startPoint.x + x_offset;
    newCentarlPoint2.x = finalPoint.x - x_offset;
    newCentarlPoint1.y = startPoint.y + y_offset;
    newCentarlPoint2.y = finalPoint.y - y_offset;


    rect1.top = newCentarlPoint1.y + (startRect.top - startRect.bottom)/2;
    rect1.bottom = newCentarlPoint1.y - (startRect.top - startRect.bottom)/2;
    rect1.left = newCentarlPoint1.x - (startRect.right - startRect.left)/2;
    rect1.right = newCentarlPoint1.x + (startRect.right - startRect.left)/2;

    rect2.top = newCentarlPoint2.y + (finalRect.top - finalRect.bottom)/2;
    rect2.bottom = newCentarlPoint2.y - (finalRect.top - finalRect.bottom)/2;
    rect2.left = newCentarlPoint2.x - (finalRect.right - finalRect.left)/2;
    rect2.right = newCentarlPoint2.x + (finalRect.right - finalRect.left)/2;
}

//Timer
Timer::Timer()
    : beg_(clock_::now())
{

}

void Timer::reset()
{
    beg_ = clock_::now();
}

float Timer::elapsed() const
{
    return std::chrono::duration_cast<second_>
                (clock_::now() - beg_).count();
}
