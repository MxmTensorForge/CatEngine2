#version 330 core

layout(location=0) in vec3 aPos;
layout(location=1) in vec3 aNormal;
layout(location=2) in vec2 aTexCoord;

uniform mat4 uProjection;
uniform mat4 uView;
uniform mat4 uModel;
uniform float uUvScale;

flat out vec3 vNormal;
out vec3 vWorldPos;
out vec2 vTexCoord;

void main() {
    vec4 worldPos = uModel * vec4(aPos, 1.0);
    vWorldPos = worldPos.xyz;
    
    gl_Position = uProjection * uView * worldPos;
    
    mat3 normalMatrix = mat3(uModel);
    vNormal = normalize(normalMatrix * aNormal);

    vTexCoord = aTexCoord * uUvScale;
}
