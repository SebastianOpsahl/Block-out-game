#ifndef SHADER_H_
#define SHADER_H_

#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>

class Shader
{
public:
    Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
    ~Shader();

    void Bind() const;
    void Unbind() const;
    void UploadUniformInt(const std::string& name, const unsigned int v);
    void UploadUniformFloat(const std::string& name, const float v);
    void UploadUniformFloat2(const std::string& name,
        const glm::vec2& vector);
    void UploadUniformFloat3(const std::string& name,
        const glm::vec3& vector);
    void UploadUniformMatrixFloat4x4(const std::string& name,
        const glm::mat4& matrix);

private:
    GLuint VertexShader;
    GLuint FragmentShader;
    GLuint ShaderProgram;

    void CompileShader(GLenum shaderType, const std::string& shaderSrc);
};

#endif