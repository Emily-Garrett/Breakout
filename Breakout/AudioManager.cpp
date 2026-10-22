#include "AudioManager.h"

AudioManager::AudioManager()
{
	_soundBuffers[SoundID::Parry].loadFromFile("sfx/parry.wav");
}

void AudioManager::PlaySound(SoundID id, float pitch)
{
	_currentSounds.push_back(sf::Sound());
	_currentSounds[_currentSounds.size() - 1].setBuffer(_soundBuffers[id]);
	_currentSounds[_currentSounds.size() - 1].setPitch(pitch);
	_currentSounds[_currentSounds.size() - 1].play();
}

void AudioManager::clearSounds()
{
	_currentSounds.erase(std::remove_if(_currentSounds.begin(), _currentSounds.end(), [](const sf::Sound& sound) {
		return sound.getStatus() == sf::SoundSource::Status::Stopped;
	}), _currentSounds.end());
}