#version 460 core

layout (location = 0) in vec3 aPos;

out vec4 vec_color;

void main() {
    if (aPos.x == -0.5) vec_color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
    else if (aPos.x == 0.5) vec_color = vec4(0.0f, 1.0f, 0.0f, 1.0f);
    else if (aPos.y == 0.5) vec_color = vec4(0.0f, 0.0f, 1.0f, 1.0f);

    gl_Position = vec4(0.5*aPos, 1.0);
}
