#ifndef TIME_H
#define TIME_H

#include <chrono>
#include <unordered_map>
#include <string>

class Time final
{
private:
	static float _deltaTime;
	static inline constexpr float _fixedDeltaTime = 1.0f / 60.0f;

	static bool _firstFrame;

	static float _accumulator;
	static float _physicsAlpha;

	static unsigned int _frameCount;
	static unsigned int _fps;
	static float _fpsTimer;

	using Clock = std::chrono::high_resolution_clock;
	using TimePoint = std::chrono::time_point<Clock>;
	struct Record
	{
		TimePoint start;
		double duration = 0.0;
		bool running = false;
	};
	static std::unordered_map<std::string, Record> _records;

	static TimePoint _lastTime;

	static void update() noexcept;

	friend class Application;
public:
	Time() = delete;
	~Time() = delete;

	static float deltaTime() noexcept;
	static float fixedDeltaTime() noexcept;
	static float accumulator() noexcept;
	static float physicsAlpha() noexcept;
	static unsigned int fps() noexcept;

	static void begin(const std::string& tag);
	static void end(const std::string& tag);

	static double get(const std::string& tag);
};

#endif
