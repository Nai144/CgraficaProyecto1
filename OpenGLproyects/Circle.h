#include <iostream>


class Circle{

    //cantidad de segmentaciones
    int numSegments;
    //radio del circulo
    float radius;
    //valores de los colores
    float red,green,blue;

    public:

    Circle();
    Circle(int _numSegments, float _radio,float _red, float _green, float _blue);

    void ModifyColor(int color, int vertexColorLocation);
    void PositionOfVertices(float vertices[]);
    void Scale();
    int GetNumOfSegments();



};