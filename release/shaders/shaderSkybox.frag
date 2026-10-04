#version 330 core

in vec3 texCoord;
out vec4 fragColor;

uniform samplerCube uSkyBox;

void main() {
    fragColor = texture(uSkyBox, texCoord);
}
