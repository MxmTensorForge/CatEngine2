#include "AudioManager.h"
#include "../Core/Logger.h"

AudioManager::AudioManager() {
	ma_result result = ma_engine_init(nullptr, &_engine);
	if (result != MA_SUCCESS) {
		Logger::getInstance().log(LogType::Fatal, "Audio engine failed");
	}

	ma_engine_listener_set_world_up(&_engine, 0, 0, 1, 0);
}
AudioManager::~AudioManager() {
	for (auto& [name, data] : _sounds)
		ma_sound_uninit(&data.sound);
	ma_engine_uninit(&_engine);
}

bool AudioManager::loadFromFile(const std::string& name, const std::string& path, bool repeat) {
	auto [it, inserted] = _sounds.try_emplace(name);
	if (!inserted) {
		return false;
	}

	AudioData& data = it->second;
	ma_result result = ma_sound_init_from_file(&_engine, path.c_str(), 0, nullptr, nullptr, &data.sound);

	if (result != MA_SUCCESS) {
		_sounds.erase(it);
		Logger::getInstance().log(LogType::Fatal, "Audio sound failed");
		return false;
	}

	data._repeat = repeat;
	ma_sound_set_looping(&data.sound, repeat);

	Logger::getInstance().log(LogType::Message, "Sound loaded successfully: " + name);
	return true;
}
void AudioManager::playSound(const std::string& name) {
	auto it = _sounds.find(name);
	if (it != _sounds.end()) {
		ma_sound_seek_to_pcm_frame(&it->second.sound, 0);

		ma_sound_set_spatialization_enabled(&it->second.sound, MA_FALSE);
		ma_sound_start(&it->second.sound);
	}
}
void AudioManager::playSound3D(const std::string& name, const Mxm::Vec3& position) {
	auto it = _sounds.find(name);
	if (it != _sounds.end()) {
		ma_sound_seek_to_pcm_frame(&it->second.sound, 0);
		ma_sound_set_attenuation_model(&it->second.sound, ma_attenuation_model_linear);

		ma_sound_set_spatialization_enabled(&it->second.sound, MA_TRUE);
		ma_sound_set_position(&it->second.sound, position.x, position.y, position.z);

		ma_sound_start(&it->second.sound);
	}
}
void AudioManager::stopSound(const std::string& name) {
	auto it = _sounds.find(name);
	if (it != _sounds.end()) {
		ma_sound_stop(&it->second.sound);
	}
}

void AudioManager::setMinMaxDist(const std::string& name, float min, float max) {
	auto it = _sounds.find(name);
	if (it != _sounds.end()) {
		ma_sound_set_min_distance(&it->second.sound, min);
		ma_sound_set_max_distance(&it->second.sound, max);
	}
}
void AudioManager::setSoundPosition(const std::string& name, const Mxm::Vec3& position) {
	auto it = _sounds.find(name);
	if (it != _sounds.end()) {
		ma_sound_set_spatialization_enabled(&it->second.sound, MA_TRUE);
		ma_sound_set_position(&it->second.sound, position.x, position.y, position.z);
	}
}
void AudioManager::setListener(const Mxm::Vec3& position, const Mxm::Vec3& forward) {
	ma_engine_listener_set_position(&_engine, 0, position.x, position.y, position.z);
	ma_engine_listener_set_direction(&_engine, 0, forward.x, forward.y, forward.z);
}

bool AudioManager::isSoundPlaying(const std::string& name) const noexcept {
	auto it = _sounds.find(name);
	if (it != _sounds.end()) {
		return ma_sound_is_playing(&it->second.sound);
	}
	return false;
}

void AudioManager::setVolume(const std::string& name, float volume) {
	auto it = _sounds.find(name);
	if (it != _sounds.end()) {
		ma_sound_set_volume(&it->second.sound, volume);
	}
}
void AudioManager::setRepeat(const std::string& name, bool repeat) {
	auto it = _sounds.find(name);
	if (it != _sounds.end()) {
		ma_sound_set_looping(&it->second.sound, repeat);
	}
}
