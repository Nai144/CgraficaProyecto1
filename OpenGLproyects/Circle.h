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

    void ModifyColor(int color, int vertexColorLocation);
    void PositionOfVertices(float vertices[]);
    void Scale(GLuint uniID,int op);
    GLfloat GetScale();
    int GetNumOfSegments();



};