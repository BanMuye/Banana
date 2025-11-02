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

struct DirectionalLight {
    vec4 Direction;
    vec4 Color;
};

struct PointLight {
    vec4 Position;
    float Constant;
    float Linear;
    float Quadratic;
    vec4 Color;
};

struct SpotLight {
    vec4 Position;
    vec4 Direction;
    float CutOff;
    float OutterCutOff;
    vec4 Color;
};

layout(location = 0) in VertexOutput Output;
layout(location = 6) in flat int v_EntityID;

layout(std140, binding = 0) uniform Camera {
    mat4 u_ViewProjection;
    vec3 u_Position;
};

layout(std140, binding = 1) uniform Light {

    int u_DirectionalLightCount;
    int u_PointLightCount;
    int u_SpotLightCount;

    DirectionalLight u_DirectionalLights[1];
    PointLight u_PointLights[100];
    SpotLight u_SpotLights[100];
};

vec3 CalcDirLight(DirectionalLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir, vec3 fragPos);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 viewDir, vec3 fragPos);

vec3 CalcDirLight(DirectionalLight directionalLight, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(-(directionalLight.Direction.xyz));

    float diff = max(dot(lightDir, normal), 0.0f);

    vec3 reflectDir = reflect(-(lightDir), normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), Output.Shininess);

    vec3 ambient = Output.Ambient.rgb * directionalLight.Color.rgb;
    vec3 diffuse = directionalLight.Color.rgb * Output.Diffuse.rgb * diff;
    vec3 specular = directionalLight.Color.rgb * Output.Specular.rgb * spec;

    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight pointLight, vec3 normal, vec3 viewDir, vec3 fragPos) {
    vec3 lightDir = normalize(pointLight.Position.xyz - fragPos);

    float diff = max(dot(normal, lightDir), 0.0f);

    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), Output.Shininess);

    float distance = length(pointLight.Position.xyz - fragPos);
    float attenuation = 1.0/(pointLight.Constant + pointLight.Linear * distance + pointLight.Quadratic *(distance * distance));

    vec3 ambient = Output.Ambient.rgb * pointLight.Color.rgb * attenuation;
    vec3 diffuse = Output.Diffuse.rgb * pointLight.Color.rgb * diff * attenuation;
    vec3 specular = Output.Specular.rgb * pointLight.Color.rgb * spec * attenuation;

    return (ambient + diffuse + specular);
}

vec3 CalcSpotLight(SpotLight spotLight, vec3 normal, vec3 viewDir, vec3 fragPos) {

    vec3 lightDir = normalize(spotLight.Position.xyz - fragPos);

    float theta = dot(lightDir, -normalize(spotLight.Direction.xyz));
    float epsilon = spotLight.CutOff - spotLight.OutterCutOff;
    float intensity = clamp((theta - spotLight.OutterCutOff)/epsilon, 0.0f, 1.0f);


    float diff = max(dot(normal, lightDir), 0.0f);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), Output.Shininess);

    vec3 ambient = Output.Ambient.rgb * spotLight.Color.rgb * intensity;
    vec3 diffuse = Output.Diffuse.rgb * spotLight.Color.rgb * diff * intensity;
    vec3 specular = Output.Specular.rgb * spotLight.Color.rgb * spec * intensity;

    return (ambient + diffuse + specular);
}

void main() {

    vec3 normal = normalize(Output.Normal.rgb);
    vec3 viewDir = normalize(u_Position-Output.Position);
    vec3 fragPos = Output.Position;

    vec3 lightColor = vec3(0.0f, 0.0f, 0.0f);
    for (int i = 0;i<u_DirectionalLightCount;i++) lightColor += CalcDirLight(u_DirectionalLights[i], normal, viewDir);
    for (int i = 0;i<u_PointLightCount;i++) lightColor += CalcPointLight(u_PointLights[i], normal, viewDir, fragPos);
    for (int i = 0;i<u_SpotLightCount;i++) lightColor += CalcSpotLight(u_SpotLights[i], normal, viewDir, fragPos);

    color = vec4(lightColor, Output.Ambient.a);

    color2 = v_EntityID;
}