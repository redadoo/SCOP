#version 450

layout(binding = 1) uniform sampler2D texSampler;

layout(push_constant) uniform PushConstants {
    int useTexture;
} pc;

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec3 fragNormal;

layout(location = 0) out vec4 outColor;

void main() {
    vec3 normal = normalize(fragNormal);
    vec3 lightDir = normalize(vec3(0.5, 1.0, 0.3));
    float diffuse = max(dot(normal, lightDir), 0.0);

    vec3 texColor = texture(texSampler, fragTexCoord).rgb;
    vec3 baseColor = mix(fragColor, texColor, float(pc.useTexture));
    vec3 finalColor = baseColor * (0.2 + 0.8 * diffuse);
    outColor = vec4(finalColor, 1.0);
}
