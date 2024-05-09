#include "glad/glad.h"
#include <iostream>

class OpenGlShadder{

    unsigned int vertexShader;
    unsigned int fragmentShader;
    unsigned int shaderProgram;
    const char *vertexShaderSource;
    const char *fragmentShaderSource;

    public:

    OpenGlShadder(const char *_vertexShaderSource,const char *_fragmentShaderSource);
    void Use(GLfloat circle);
    void DeleteProgram();
    GLuint GetID();
    int GetIDColor();
};