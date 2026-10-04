#version 330 core

out vec4 fragColor;
in vec2 vTextCoord;
in vec4 vColor;

uniform sampler2D textTexture;

void main() {
	fragColor = texture(textTexture, vTextCoord).rgba * vColor;
}