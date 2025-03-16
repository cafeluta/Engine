#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

typedef struct {
    GLuint ID;
} Shader;

void Shader_init(Shader* shader, const char* vertexPath, const char* fragmentPath);
void Shader_use(Shader* shader);
void Shader_setBool(Shader* shader, const char* name, int value);
void Shader_setInt(Shader* shader, const char* name, int value);
void Shader_setFloat(Shader* shader, const char* name, float value);
void Shader_setFloat4(Shader* shader, const char* name, float x, float y, float z, float w);
void Shader_destroy(Shader* shader);

#endif