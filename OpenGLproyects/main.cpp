#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "Circle.h"
#include "OpenGlShadder.h"

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode);
int readNumberOfCircles(const std::string& fileName); 

// settings
const unsigned int SCR_WIDTH = 1080;
const unsigned int SCR_HEIGHT = 920;

int vertexColorLocation;
GLuint uniID, ourColorID;
GLfloat escala = 1.0f, aumento = 0.1f;
Circle circle(30, 0.125f); 
int numCircles; 
float offset = 0;

int main(int argc, char *argv[])
{
    numCircles = readNumberOfCircles("ENTRADA.TXT");

    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    } 
    else 
    {
        std::cout << "GLFW initialized successfully" << std::endl;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetKeyCallback(window, glfw_onKey);

    OpenGlShadder shader;

    int numVertices = circle.GetNumOfSegments();
    float* vertices = new float[numVertices * 5]; // Corregido: Asegurarse de tener suficiente espacio para coordenadas y texturas
    circle.PositionOfVertices(vertices);

    shader.loadTextures();

    unsigned int VBO, VAO, IBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &IBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, numVertices * 5 * sizeof(float), vertices, GL_STATIC_DRAW);

    unsigned int* indices = new unsigned int[circle.GetNumOfSegments()];
    for (int j = 0; j < circle.GetNumOfSegments(); ++j) 
    {
        indices[j] = j;
    }
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, circle.GetNumOfSegments() * sizeof(unsigned int), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    uniID = shader.GetID();
    vertexColorLocation = shader.GetIDColor();

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.Use(circle.GetScale());
        //circle.ModifyColor(0, vertexColorLocation);

        glBindVertexArray(VAO);
        
        for (int i = 0; i < numCircles; ++i) 
        {
            float offsetX = (i % 3) * (0.25f + offset) - 0.5f;
            float offsetY = (i / 3) * (0.25f + offset) - 0.5f;
            glUniform2f(shader.GetIDOffset(), offsetX, offsetY);
            
            if (i == 0 || i == numCircles - 1) 
            {
                glBindTexture(GL_TEXTURE_2D, shader.GetIDTexture());
            } 
            else 
            {
                glBindTexture(GL_TEXTURE_2D, 0); // Sin textura
                
                
            }
            circle.ModifyColor(0,vertexColorLocation);
            //glUniform4fv(circles[i].getOurColorID(), 1, circles[i].getCurrentColor());
            glDrawElements(GL_TRIANGLE_FAN, circle.GetNumOfSegments(), GL_UNSIGNED_INT, 0);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &IBO);
    delete[] vertices;
    delete[] indices;
    shader.DeleteProgram();

    glfwTerminate();
    return 0;
}

void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
        glfwSetWindowShouldClose(window, GL_TRUE);
    
    if ((key == GLFW_KEY_1 && action == GLFW_RELEASE) || 
        (key == GLFW_KEY_2 && action == GLFW_RELEASE) || 
        (key == GLFW_KEY_3 && action == GLFW_RELEASE) || 
        (key == GLFW_KEY_4 && action == GLFW_RELEASE) || 
        (key == GLFW_KEY_5 && action == GLFW_RELEASE) || 
        (key == GLFW_KEY_6 && action == GLFW_RELEASE))
    {
        circle.ModifyColor(key, vertexColorLocation);
    }

    if (key == GLFW_KEY_A && action == GLFW_RELEASE)
        circle.Scale(uniID, 1);
        
    if (key == GLFW_KEY_B && action == GLFW_RELEASE)
        circle.Scale(uniID, -1);

    offset += ((key == GLFW_KEY_A && action == GLFW_RELEASE)) ? 0.025f : ((key == GLFW_KEY_B && action == GLFW_RELEASE)) ? -0.025f : 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int readNumberOfCircles(const std::string& fileName) 
{
    std::ifstream file(fileName);
    if (!file) 
    {
        std::cerr << "Failed to open file: " << fileName << std::endl;
        return 0;
    }

    int N;
    file >> N;
    file.close();
    return N;
}