#version 450

layout(binding = 1) uniform sampler2D texSampler;
layout(binding = 2) uniform MaterialUBO {
    int useTexture;
} material;

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec3 fragNormal;   

layout(location = 0) out vec4 outColor;

void main() {
    vec3 normal = normalize(fragNormal);

    vec3 lightDir = normalize(vec3(0.5, 1.0, 0.3));
    float diffuse = max(dot(normal, lightDir), 0.0);

    vec3 baseColor = (material.useTexture == 1)
        ? texture(texSampler, fragTexCoord).rgb
        : fragColor;

    vec3 finalColor = baseColor * (0.2 + 0.8 * diffuse);

    outColor = vec4(finalColor, 1.0);
}
