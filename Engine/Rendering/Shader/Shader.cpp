#include "Shader.h"

Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc) {
	CompileShader(GL_VERTEX_SHADER, vertexSrc);
	CompileShader(GL_FRAGMENT_SHADER, fragmentSrc);

	ShaderProgram = glCreateProgram();
	glAttachShader(ShaderProgram, VertexShader);
	glAttachShader(ShaderProgram, FragmentShader);
	glLinkProgram(ShaderProgram);

	glDeleteShader(VertexShader);
	glDeleteShader(FragmentShader);
}

Shader::~Shader() {
	glDeleteProgram(ShaderProgram);
}

void Shader::Bind() const {
	glUseProgram(ShaderProgram);
}

void Shader::Unbind() const {
	glUseProgram(0);
}

void Shader::UploadUniformInt(const std::string& name, const unsigned int v) {
	Bind();
	glUniform1i(glGetUniformLocation(ShaderProgram, name.c_str()), v);
}

void Shader::UploadUniformFloat(const std::string& name, const float v) {
	Bind();
	glUniform1f(glGetUniformLocation(ShaderProgram, name.c_str()), v);
}

void Shader::UploadUniformFloat2(const std::string& name, const glm::vec2& vector) {
	Bind();
	glUniform2f(glGetUniformLocation(ShaderProgram, name.c_str()), vector[0], vector[1]);
}

void Shader::UploadUniformFloat3(const std::string& name, const glm::vec3& vector) {
	Bind();
	glUniform3f(glGetUniformLocation(ShaderProgram, name.c_str()), vector[0], vector[1], vector[2]);
}

void Shader::UploadUniformMatrixFloat4x4(const std::string& name, const glm::mat4& matrix) {
	Bind();
	glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, name.c_str()), 1, GL_FALSE, &matrix[0][0]);
}

void Shader::CompileShader(GLenum shaderType, const std::string& shaderSrc) {
	GLuint shader = glCreateShader(shaderType);
	const GLchar* src = shaderSrc.c_str();
	glShaderSource(shader, 1, &src, nullptr);
	glCompileShader(shader);
	if (shaderType == GL_VERTEX_SHADER) VertexShader = shader;
	else FragmentShader = shader;
}