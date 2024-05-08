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
void Circle::ModifyColor(int color,int vertexColorLocation){

    switch (color)
    {
    case 1:
        red+=0.1f;
        break;
    case 2:
        green+=0.1f;
        break;
    case 3:
        blue+=0.1f;
        break;
    case 4:
        red-=0.1f;
        break;
    case 5:
        green-=0.1f;
        break;
    case 6:
        blue-=0.1f;
        break;
    default:
        break;
    }
    
    glUniform4f( vertexColorLocation,red , green, blue, 1.0f);
}
int Circle::GetNumOfSegments(){
    return numSegments;
}
