#ifndef INFOLOG_H
#define INFOLOG_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#ifndef INFOLOG_NO_INLINE
#define INFOLOG_H_FUNC static
// #else
// #define INFOLOG_H_FUNC static inline
#endif

#endif // INFOLOG_H

INFOLOG_H_FUNC void checkIfCompileWasSuccessful(const GLuint *shader, char* str) {
    // Check if compilation was successful
    int  success;
    char infoLog[512];
    glGetShaderiv(*shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(*shader, 512, NULL, infoLog);
        printf("ERROR::SHADER::%s::COMPILATION_FAILED\n%s\n", str, infoLog);
    }
}
