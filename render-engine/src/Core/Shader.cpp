#include <Core/Shader.h>
Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	std::string vertexCodeStr, fragmentCodeStr;
	//read shader code
	try
	{
		ifstream vertex_fstream(vertexPath);
		ifstream fragment_fstream(fragmentPath);
		std::stringstream vertex_strstream, frag_strstream;
		vertex_strstream << vertex_fstream.rdbuf();
		frag_strstream << fragment_fstream.rdbuf();
		vertex_fstream.close();
		fragment_fstream.close();
		vertexCodeStr = vertex_strstream.str();
		fragmentCodeStr = frag_strstream.str();
	}
	catch(std::ifstream::failure e)
	{
		std::cout << "ERROR:shader file node successfully read" << std::endl;
	}
	const char* vShaderCode = vertexCodeStr.c_str();
	const char* fShaderCode = fragmentCodeStr.c_str();
	//compile shader code
	unsigned int vertex, fragment;
	char infoLog[512];
	int success;
	//vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR:shader vertex compile failed\n" << infoLog << std::endl;
	}
	//fragment shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR:shader fragment compile failed\n" << infoLog << std::endl;
	}
	//shader link
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR:shader program link failed\n" << infoLog << std::endl;
	}
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::setBool(const string &name, bool value)
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setFloat(const string &name, float value)
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setInt(const string &name, int value)
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setColor(const string &name, float r, float g, float b, float a)
{
	glUniform4f(glGetUniformLocation(ID, name.c_str()), r, g, b, a);
}