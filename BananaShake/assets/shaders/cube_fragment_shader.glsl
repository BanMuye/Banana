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

layout(std140, binding = 1) uniform Light {
    struct DirectionalLight {
        vec3 Direction;
        vec3 Color;
    };

    struct PointLight {
        vec3 Position;
        float Constant;
        float Linear;
        float Quadratic;
        vec3 Color;
    };

    struct SpotLight {
        vec3 Position;
        vec3 Direction;
        float CutOff;
        vec3 Color;
    }

    DirectionalLight u_DirectionalLights[1];
    PointLight u_PointLights[100];
    SpotLight u_SpotLights[100];
}

vec3 CalcDirLight(Light::DirectionalLight directionalLight, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(-(directionalLight.Direction));

    float diff = max(dot(lightDir, normal), 0.0f);

    vec3 reflectDir = reflect(-(directionalLight.Direction), normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), Output.Shininess);

    vec3 ambient = Output.Ambient * directionalLight.Color;
    vec3 diffuse = directionalLight.Color * Output.Diffuse * diff;
    vec3 specular = directionalLight.Color * Output.Specular * spec;

    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(Light::PointLight pointLight, vec3 normal, vec3 viewDir, vec3 fragPos) {
    vec3 lightDir = normalize(pointLight.Position - fragPos);

    float diff = max(dot(normal, lightDir), 0.0f);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), Output.Shininess);

    float distance = length(pointLight.Position - fragPos);
    float attenuation = 1.0/(pointLight.Constant + pointLight.Linear * distance + pointLight.Quadratic *(distance * distance));

    vec3 ambient = Output.Ambient * pointLight.Color * attenuation;
    vec3 diffuse = Output.Diffuse * pointLight.Color * diff * attenuation;
    vec3 specular = Output.Specular * pointLight.Color * spec * attenuation;

    return (ambient + diffuse + specular);
}

vec3 CalcSpotLight(Light::SpotLight spotLight, vec3 normal, vec3 viewDir, vec3 fragPos) {

    vec3 lightDir = normalize(spotLight.Position - fragPos);

    float ambient = 0, diff = 0, spec = 0;

    float theta = dot(lightDir, -(spotLight.Direction));
    if (theta > light.cutOff) {

        ambient = 1;

        diff = max(dot(normal, lightDir), 0.0f);

        vec3 reflectDir = reflect(-lightDir, normal);
        spec = pow(max(dot(viewDir, reflectDir), 0.0f), Output.Shininess);
    }

    vec3 ambient = Output.Ambient * spotLight.Color * ambient;
    vec3 diffuse = Output.Diffuse * spotLight.Color * diff;
    vec3 specular = Output.Specular * spotLight.Color * spec;

    return (ambient + diffuse + specular);
}

void main() {

    vec3 normal = normalize(Output.Normal);
    vec3 viewDir = normalize(u_ViewPos-Output.Position);
    vec3 fragPos = Output.Position;

    color = (0.0, 0.0, 0.0, Output.Ambient.a);
    for (int i = 0;i<1;i++) color += CalcDirectionalLight(Light.u_DirectionalLights[i], normal, viewDir);
    for (int i = 0;i<100;i++) color += CalPointLight(Light.u_PointLights[i], normal, viewDir, fragPos);
    for (int i = 0;i<100;i++) color += CalSpotLight(Light.u_SpotLights[i], normal, viewDir, fragPos);

    color2 = v_EntityID;
};