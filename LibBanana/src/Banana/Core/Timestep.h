//
// Created by 周春阳 on 2025/9/7.
//

#ifndef BANANA_TIMESTEP_H
#define BANANA_TIMESTEP_H

namespace Banana {
    class Timestep {
    public:
        Timestep(float time = 0.0f) : m_Time(time) {
        }

        operator float() const { return m_Time; }

        float GetSeconds() const { return m_Time; }
        float GetMilliseconds() const { return m_Time * 1000.0f; }

    private:
        float m_Time;
    };
}


#endif //BANANA_TIMESTEP_H
