namespace Mxm
{
	namespace Easing {
		inline float easeInQuad(float x) noexcept {
			return x * x;
		}
		inline float easeOutQuad(float x) noexcept {
			return easeInQuad(1.0f - x);
		}

		inline float easeInCubic(float x) noexcept {
			return x * x * x;
		}
		inline float easeOutCubic(float x) noexcept {
			return easeInCubic(1.0f - x);
		}

		inline float easeInQuart(float x) noexcept {
			return x * x * x * x;
		}
		inline float easeOutQuart(float x) noexcept {
			return easeInQuart(1.0f - x);
		}

		inline float easeInSine(float x) noexcept {
			return 1.0f - cosf(x * Consts::HALF_PI);
		}
		inline float easeOutSine(float x) noexcept {
			return sinf(x * Consts::HALF_PI);
		}

		inline float easeExp(float x, float a) noexcept {
			return (1.0f - expf(-x * a)) / (1.0f - expf(-a));
		}

		inline float cosBounceIn(float x, float bounces, float decay) noexcept {
			float cos_val = cosf(x * Consts::PI * bounces);
			return 1.0f - fabsf(cos_val) * powf(1.0f - x, decay);
		}
		inline float cosBounceOut(float x, float bounces, float decay) noexcept {
			return cosBounceIn(1.0f - x, bounces, decay);
		}

		inline float elasticCosBounceIn(float x, float bounces, float decay) noexcept {
			float cos_val = cosf(x * Consts::PI * bounces * 2.0f);
			return 1.0f - cos_val * powf(1.0f - x, decay);
		}
		inline float elasticCosBounceOut(float x, float bounces, float decay) noexcept {
			return elasticCosBounceIn(1.0f - x, bounces, decay);
		}

		inline float smoothstep(float x) noexcept { 
			return x * x * (3.0f - 2.0f * x);
		}

		inline float bezier(float t, float x1, float y1, float x2, float y2) noexcept {
			// ћы ищем все Bx(t_progress) такие, которые равны t, затем просто берем y компоненту этой точки и получаем наше нелинейное врем€
			// ¬ поиске t_progress помогает численный метод Ќьютона (Xn+1 = Xn - f(x) / f'(x)), т.е. Bx(t_progress) = t, приводим к стандартному виду: Bx(t_progress) - t = 0
			// ѕодставл€ем: t_progress_new = t_progress_old - (Bx(t_progress_old) - t) / Bx'(t_progress_old)
			float startX = 0.0f, startY = 0.0f;
			float endX = 1.0f, endY = 1.0f;

			auto sx = [=](float st) -> float {
				return (1.0f - st) * (1.0f - st) * (1.0f - st) * startX + 3.0f * st * (1.0f - st) * (1.0f - st) * x1 + 3.0f * st * st * (1.0f - st) * x2 + st * st * st * endX;
				};

			auto sy = [=](float st) -> float {
				return (1.0f - st) * (1.0f - st) * (1.0f - st) * startY + 3.0f * st * (1.0f - st) * (1.0f - st) * y1 + 3.0f * st * st * (1.0f - st) * y2 + st * st * st * endY;
				};

			auto sxd = [=](float st) -> float {
				return (sx(st + Mxm::Consts::EPS) - sx(st - Mxm::Consts::EPS)) / (2.0f * Mxm::Consts::EPS);
				};

			float ty = 0.5f;
			for (int i = 0; i < 8; i++) {
				float f = sx(ty) - t;
				if (fabsf(f) < Mxm::Consts::EPS) break;

				float df = sxd(ty);
				if (fabsf(df) < Mxm::Consts::EPS) break;

				ty = ty - f / df; //df равна sdx, т.к. константа t сокращаетс€ при дифференцировании
			}
			return sy(ty);
		}
	}
}