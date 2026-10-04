#version 330 core

layout(location=0) in vec3 aPos;
layout(location=1) in vec2 aTextCoord;
layout(location=2) in vec4 aColor;

uniform mat4 uProjection;
out vec2 vTextCoord;
out vec4 vColor;

void main() {
    gl_Position = uProjection * vec4(aPos, 1.0);
    vTextCoord = aTextCoord;
    vColor = aColor;
}