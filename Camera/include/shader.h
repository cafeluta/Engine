#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

typedef struct {
    GLuint ID;
} Shader;

void Shader_init(Shader* shader, const char* vertexPath, const char* fragmentPath);
void Shader_use(Shader* shader);
void Shader_setBool(Shader* shader, const char* name, int value);
void Shader_setInt(Shader* shader, const char* name, int value);
void Shader_setFloat(Shader* shader, const char* name, float value);
void Shader_setFloat4(Shader* shader, const char* name, float x, float y, float z, float w);
GLint Shader_getUniformLocation(GLuint shaderID, const char *name);
void Shader_setVec2(GLuint shaderID, const char *name, GLfloat x, GLfloat y);
void Shader_setVec2v(GLuint shaderID, const char *name, const GLfloat *value);
void Shader_setVec3(GLuint shaderID, const char *name, GLfloat x, GLfloat y, GLfloat z);
void Shader_setVec3v(GLuint shaderID, const char *name, const GLfloat *value);
void Shader_setVec4(GLuint shaderID, const char *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
void Shader_setMat2(GLuint shaderID, const char *name, const glm::mat2 *mat);
void Shader_setMat3(GLuint shaderID, const char *name, const glm::mat3 *mat);
void Shader_setMat4(GLuint shaderID, const char *name, const glm::mat4 *mat);
void Shader_destroy(Shader* shader);

#endif