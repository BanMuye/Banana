//
// Created by 周春阳 on 2025/8/18.
//

#ifndef BANANA_CORE_H
#define BANANA_CORE_H


#define GLM_ENABLE_EXPERIMENTAL

#if defined(__GNUC__) || defined(__clang__)
    #define API_EXPORT __attribute__((visibility("default")))
#else
    #define API_EXPORT // 其他编译器（如MSVC）使用 __declspec(dllexport)
#endif

#ifdef BANANA_DEBUG
    #define BANANA_ENABLE_ASSERTS
#endif


#endif //BANANA_CORE_H
