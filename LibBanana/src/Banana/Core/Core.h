//
// Created by 周春阳 on 2025/8/18.
//

#ifndef BANANA_CORE_H
#define BANANA_CORE_H

#if defined(__GNUC__) || defined(__clang__)
    #define API_EXPORT __attribute__((visibility("default")))
#else
    #define API_EXPORT // 其他编译器（如MSVC）使用 __declspec(dllexport)
#endif



#endif //BANANA_CORE_H
