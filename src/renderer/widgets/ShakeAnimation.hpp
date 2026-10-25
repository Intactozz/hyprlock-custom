#pragma once

#include <algorithm>
#include <chrono>
#include <cmath>

class CShakeAnimation {
  public:
    void trigger() {
        m_start = Clock::now();
        m_active = true;
    }

    double offset() {
        if (!m_active)
            return 0.0;

        const double elapsed =
            std::chrono::duration<double, std::milli>(
                Clock::now() - m_start
            ).count();

        constexpr double DURATION = 350.0;
        constexpr double AMPLITUDE = 12.0;
        constexpr double OSCILLATIONS = 4.0;
        constexpr double PI = 3.14159265358979323846;

        const double progress =
            std::clamp(elapsed / DURATION, 0.0, 1.0);

        if (progress >= 1.0) {
            m_active = false;
            return 0.0;
        }

        const double envelope =
            (1.0 - progress) * (1.0 - progress);

        return AMPLITUDE * envelope *
               std::sin(progress * OSCILLATIONS * 2.0 * PI);
    }

    bool isActive() const {
        return m_active;
    }

  private:
    using Clock = std::chrono::steady_clock;

    Clock::time_point m_start{};
    bool m_active = false;
};