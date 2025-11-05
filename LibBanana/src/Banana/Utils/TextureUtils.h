//
// Created by cyzho on 2025/11/4.
//

#ifndef TEXTUREUTILS_H
#define TEXTUREUTILS_H

#include <vector>
#include <string>
#include <algorithm>
#include <cstring>
#include <glad/glad.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

namespace Banana {
    class TextureSaver {
    public:
        // 保存普通 RGBA 纹理
        static bool SaveTextureToPNG(GLuint textureID, int width, int height, const std::string &filename) {
            glBindTexture(GL_TEXTURE_2D, textureID);

            std::vector<unsigned char> pixels(width * height * 4);
            glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());

            FlipImageY(pixels, width, height, 4);
            int result = stbi_write_png(filename.c_str(), width, height, 4, pixels.data(), width * 4);
            return (result != 0);
        }

        // 保存深度纹理为灰度 PNG
        static bool SaveDepthTextureToPNG(GLuint textureID, int width, int height, const std::string &filename) {
            glBindTexture(GL_TEXTURE_2D, textureID);

            // 读回深度数据 (float)
            std::vector<float> depthData(width * height);
            glGetTexImage(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, GL_FLOAT, depthData.data());

            // 转换为 [0,255] 灰度
            std::vector<unsigned char> image(width * height);
            for (int i = 0; i < width * height; i++) {
                float d = std::clamp(depthData[i], 0.f, 1.f);
                image[i] = static_cast<unsigned char>(d * 255.0f);
            }

            // 翻转 Y 轴
            FlipImageY(image, width, height, 1);

            // 保存 PNG
            int result = stbi_write_png(filename.c_str(), width, height, 1, image.data(), width);
            return (result != 0);
        }

    private:
        // 通用翻转函数
        static void FlipImageY(std::vector<unsigned char> &data, int width, int height, int channels) {
            int rowSize = width * channels;
            std::vector<unsigned char> temp(rowSize);
            for (int y = 0; y < height / 2; ++y) {
                unsigned char *row1 = data.data() + y * rowSize;
                unsigned char *row2 = data.data() + (height - 1 - y) * rowSize;
                std::memcpy(temp.data(), row1, rowSize);
                std::memcpy(row1, row2, rowSize);
                std::memcpy(row2, temp.data(), rowSize);
            }
        }
    };
};

#endif //TEXTUREUTILS_H
