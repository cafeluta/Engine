#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "glm/glm.hpp"
#include "glm/vec3.hpp"

#include "camera.h"

// WINDOW
extern const int SCR_WIDTH;
extern const int SCR_HEIGHT;

// SHADER
extern const char* vertexShaderPath;
extern const char* fragmentShaderPath;

// CAMERA
extern Camera camera;
extern glm::vec3 cameraPos;
extern glm::vec3 cameraFront;
extern glm::vec3 cameraUp;

extern float lastX;
extern float lastY;
extern bool firstMouse;

// MOUSE MOVEMENT
extern bool firstMouse;
extern float yaw;
extern float pitch;
extern float lastX;
extern float lastY;
extern float fov;

// needed for smoother movement
extern float deltaTime;
extern float lastFrame;

// vertices
extern float vertices[];
extern const size_t verticesSize;

// cubes
extern glm::vec3 cubePositions[];

#endif