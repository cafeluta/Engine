/*
    Name: Ionita Sebastian-Marius ☕
    University: ACS UPB
*/

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "lib/linmath.h"
#include "lib/callback.h"
#include "include/stb_image.h"
#include "include/shader.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;

// float vertices[] = {
//     // positions          // texture coords
//      0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
//      0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
//     -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
//     -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
// };
float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

glm::vec3 cubePositions[] = {
    glm::vec3(1.0f, 0.0f, 0.0f),
    glm::vec3( 2.0f,  5.0f, -15.0f), 
    glm::vec3(-1.5f, -2.2f, -2.5f),  
    glm::vec3(-3.8f, -2.0f, -12.3f),  
    glm::vec3( 2.4f, -0.4f, -3.5f),  
    glm::vec3(-1.7f,  3.0f, -7.5f),  
    glm::vec3( 1.3f, -2.0f, -2.5f),  
    glm::vec3( 1.5f,  2.0f, -2.5f), 
    glm::vec3( 1.5f,  0.2f, -1.5f), 
    glm::vec3(-1.3f,  1.0f, -1.5f)
};
// unsigned int indices[] = {
//     0, 1, 3, // first triangle
//     1, 2, 3  // second triangle
// };

const char* vertexShaderPath = "ssc/vertex_shader.glsl";
const char* fragmentShaderPath = "ssc/fragment_shader.glsl";
const char* imageContainer = "img/container.jpg";
const char* imageAwesomeFace = "img/awesomeface.png";

// CAMERA
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 20.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

// TIMING 
float deltaTime = 0.0f; // the time between current frame and last frame
float lastFrame = 0.0f;

void processInput(GLFWwindow* window);

int main() {
    if (!glfwInit()) {
        // Initialization failed
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Shaders", NULL, NULL);
    if (!window) {
        // Window creation failed
        exit(EXIT_FAILURE);
    }
    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        // Glad initialization failed
        exit(EXIT_FAILURE);
    }
    glfwSwapInterval(1);
    glEnable(GL_DEPTH_TEST);

    // VERTEX OBJECTS
    GLuint VAO;
    glGenVertexArrays(1, &VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO);

    // SHADER
    Shader shader;
    Shader_init(&shader, vertexShaderPath, fragmentShaderPath);
    Shader_use(&shader);

    // LINKING
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // POSITION ATTRIBUTE
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // COORD ATTRIBUTE
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // TEXTURE
    GLuint texture1, texture2;

    // texture 1
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    // TEXTURE WRAPPING
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // TEXTURE FILTERING
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // LOAD IMAGE
    int imageWidth, imageHeight, imageNrChannels;
    stbi_set_flip_vertically_on_load(GL_TRUE);
    unsigned char* data = stbi_load(imageContainer, &imageWidth, &imageHeight, &imageNrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        printf("Failed to load image from: %s\n", imageContainer);
        exit(EXIT_FAILURE);
    }
    stbi_image_free(data);

    // texture 2
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    // TEXTURE WRAPPING
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // TEXTURE FILTERING
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // LOAD IMAGE
    data = stbi_load(imageAwesomeFace, &imageWidth, &imageHeight, &imageNrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        printf("Failed to load image from: %s\n", imageAwesomeFace);
        exit(EXIT_FAILURE);
    }
    stbi_image_free(data);

    // SETTING TEXTURES
    Shader_use(&shader);
    Shader_setInt(&shader, "texture1", 0);
    Shader_setInt(&shader, "texture2", 1);

    // Camera
    // this is for fps like games
    // glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 10.0f);
    // glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);  // the camera points at the intersection of all axis
    // glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
    // /*
    //     normalize = the vector sits between [0,1]
    //     the directions is the vector from (0,0,0) to (0,0,3)
    // */
    // glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);  // y axis
    // glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
    // /*
    //     the cross product of 2 vectors result in a vector perpendicular on both of them
    //     cross(up, cameraDirection) = cross(y-axis, z-axis) = x-axis
    // */
    // glm::vec3 cameraUp = glm::normalize(glm::cross(cameraRight, cameraDirection));  // this is the y-axis

    glm::mat4 projection = glm::perspective(glm::radians(75.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 500.0f);  
    Shader_setMat4(shader.ID, "projection", &projection);


    // LOOP
    while (!glfwWindowShouldClose(window)) {
        // for a smoother movement
        float currentFrame = (float)(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Using textures
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        Shader_use(&shader);

        // GOING 3D
        // printf("Pos: %f, %f, %f | Front: %f, %f, %f\n",
        //     cameraPos.x, cameraPos.y, cameraPos.z,
        //     cameraFront.x, cameraFront.y, cameraFront.z);
        // moving the camera ourself with input        
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        Shader_setMat4(shader.ID, "view", &view);

    //     printf("View Matrix:\n");
    // for (int i = 0; i < 4; i++) {
    //     for (int j = 0; j < 4; j++) {
    //         printf("%f ", view[i][j]);
    //     }
    //  }

        glBindVertexArray(VAO);
        for(unsigned int i = 0; i < 10; i++)
        {
            // rotating and rendering cubes
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            Shader_setMat4(shader.ID, "model", &model);

            // rotating camera on x and z axis
            // float radius = 10.0f;
            // float camX = sin(glfwGetTime()) * radius;
            // float camZ = cos(glfwGetTime()) * radius;
            // view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            // Shader_setMat4(shader.ID, "view", &view);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    Shader_destroy(&shader);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window) {
    float cameraSpeed = 10.5f * deltaTime; // deltaTime pentru mișcare fluidă

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    printf("cameraPos.x: %f, cameraPos.y: %f, cameraPos: %f\n", cameraPos.x, cameraPos.y, cameraPos.z);    
}


