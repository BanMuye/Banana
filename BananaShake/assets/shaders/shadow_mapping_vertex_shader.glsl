#version 450 core
layout(location = 1) in vec3 a_OriginalPosition;

layout(std140, binding=2) uniform LightSpace {
    mat4 u_LightViewProjection;
};

void main() {
    gl_Position = u_LightViewProjection * vec4(a_OriginalPosition, 1.0f);
}