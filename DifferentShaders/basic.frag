#version 410 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;
in vec4 FragPosLightSpace;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;

uniform sampler2D texture_diffuse1;
uniform sampler2D shadowMap;

float ShadowCalculation(vec4 fragPosLightSpace)
{
	vec3 projCoords =  fragPosLightSpace.xyz /  fragPosLightSpace.w;
	projCoords = projCoords * 0.5 + 0.5;
	float closestDepth =  texture(shadowMap,projCoords.xy).r;
	float currentDepth = projCoords.z;
	return currentDepth > closestDepth ? 1.0f : 0.0f;
}

void main()
{
	// ambient
	vec3 ambient = 0.1f * lightColor;

	// diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	//Dot product of normals
	float diff = max(dot(lightDir, norm), 0.0);
	vec3 diffuse = diff * lightColor;

	// specular
	float specularStrength = 0.1f;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	vec3 halfwayDir = normalize(lightDir + viewDir);
	float spec = pow(max(dot(norm, halfwayDir), 0.0), 32.0);

	vec3 specular =specularStrength* spec * lightColor;

	float shadow =  ShadowCalculation(FragPosLightSpace);

	vec3 result = (ambient  + (1.0-shadow) *(diffuse + specular) ) * texture(texture_diffuse1,TexCoords).rgb;

	FragColor = vec4(result, 1.0);
}