#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H
#include <QSound>

#include "SoundManager/sounddescription.h"

class SoundManager
{
public:
    SoundManager();
    void play(const QString &name);
private:
    QSound player;
};

#endif // SOUNDMANAGER_H
