//
// Created by 周春阳 on 2025/8/18.
//

#ifndef BANANA_APPLICATION_H
#define BANANA_APPLICATION_H

#include "Core.h"

namespace Banana {
    class API_EXPORT Application {
    public:
        Application();

        virtual ~Application();

        void Run();
    };
}


#endif //BANANA_APPLICATION_H
