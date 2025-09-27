#version 450

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;
layout(location = 3) in vec3 inColor; // added vertex color

layout(binding = 0) uniform UBO {
    mat4 translation;
    mat4 rotation;
    mat4 view;
    mat4 proj;
} ubo;

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec2 fragTexCoord;
layout(location = 2) out vec3 fragNormal;

void main() {
    mat4 model = ubo.translation * ubo.rotation;
    gl_Position = ubo.proj * ubo.view * model * vec4(inPos, 1.0);
    
    fragColor = inColor; // use vertex color instead of position
    fragTexCoord = inTexCoord;
    fragNormal = mat3(model) * inNormal; // simple normal transform
}
