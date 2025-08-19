//
// Created by 周春阳 on 2025/8/18.
//
#include <iostream>
#include "Banana/Application.h"

namespace Banana {
    Application::Application() = default;

    Application::~Application() = default;

    void Application::Run() {
        std::cout << "Banana Application Run" << std::endl;
    }
}
