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

        friend bool operator==(const UUID &lhs, const UUID &rhs) {
            return lhs.m_UUID == rhs.m_UUID;
        }

        friend bool operator!=(const UUID &lhs, const UUID &rhs) {
            return !(lhs == rhs);
        }

        friend std::size_t hash_value(const UUID &obj) {
            std::size_t seed = 0x6BA0CBAC;
            seed ^= (seed << 6) + (seed >> 2) + 0x5704564D + static_cast<std::size_t>(obj.m_UUID);
            return seed;
        }

    private:
        uint64_t m_UUID;
    };
}

namespace std {
    template<>
    struct hash<Banana::UUID> {
        size_t operator()(const Banana::UUID &uuid) const {
            return hash_value(uuid);
        }
    };
}


#endif //UUID_H
