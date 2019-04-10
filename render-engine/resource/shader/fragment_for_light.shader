#version 330 core
out vec4 FragColor;
uniform vec3 lightColor;
uniform sampler2D myTexture1;
uniform sampler2D myTexture2;
void main()
{
	FragColor = vec4(1.0);
}