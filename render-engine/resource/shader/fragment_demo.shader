#version 330 core
out vec4 FragColor;
in vec2 TexCoord;
uniform vec4 globalColor;
uniform float smileValue;
uniform sampler2D myTexture1;
uniform sampler2D myTexture2;
void main()
{
	FragColor = texture(myTexture1, TexCoord);
}