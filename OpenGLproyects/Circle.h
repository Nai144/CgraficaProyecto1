#include <iostream>
#include "glad/glad.h"

class Circle{

    //cantidad de segmentaciones
    int numSegments;
    //radio del circulo
    float radius;
    //valores de los colores
    float red,green,blue;
    //valores de la escala
    GLfloat scale;

    public:

    Circle();
    Circle(int _numSegments, float _radio);

    

    void PositionOfVertices(float* vertices);
    void ModifyColor(int GLFW_KEY, int vertexColorLocation);
    void Scale(GLuint uniID, int op);
    
    GLfloat GetScale();
    int GetNumOfSegments();

    float GetRed();
    float GetGreen();
    float GetBlue();


    ~Circle();



};