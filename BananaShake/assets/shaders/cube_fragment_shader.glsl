#version 450 core

layout(location = 0) out vec4 color;
layout(location = 1) out int color2;

struct VertexOutput {
    vec3 Position;
    vec3 Normal;
    vec4 Ambient;
    vec4 Diffuse;
    vec4 Specular;
    float Shininess;
};


layout(location = 0) in VertexOutput Output;
layout(location = 6) in flat int v_EntityID;

uniform vec4 u_LightColor;
uniform vec3 u_LightPos;
uniform vec3 u_ViewPos;

void main() {

    vec4 ambient = Output.Ambient * u_LightColor;

    vec3 norm = normalize(Output.Normal);
    vec3 lightDir = normalize(u_LightPos - Output.Position);

    float diff = max(dot(norm, lightDir), 0.0);
    vec4 diffuse = diff * Output.Diffuse * u_LightColor;

    vec3 viewDir = normalize(u_ViewPos-Output.Position);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), Output.Shininess);
    vec4 specular = spec * Output.Specular * u_LightColor;

    color = ambient + diffuse + specular;
    color = vec4(color.rgb, 1.0f);

    color2 = v_EntityID;
};