#include "OpenGlShadder.h"
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include "glad/glad.h"
#include <iostream>

OpenGlShadder::OpenGlShadder(const char *_vertexShaderSource,const char *_fragmentShaderSource){

    vertexShaderSource=_vertexShaderSource;
    fragmentShaderSource=_fragmentShaderSource;
    
    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        
    }
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // link shaders
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

}

void OpenGlShadder::Use(GLfloat circle){
    glUseProgram(shaderProgram);
    glUniform1f(glGetUniformLocation(shaderProgram, "scale"), circle);
}

GLuint OpenGlShadder::GetID(){
    return glGetUniformLocation(shaderProgram, "scale");
}
int OpenGlShadder::GetIDColor(){
    return glGetUniformLocation(shaderProgram, "ourColor");
}
void OpenGlShadder::DeleteProgram(){
    glDeleteProgram(shaderProgram);
}

