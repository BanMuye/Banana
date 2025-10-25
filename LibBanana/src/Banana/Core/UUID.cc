//
// Created by cyzho on 2025/10/25.
//

#include "Banana/Core/bapch.h"
#include "UUID.h"

namespace Banana {
    static std::random_device s_RandomDevice;
    static std::mt19937_64 s_Engine(s_RandomDevice());
    static std::uniform_int_distribution<uint64_t> s_UniformDistribution;

    UUID::UUID() : m_UUID(s_UniformDistribution(s_Engine)) {
    }

    UUID::UUID(uint64_t uuid) : m_UUID(uuid) {
    }
}
