#version 330 core
out vec4 FragColor;
in vec3 fragWorldPos;
in vec3 Normal;
in vec3 ViewPos;
in vec2 TexCoords;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform sampler2D myTexture1;
uniform sampler2D myTexture2;

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
	float shininess;
};

struct LightingMaterial {
	vec3 specular;
	vec3 diffuse;
	vec3 ambient;
	float shininess;
};

uniform Material material;
uniform LightingMaterial lighting;

void main()
{
	vec3 lightDir = normalize(lightPos - fragWorldPos);
	float diff = max(dot(lightDir, normalize(Normal)), 0.0);
	vec3 diffuse = diff * lighting.diffuse * vec3(texture(material.diffuse, TexCoords));

	float ambientStrenth = 0.1;
	vec3 ambient = lighting.ambient * vec3(texture(material.diffuse, TexCoords));

	float specularStrenth = 0.3;
	vec3 viewDir = normalize(ViewPos - fragWorldPos);
	vec3 reflectDir = reflect(-lightDir, normalize(Normal));
	float specularDiff = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = specularDiff * lighting.specular * vec3(texture(material.specular, TexCoords));

	vec3 emission = vec3(texture(material.emission, TexCoords));
	FragColor = vec4(ambient + diffuse + specular + emission, 1.0f);
}