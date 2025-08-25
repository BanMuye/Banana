//
// Created by 周春阳 on 2025/8/23.
//

#ifndef BANANA_ASSERT_H
#define BANANA_ASSERT_H

#include "Banana/Core/Base.h"
#include "Banana/Core/Log.h"
#include <filesystem>

#ifdef BANANA_ENABLE_ASSERTS

    // Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
    // provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
    #define BANANA_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { BANANA##type##ERROR(msg, __VA_ARGS__); BANANA_DEBUGBREAK(); } }
    #define BANANA_INTERNAL_ASSERT_WITH_MSG(type, check, ...) BANANA_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
    #define BANANA_INTERNAL_ASSERT_NO_MSG(type, check) BANANA_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", BANANA_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

    #define BANANA_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
    #define BANANA_INTERNAL_ASSERT_GET_MACRO(...) BANANA_EXPAND_MACRO( BANANA_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, BANANA_INTERNAL_ASSERT_WITH_MSG, BANANA_INTERNAL_ASSERT_NO_MSG) )

    // Currently accepts at least the condition and one additional parameter (the message) being optional
    #define BANANA_ASSERT(...) BANANA_EXPAND_MACRO( BANANA_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
    #define BANANA_CORE_ASSERT(...) BANANA_EXPAND_MACRO( BANANA_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
    #define BANANA_ASSERT(...)
    #define BANANA_CORE_ASSERT(...)
#endif


#endif //BANANA_ASSERT_H