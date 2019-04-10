#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 normal;
out vec3 fragWorldPos;
out vec3 Normal;
out vec3 ViewPos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 viewPos;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	fragWorldPos = vec3(model * vec4(aPos, 1.0));
	Normal = mat3(transpose(inverse(model))) * normal;
	ViewPos = viewPos;
}