#pragma once

#include "SFML/Audio.hpp"
#include <map>

class AudioManager
{
public:
	AudioManager();

	enum struct SoundID
	{
		Parry = 0
	};

	void PlaySound(SoundID id, float pitch = 1.f);
	void clearSounds();
private:
	std::map<SoundID, sf::SoundBuffer> _soundBuffers;
	std::vector<sf::Sound> _currentSounds;
};