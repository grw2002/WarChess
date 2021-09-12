#include "soundinitializer.h"
#include "action.h"
#include <QSoundEffect>

void SoundInitializer::SoundInitial() {
  Attack::m_tapSound = new QSoundEffect();
  Attack::m_tapSound->setSource(QUrl("qrc:/sound/steve/attack.wav"));
  Attack::m_tapSound->setVolume(1);
  Attack::m_tapSound->setLoopCount(QSoundEffect::Infinite);

  Attack::m_zombieSound = new QSoundEffect();
  Attack::m_zombieSound->setSource(QUrl("qrc:/sound/zombie/zombie.wav"));
  Attack::m_zombieSound->setVolume(1);
  Attack::m_zombieSound->setLoopCount(QSoundEffect::Infinite);

  Attack::m_explosionSound = new QSoundEffect();
  Attack::m_explosionSound->setSource(QUrl("qrc:/sound/creeper/explosion.wav"));
  Attack::m_explosionSound->setVolume(1);
  Attack::m_explosionSound->setLoopCount(1);

  Attack::m_creeperSound = new QSoundEffect();
  Attack::m_creeperSound->setSource(QUrl("qrc:/sound/creeper/creeper.wav"));
  Attack::m_creeperSound->setVolume(1);
  Attack::m_creeperSound->setLoopCount(QSoundEffect::Infinite);
}
