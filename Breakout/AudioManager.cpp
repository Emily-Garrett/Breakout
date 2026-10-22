#include "AudioManager.h"

AudioManager::AudioManager()
{
	soundBuffers[SoundID::Parry].loadFromFile("sfx/parry.wav");
}

void AudioManager::PlaySound(SoundID id, float pitch)
{
	currentSounds.push_back(sf::Sound());
	currentSounds[currentSounds.size() - 1].setBuffer(soundBuffers[id]);
	currentSounds[currentSounds.size() - 1].setPitch(pitch);
	currentSounds[currentSounds.size() - 1].play();
}

void AudioManager::clearSounds()
{
	currentSounds.erase(std::remove_if(currentSounds.begin(), currentSounds.end(), [](const sf::Sound& sound) {
		return sound.getStatus() == sf::SoundSource::Status::Stopped;
	}), currentSounds.end());
}