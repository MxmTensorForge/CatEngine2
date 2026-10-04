#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <miniaudio.h>
#include <unordered_map>
#include <string>

#include "../Mxm/Vec3.h"

class AudioManager final
{
private:
	struct AudioData
	{
		ma_sound sound;
		bool _repeat = false;
	};

	ma_engine _engine;
	std::unordered_map<std::string, AudioData> _sounds;

	AudioManager();
	~AudioManager();
public:
	AudioManager(const AudioManager&) = delete;
	AudioManager& operator=(const AudioManager&) = delete;
	AudioManager(AudioManager&&) = delete;
	AudioManager& operator=(AudioManager&&) = delete;

	static AudioManager& getInstance() noexcept {
		static AudioManager manager;
		return manager;
	}

	bool loadFromFile(const std::string& name, const std::string& path, bool repeat = false);
	void playSound(const std::string& name);
	void playSound3D(const std::string& name, const Mxm::Vec3& position);
	void stopSound(const std::string& name);

	void setMinMaxDist(const std::string& name, float min, float max);
	void setSoundPosition(const std::string& name, const Mxm::Vec3& position);
	void setListener(const Mxm::Vec3& position, const Mxm::Vec3& forward);

	bool isSoundPlaying(const std::string& name) const noexcept;

	void setVolume(const std::string& name, float volume);
	void setRepeat(const std::string& name, bool repeat);
};

#endif // !AUDIOMANAGER_H
