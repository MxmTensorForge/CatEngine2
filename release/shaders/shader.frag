#version 330 core

out vec4 fragColor;
flat in vec3 vNormal;
in vec3 vWorldPos;
in vec2 vTexCoord;

uniform vec4 uColor;
uniform vec3 uAmbient;

uniform int uUseTexture;
uniform int uIsShaded;

uniform float uShininess;
uniform float uSpecular;

uniform vec3 uCameraPos;

uniform sampler2D uTexture;

struct PointLight
{
	float linearFading;
	float quadraticFading;
	float intensity;
	vec3 lightColor;
	vec3 lightPos;
};
uniform PointLight pointLights[8];
uniform int pointLightsCount;

struct DirectionLight
{
	vec3 direction;
	vec3 lightColor;
	float intensity;
};
uniform DirectionLight directionLight;

vec3 calculatePointLight(PointLight light, vec3 fragCoord, vec3 viewDir) {
	vec3 toLight = normalize(light.lightPos - fragCoord);
    vec3 halfVec = normalize(toLight + viewDir);

	float diffuse = max(dot(toLight, vNormal), 0.0);
    float specular = pow(max(dot(halfVec, vNormal), 0.0), uShininess);

	float r = length(light.lightPos - fragCoord);
	float intensity = light.intensity / (1 + light.linearFading*r + light.quadraticFading*r*r);
	float finalLight = (diffuse + specular * uSpecular) * intensity;

	return light.lightColor * finalLight;
}
vec3 calculateDirectionLight(DirectionLight light, vec3 viewDir) {
    vec3 lightDir = -light.direction;

    float diffuse = max(dot(vNormal, lightDir), 0.0);
    
    vec3 halfVec = normalize(lightDir + viewDir);
    float specular = pow(max(dot(halfVec, vNormal), 0.0), uShininess);
    
    return light.lightColor * light.intensity * (diffuse + specular * uSpecular);
}

void main() {
	vec4 baseColor = (uUseTexture == 0) ? uColor : texture(uTexture, vTexCoord);
	if (uUseTexture == 1) {
		if (baseColor.a < 0.1) discard; 
		baseColor.a *= uColor.a;
	}
	
	if (uIsShaded == 0) {
		fragColor = baseColor;
		return;
	}

	vec3 viewDir = normalize(uCameraPos - vWorldPos);

	vec3 totalLight = uAmbient;
	for (int i = 0; i < pointLightsCount; i++) {
		totalLight += calculatePointLight(pointLights[i], vWorldPos, viewDir);
	}
	totalLight += calculateDirectionLight(directionLight, viewDir);

    vec3 finalColor = baseColor.rgb * totalLight;
	fragColor = vec4(finalColor, baseColor.a);
}
