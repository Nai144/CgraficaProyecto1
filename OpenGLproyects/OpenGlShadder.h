#include "glad/glad.h"
#include <iostream>



class OpenGlShadder{

    unsigned int shaderProgram;
    GLuint texture1;
    bool tex;

    public:

    OpenGlShadder();
    void Use(GLfloat circleScale);
    void loadTextures();
    void loadTextureFromFile(const char* path, GLuint& textureID);
    void DeleteProgram();
    GLuint GetID();
    int GetIDColor();
    GLuint GetIDTexture();
    int GetIDtrue();
    void UseLocation(int offsetX, int offsetY);
    int GetIDOffset();
};