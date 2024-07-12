#include "OpenGlShadder.h"
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include "glad/glad.h"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

OpenGlShadder::OpenGlShadder(){

const char *vertexShaderSource = R"glsl(
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;

out vec2 TexCoord;
uniform vec2 offset;
uniform float scale;

void main() {
    gl_Position = vec4(scale * (aPos.xy + offset), 0.0, 1.0);
    TexCoord = aTexCoord;
}
)glsl";

const char *fragmentShaderSource = R"glsl(
#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;
uniform vec4 ourColor;
uniform bool tex;

void main() {
    vec4 texColor = texture(texture1, TexCoord);
    if(tex){
        FragColor = texColor*ourColor;
    }else{
        FragColor = ourColor;
    }
    
}
)glsl";

    
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

void OpenGlShadder::loadTextures() {
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    loadTextureFromFile("./imagenes/wall.jpg", texture1);

        
}

void OpenGlShadder::loadTextureFromFile(const char* path, GLuint& textureID) {
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data) {
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture: " << path << std::endl;
    }
    stbi_image_free(data);
}

void OpenGlShadder::Use(GLfloat circleScale){
    // asegÃºrese de activar el sombreador antes de cualquier llamada a glUniform
    glUseProgram(shaderProgram);
    glUniform1f(glGetUniformLocation(shaderProgram, "scale"), circleScale);
    glUniform1f(glGetUniformLocation(shaderProgram, "tex"), true);
}
//
GLuint OpenGlShadder::GetID(){
    return glGetUniformLocation(shaderProgram, "scale");
}
GLuint OpenGlShadder::GetIDTexture(){
    return texture1;
}
int OpenGlShadder::GetIDColor(){
    return glGetUniformLocation(shaderProgram, "ourColor");
}
int OpenGlShadder::GetIDtrue(){
    return glGetUniformLocation(shaderProgram, "tex");
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