#include "OpenGlShadder.h"
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include "glad/glad.h"
#include <iostream>

OpenGlShadder::OpenGlShadder(){

const char *vertexShaderSource ="#version 410 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "uniform float scale;\n"
    "uniform vec2 offset;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(aPos * scale + vec3(offset, 0.0), 1.0);\n"
    "}\n\0";

const char *fragmentShaderSource = "#version 410 core\n"
    "out vec4 FragColor;\n"
    "uniform vec4 ourColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = ourColor;\n"
    "}\n\0";

    
    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        
    }
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
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
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
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

void OpenGlShadder::Use(GLfloat circleScale){
    // asegÃºrese de activar el sombreador antes de cualquier llamada a glUniform
    glUseProgram(shaderProgram);
    glUniform1f(glGetUniformLocation(shaderProgram, "scale"), circleScale);
}
//
GLuint OpenGlShadder::GetID(){
    return glGetUniformLocation(shaderProgram, "scale");
}
int OpenGlShadder::GetIDColor(){
    return glGetUniformLocation(shaderProgram, "ourColor");
}
void OpenGlShadder::DeleteProgram(){
    glDeleteProgram(shaderProgram);
}

void OpenGlShadder::UseLocation(int offsetX, int offsetY)
{   
    glUniform2f(glGetUniformLocation(shaderProgram, "offset"), offsetX, offsetY);

}

int OpenGlShadder::GetIDOffset(){
    return glGetUniformLocation(shaderProgram, "offset");
}