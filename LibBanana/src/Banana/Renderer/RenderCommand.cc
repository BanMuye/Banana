//
// Created by 周春阳 on 2025/9/7.
//

#include "Banana/Core/bapch.h"
#include "RenderCommand.h"
#include "Banana/Platform/OpenGL/OpenGLRendererAPI.h"

namespace Banana {
    RendererAPI *RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}
