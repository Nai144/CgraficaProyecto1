#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include "Circle.h"
#include "OpenGlShadder.h"

using namespace std;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode);


// settings
const unsigned int SCR_WIDTH = 1080;
const unsigned int SCR_HEIGHT = 920;

int vertexColorLocation;

GLuint uniID, ourColorID;
GLfloat escala = 1.0f, aumento = 0.1f;
Circle circle(30, 0.125f, 1.0f, 0.0f, 0.0f); 
int numCircles = 16; // Número de círculos a dibujar

int main(int argc, char *argv[])
{
    // glfw: initialize and configure
    // ------------------------------
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    } else {
        std::cout << "si inicializo GLFW" << std::endl;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetKeyCallback(window, glfw_onKey);

    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    OpenGlShadder shader;

    int numVertices = circle.GetNumOfSegments();
    float* vertices = new float[numVertices * 3];
    circle.PositionOfVertices(vertices);

    unsigned int VBO, VAO, IBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &IBO);  // Generate IBO

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, numVertices * 3 * sizeof(float), vertices, GL_STATIC_DRAW);

/*
    unsigned int* indices = new unsigned int[numCircles * circle.GetNumOfSegments()];
    for (int i = 0; i < numCircles; ++i) {
        for (int j = 0; j < circle.GetNumOfSegments(); ++j) {
            indices[i * circle.GetNumOfSegments() + j] = j;
        }
    }
*/
    unsigned int* indices = new unsigned int[circle.GetNumOfSegments()];
    for (int j = 0; j < circle.GetNumOfSegments(); ++j) {
        indices[j] = j;
    }
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, numCircles * circle.GetNumOfSegments() * sizeof(unsigned int), indices, GL_STATIC_DRAW);
     glBufferData(GL_ELEMENT_ARRAY_BUFFER, circle.GetNumOfSegments() * sizeof(unsigned int), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    uniID = shader.GetID();
    printf("uniID: %d\n", uniID);
    vertexColorLocation = shader.GetIDColor();
    printf("ourColor: %d\n", vertexColorLocation);

    while (!glfwWindowShouldClose(window))
    {
        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // be sure to activate the shader before any calls to glUniform
        shader.Use(circle.GetScale());
        // update shader uniform
        circle.ModifyColor(0, vertexColorLocation);

        // render the circles
        glBindVertexArray(VAO);
        for (int i = 0; i < numCircles; ++i) {
            float offsetX = (i % 3) * 0.25f - 0.5f;
            float offsetY = (i / 3) * 0.25f- 0.5f;
            //shader.UseLocation(offsetX,offsetY);
            glUniform2f(shader.GetIDOffset(), offsetX, offsetY);
            glDrawElements(GL_TRIANGLE_FAN, circle.GetNumOfSegments(), GL_UNSIGNED_INT, 0);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &IBO);
    delete[] vertices;
    delete[] indices;
    shader.DeleteProgram();

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}



void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
		glfwSetWindowShouldClose(window, GL_TRUE);
    
    if((key == GLFW_KEY_1 && action == GLFW_RELEASE)||(key == GLFW_KEY_2 && action == GLFW_RELEASE)||
       (key == GLFW_KEY_3 && action == GLFW_RELEASE)||(key == GLFW_KEY_4 && action == GLFW_RELEASE)||
       (key == GLFW_KEY_5 && action == GLFW_RELEASE)||(key == GLFW_KEY_6 && action == GLFW_RELEASE)){
        circle.ModifyColor(key,vertexColorLocation);
    }
    

    if (key == GLFW_KEY_A && action == GLFW_RELEASE)
        circle.Scale(uniID,1);
        
    
    if (key == GLFW_KEY_B && action == GLFW_RELEASE)
        circle.Scale(uniID,-1);

}



// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}