#version 330 core
out vec4 FragColor;
in vec3 fragWorldPos;
in vec3 Normal;
in vec3 ViewPos;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform sampler2D myTexture1;
uniform sampler2D myTexture2;
void main()
{
	vec3 lightDir = normalize(lightPos - fragWorldPos);
	float diff = max(dot(lightDir, normalize(Normal)), 0.0);
	vec3 diffuse = diff * lightColor;

	float ambientStrenth = 0.1;
	vec3 ambient = lightColor * ambientStrenth;

	float specularStrenth = 0.3;
	vec3 viewDir = normalize(ViewPos - fragWorldPos);
	vec3 reflectDir = reflect(-lightDir, normalize(Normal));
	float specularDiff = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularDiff * lightColor * specularStrenth;

	FragColor = vec4((ambient + diffuse + specular) * vec3(1.0f, 0.5f, 0.31f), 1.0f);
}