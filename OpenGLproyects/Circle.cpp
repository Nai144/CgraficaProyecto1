#include "Circle.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath>





Circle::Circle(int _numSegments, float _radius,float _red, float _green, float _blue){
    numSegments=_numSegments;
    radius=_radius;
    red=_red;
    green=_green;
    blue=_blue;
    scale=1.0f;
}

void Circle::PositionOfVertices(float vertices[]){

    for (int i = 0; i < numSegments; ++i) {
        float theta = 2.0f * 3.1415926f * float(i) / float(numSegments);
        float x = radius * cosf(theta);
        float y = radius * sinf(theta);
        vertices[i * 3] = x;
        vertices[i * 3 + 1] = y;
        vertices[i * 3 + 2] = 0.0f; // Z coordinate is 0 for 2D drawing
    }

}
void Circle::ModifyColor(int GLFW_KEY,int vertexColorLocation){

    switch (GLFW_KEY)
    {
    case GLFW_KEY_1:
        if(red<=1.0f)
        red+=0.1f;
        break;
    case GLFW_KEY_2:
    if(green<=1.0f)
        green+=0.1f;
        break;
    case GLFW_KEY_3:
    if(blue<=1.0f)
        blue+=0.1f;
        break;
    case GLFW_KEY_4:
        if(red>=0.1f)
        red-=0.1f;
        break;
    case GLFW_KEY_5:
    if(green>=0.1f)
        green-=0.1f;
        break;
    case GLFW_KEY_6:
    if(blue>=0.1f)
        blue-=0.1f;
        break;
    default:
        break;
    }
    

    glUniform4f( vertexColorLocation,red , green, blue, 1.0f);
}
void Circle::Scale(GLuint uniID,int op){
    
    GLfloat aumento=0.1f;
    scale += op*aumento;
    glUniform1f(uniID, scale);
}
GLfloat Circle::GetScale(){
    return scale;
}
int Circle::GetNumOfSegments(){
    return numSegments;
}
