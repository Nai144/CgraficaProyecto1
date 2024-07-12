#include "Circle.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <random>





Circle::Circle(int _numSegments, float _radius){
    numSegments=_numSegments;
    radius=_radius;
    std::random_device rd;
    std::mt19937 gen(rd()); // Generador de números aleatorios basado en random_device
    std::uniform_real_distribution<float> dis(0.0f, 1.0f); // Distribución uniforme entre 0 y 1

    // Generar colores aleatorios
    red = dis(gen);
    green = dis(gen);
    blue = dis(gen);
    scale=1.0f;
}

void Circle::PositionOfVertices(float* vertices) {
    int vertexIndex = 0;
    for (int j = 0; j < numSegments; ++j) {
        float theta = 2.0f * 3.1415926f * float(j) / float(numSegments);
        float x = radius * cosf(theta);
        float y = radius * sinf(theta);
        vertices[vertexIndex++] = x;
        vertices[vertexIndex++] = y;
        vertices[vertexIndex++] = 0.0f; // Coordenada Z para dibujo 2D

        float u = (cosf(theta) + 1.0f) / 2.0f;
        float v = (sinf(theta) + 1.0f) / 2.0f;
        vertices[vertexIndex++] = u;
        vertices[vertexIndex++] = v;
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
Circle::~Circle(){

}
