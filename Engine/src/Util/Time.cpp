#include <Util/Time.h>

namespace Engine::Util
{
    Time::Time()
        : m_start(Clock::now()), m_prev(m_start), m_deltaSeconds(0.0), m_fps(0.0)
    {
    }

    void Time::Update()
    {
        auto now = Clock::now();
        m_deltaSeconds = std::chrono::duration<double>(now - m_prev).count();
        m_prev = now;

        if (m_deltaSeconds > 0.0)
        {
            m_fps = m_fps * 0.9 + (1.0 / m_deltaSeconds) * 0.1;
        }
    }

    double Time::GetElapsedSeconds() const
    {
        return std::chrono::duration<double>(Clock::now() - m_start).count();
    }
}