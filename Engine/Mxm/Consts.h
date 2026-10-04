#ifndef CONSTS_H
#define CONSTS_H

namespace Mxm {
	namespace Consts {
		constexpr float PI = 3.141592653589f;
		constexpr float TWO_PI = PI * 2.0f;
		constexpr float HALF_PI = PI * 0.5f;
		constexpr float QUARTER_PI = PI * 0.25f;
		constexpr float INV_PI = 1.0f / PI;
		constexpr float INV_TWO_PI = 1.0f / TWO_PI;

		constexpr float DEG2RAD = PI / 180.0f;
		constexpr float RAD2DEG = 180.0f / PI;

		constexpr float E = 2.718281828f;
		constexpr float LOG2E = 1.442695022f;   // log2(e)
		constexpr float LOG10E = 0.434294492f;   // log10(e)
		constexpr float LN2 = 0.693147182f;   // ln(2)
		constexpr float LN10 = 2.302585125f;   // ln(10)

		constexpr float PHI = 1.618034005f;
		constexpr float INV_PHI = 0.618034005f;

		constexpr float SQRT2 = 1.414213538f;
		constexpr float INV_SQRT2 = 0.707106769f;
		constexpr float SQRT3 = 1.732050776f;
		constexpr float INV_SQRT3 = 0.577350259f;
		constexpr float SQRT5 = 2.236067977f;

		constexpr float EPS = 0.000001f;
	}
}

#endif // !CONSTS_H
