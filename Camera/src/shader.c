#include "../include/shader.h"
#include "../lib/infolog.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* vertexString = "VERTEX";
const char* fragmentString = "FRAGMENT";
const char* shaderString = "SHADER";

// LOAD SHADERS
static char* readFile(const char* filePath) {
    FILE* file = fopen(filePath, "rb");
    if (!file) {
        printf("Failed to open file: %s\n", filePath);
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    rewind(file);

    char* buffer = (char*)malloc(length + 1);
    fread(buffer, 1, length, file);
    buffer[length] = '\0';
    fclose(file);
    return buffer;
}

// INITIALIZATION
void Shader_init(Shader* shader, const char* vertexPath, const char* fragmentPath) {
    char* vertexCode = readFile(vertexPath);
    char* fragmentCode = readFile(fragmentPath);

    if (!vertexCode || !fragmentCode) {
        printf("Shader file not loaded properly!\n");
        return;
    }

    // CREATING VERTEX SHADER
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, (const GLchar**) &vertexCode, NULL);
    glCompileShader(vertexShader);
    checkIfCompileWasSuccessful(&vertexShader, vertexString);
    free(vertexCode);

    // CREATING FRAGMENT SHADER
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, (const GLchar**) &fragmentCode, NULL);
    glCompileShader(fragmentShader);
    checkIfCompileWasSuccessful(&fragmentShader, fragmentString);
    free(fragmentCode);

    // CREATING SHADER PROGRAM 
    shader->ID = glCreateProgram();
    glAttachShader(shader->ID, vertexShader);
    glAttachShader(shader->ID, fragmentShader);
    glLinkProgram(shader->ID);
    checkIfCompileWasSuccessful(&shader->ID, shaderString);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader_use(Shader* shader) {
    glUseProgram(shader->ID);
}

void Shader_setBool(Shader* shader, const char* name, int value) {
    glUniform1i(glGetUniformLocation(shader->ID, name), value);
}

void Shader_setInt(Shader* shader, const char* name, int value) {
    glUniform1i(glGetUniformLocation(shader->ID, name), value);
}
void Shader_setFloat(Shader* shader, const char* name, float value) {
    glUniform1f(glGetUniformLocation(shader->ID, name), value);
}

void Shader_setFloat4(Shader* shader, const char* name, float x, float y, float z, float w) {
    glUniform4f(glGetUniformLocation(shader->ID, name), x, y, z, w);
}

GLint Shader_getUniformLocation(GLuint shaderID, const char *name) {
    return glGetUniformLocation(shaderID, name);
}

void Shader_setVec2(GLuint shaderID, const char *name, GLfloat x, GLfloat y) {
    glUniform2f(Shader_getUniformLocation(shaderID, name), x, y);
}

void Shader_setVec2v(GLuint shaderID, const char *name, const GLfloat *value) {
    glUniform2fv(Shader_getUniformLocation(shaderID, name), 1, value);
}

void Shader_setVec3(GLuint shaderID, const char *name, GLfloat x, GLfloat y, GLfloat z) {
    glUniform3f(Shader_getUniformLocation(shaderID, name), x, y, z);
}

void Shader_setVec3v(GLuint shaderID, const char *name, const GLfloat *value) {
    glUniform3fv(Shader_getUniformLocation(shaderID, name), 1, value);
}

void Shader_setVec4(GLuint shaderID, const char *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
    glUniform4f(Shader_getUniformLocation(shaderID, name), x, y, z, w);
}

void Shader_setVec4v(GLuint shaderID, const char *name, const GLfloat *value) {
    glUniform4fv(Shader_getUniformLocation(shaderID, name), 1, value);
}

void Shader_setMat2(GLuint shaderID, const char *name, const glm::mat2 *mat) {
    glUniformMatrix2fv(Shader_getUniformLocation(shaderID, name), 1, GL_FALSE, glm::value_ptr(*mat));
}

void Shader_setMat3(GLuint shaderID, const char *name, const glm::mat3 *mat) {
    glUniformMatrix3fv(Shader_getUniformLocation(shaderID, name), 1, GL_FALSE, glm::value_ptr(*mat));
}

void Shader_setMat4(GLuint shaderID, const char *name, const glm::mat4 *mat) {
    glUniformMatrix4fv(Shader_getUniformLocation(shaderID, name), 1, GL_FALSE, glm::value_ptr(*mat));
}

void Shader_destroy(Shader* shader) {
    glDeleteProgram(shader->ID);
}
