#version 460 core

out vec4 FragColor;

in vec3 frontColor;
in vec2 texCoord;
in float vBrightness;

uniform sampler2D tex;

void main() {
    // FragColor = vec4(color, 1.0f);
    // FragColor = vec4(frontColor, 1.0f);

    vec4 texColor = texture(tex, texCoord) * vBrightness;

    if (texColor.a < 0.1)
        discard;

    FragColor = texColor;
}
