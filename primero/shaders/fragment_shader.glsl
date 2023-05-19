#version 460 core

out vec4 FragColor;

in vec4 vec_color;

void main() {
    FragColor = vec_color;
    // FragColor = vec4(0.0f, 0.5f, 0.2f, 1.0f);
}
