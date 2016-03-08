#include "SoundManager/soundmanager.h"

SoundManager::SoundManager()
    :player("")
{

}

void SoundManager::play(const QString &name)
{
    player.play(name);
}
