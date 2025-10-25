//
// Created by cyzho on 2025/10/25.
//

#ifndef UUID_H
#define UUID_H
#include <random>


namespace Banana {
    class UUID {
    public:
        UUID();

        UUID(uint64_t uuid);

        UUID(const UUID &) = default;

        operator uint64_t() const {
            return m_UUID;
        }

    private:
        uint64_t m_UUID;
    };
}


#endif //UUID_H
