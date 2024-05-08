#include <iostream>


class Circle{

    //valores de los colores
    int numSegments;
    float radius,red,green,blue;

    public:

    Circle();
    Circle(int _numSegments, float _radio,float _red, float _green, float _blue);

    void ModifyColor(int color, int vertexColorLocation);
    void PositionOfVertices(float vertices[]);
    int GetNumOfSegments();



};