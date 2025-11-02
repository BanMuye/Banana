#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec4 a_Ambient;
layout(location = 3) in vec4 a_Diffuse;
layout(location = 4) in vec4 a_Specular;
layout(location = 5) in float a_Shininess;
layout(location = 6) in int a_EntityID;


layout(std140, binding = 0) uniform Camera {
    mat4 u_ViewProjection;
    vec3 u_Position;
};

struct VertexOutput {
    vec3 Position;
    vec3 Normal;
    vec4 Ambient;
    vec4 Diffuse;
    vec4 Specular;
    float Shininess;
};

layout(location = 0) out VertexOutput Output;
layout(location = 6) out flat int v_EntityID;

void main() {
    Output.Position = a_Position;
    Output.Normal = a_Normal;
    Output.Ambient = a_Ambient;
    Output.Diffuse = a_Diffuse;
    Output.Specular = a_Specular;
    Output.Shininess = a_Shininess;

    v_EntityID = a_EntityID;

    gl_Position = u_ViewProjection * vec4(a_Position, 1.0f);
}