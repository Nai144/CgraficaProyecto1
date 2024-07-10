#include <iostream>
#include "glad/glad.h"


class Circle{

    //cantidad de segmentaciones
    int numSegments;
    //radio del circulo
    float radius;
    //valores de los colores
    float red,green,blue;
    //escala
    GLfloat scale;

    public:

    Circle();
    Circle(int _numSegments, float _radio,float _red, float _green, float _blue);

    void PositionOfVertices(float* vertices, int numCircles, float offsetX, float offsetY);
    void ModifyColor(int GLFW_KEY, int vertexColorLocation);
    void Scale(GLuint uniID, int op);
    GLfloat GetScale();
    int GetNumOfSegments();




};