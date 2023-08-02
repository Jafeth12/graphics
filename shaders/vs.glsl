#version 460 core

layout (location = 0) in vec3 pos;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;

out vec3 frontColor;

void main() {
    frontColor = vec4(normalize(pos), 1.0).xyz;

    gl_Position = projection * view * model * vec4(pos, 1.0);
}
