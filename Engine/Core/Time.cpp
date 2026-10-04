#include "Time.h"

#include <SDL3/SDL.h>

Time::TimePoint Time::_lastTime = Time::Clock::now();

float Time::_deltaTime = 0;
bool Time::_firstFrame = true;

float Time::_accumulator = 0;
float Time::_physicsAlpha = 0;

unsigned int Time::_frameCount = 0;
unsigned int Time::_fps = 0;
float Time::_fpsTimer = 0;

std::unordered_map<std::string, Time::Record> Time::_records;

void Time::update() noexcept {
    auto currentTime = Clock::now();
    
    if (!_firstFrame) {
        _deltaTime = std::chrono::duration<float>(currentTime - _lastTime).count(); 
    }
    else {
        _firstFrame = false;
        _deltaTime = 0.0f;
    }

    _lastTime = currentTime;

    _frameCount++;
    _fpsTimer += _deltaTime;
    if (_fpsTimer >= 1.0f) {
        _fps = _frameCount;
        
        _fpsTimer = 0.0f;
        _frameCount = 0;
    }
}

float Time::deltaTime() noexcept {
    return _deltaTime;
}
float Time::fixedDeltaTime() noexcept {
    return _fixedDeltaTime;
}
float Time::accumulator() noexcept {
    return _accumulator;
}
float Time::physicsAlpha() noexcept {
    return _physicsAlpha;
}

unsigned int Time::fps() noexcept {
    return _fps;
}

void Time::begin(const std::string& tag) {
    auto& rec = _records[tag];
    rec.start = Clock::now();
    rec.running = true;
}
void Time::end(const std::string& tag) {
    auto it = _records.find(tag);
    if (it == _records.end() || !it->second.running) return;

    auto now = Clock::now();
    it->second.duration = std::chrono::duration<double, std::milli>(now - it->second.start).count();
    it->second.running = false;
}

double Time::get(const std::string& tag) {
    auto it = _records.find(tag);
    if (it == _records.end()) return 0.0;
    return it->second.duration;
}
