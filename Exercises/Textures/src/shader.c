#include "../include/shader.h"
#include "../lib/infolog.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    checkIfCompileWasSuccessful(&vertexShader, "VERTEX");
    free(vertexCode);

    // CREATING FRAGMENT SHADER
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, (const GLchar**) &fragmentCode, NULL);
    glCompileShader(fragmentShader);
    checkIfCompileWasSuccessful(&fragmentShader, "FRAGMENT");
    free(fragmentCode);

    // CREATING SHADER PROGRAM 
    shader->ID = glCreateProgram();
    glAttachShader(shader->ID, vertexShader);
    glAttachShader(shader->ID, fragmentShader);
    glLinkProgram(shader->ID);
    checkIfCompileWasSuccessful(&shader->ID, "SHADER");

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

void Shader_destroy(Shader* shader) {
    glDeleteProgram(shader->ID);
}
