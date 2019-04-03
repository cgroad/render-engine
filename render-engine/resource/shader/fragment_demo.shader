#version 330 core
out vec4 FragColor;
in vec4 color;
in vec2 TexCoord;
uniform vec4 globalColor;
uniform float smileValue;
uniform sampler2D myTexture1;
uniform sampler2D myTexture2;
void main()
{
	FragColor = color;
	FragColor = mix(texture(myTexture1, TexCoord), texture(myTexture2, vec2(smileValue*TexCoord.x, TexCoord.y)), 0.1);
}