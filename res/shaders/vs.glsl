#version 460 core

layout (location = 0) in vec3 pos;
// layout (location = 1) in vec3 normal;
layout (location = 1) in vec2 uv;
layout (location = 2) in float brightness;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;

out vec3 frontColor;
out vec2 texCoord;
out float vBrightness;

void main() {
    // frontColor = vec4(normalize(pos), 1.0).xyz;
    texCoord = uv;
    vBrightness = brightness;

    gl_Position = projection * view * model * vec4(pos, 1.0);
}
