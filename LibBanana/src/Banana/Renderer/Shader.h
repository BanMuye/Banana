//
// Created by 周春阳 on 2025/9/7.
//

#ifndef BANANA_SHADER_H
#define BANANA_SHADER_H
#include <string>


class Shader {
public:
    Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
    ~Shader();

    void Bind();
    void UnBind();

private:
    uint32_t m_RendererID;
};


#endif //BANANA_SHADER_H