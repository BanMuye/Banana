//
// Created by cyzho on 2025/10/13.
//

#ifndef PLATFORMUTILS_H
#define PLATFORMUTILS_H

#include <string>

namespace Banana {
    class FileDialogs {
    public:
        // return empty string if cancelled
        static std::string OpenFile(const char* filter);
        static std::string SaveFile(const char* filter);
    };
}

#endif //PLATFORMUTILS_H
