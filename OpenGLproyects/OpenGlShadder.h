#include "glad/glad.h"
#include <iostream>

class OpenGlShadder{

    unsigned int shaderProgram;

    public:

    OpenGlShadder();
    void Use(GLfloat circleScale);
    void DeleteProgram();
    GLuint GetID();
    int GetIDColor();
    void UseLocation(int offsetX, int offsetY);
    int GetIDOffset();
};