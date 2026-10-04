#include "Random.h"

#include <random>
#include <chrono>

namespace Random {
	static std::mt19937 rng;
	static bool initialized = false;

	void init(uint32_t seed) {
		rng.seed(seed);
		initialized = true;
	}
	void init() {
		std::random_device dev;
		auto time_seed = static_cast<uint32_t>(std::chrono::high_resolution_clock::now().time_since_epoch().count());

		uint32_t seed = time_seed ^ dev();
		rng.seed(seed);
		initialized = true;
	}

	float range(float min, float max) {
		if (!initialized) init();
		std::uniform_real_distribution<float> dist(min, max);
		return dist(rng);
	}
	float value() {
		return range(0.0f, 1.0f);
	}
	int range(int min, int max) {
		if (!initialized) init();
		std::uniform_int_distribution<int> dist(min, max);
		return dist(rng);
	}
	unsigned int range(unsigned int min, unsigned int max) {
		if (!initialized) init();
		std::uniform_int_distribution<unsigned int> dist(min, max);
		return dist(rng);
	}

	bool flag(float chance) {
		return range(0.0f, 1.0f) < chance;
	}
}
