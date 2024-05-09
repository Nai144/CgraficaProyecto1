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
void colorTriangle();

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSource ="#version 410 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "uniform float scale;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(aPos*scale, 1.0);\n"
    "}\n\0";

const char *fragmentShaderSource = "#version 410 core\n"
    "out vec4 FragColor;\n"
    "uniform vec4 ourColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = ourColor;\n"
    "}\n\0";

int vertexColorLocation;
GLuint uniID;
GLfloat escala = 1.0f, aumento = 0.1f;
Circle circle(30,0.5f,1.0f,0.0f,0.0f); 
int main(int argc, char *argv[])
{

    // glfw: initialize and configure
    // ------------------------------
   
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }else{
        std::cout << "si inicialiso GLFW" << std::endl;
    }
    glfwInit();
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    OpenGlShadder shader(vertexShaderSource,fragmentShaderSource);

    float vertices[circle.GetNumOfSegments() * 3];

    circle.PositionOfVertices(vertices);

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO);
    
    uniID = shader.GetID();

    vertexColorLocation = shader.GetIDColor();
    
    while (!glfwWindowShouldClose(window))
    {
        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // be sure to activate the shader before any calls to glUniform
        shader.Use(circle.GetScale());

        circle.ModifyColor(0,shader.GetIDColor());
        // renderizar el circulo  
        glDrawArrays(GL_TRIANGLE_FAN, 0, circle.GetNumOfSegments());
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    
    shader.DeleteProgram();
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}
// acciones de teclas
void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
		glfwSetWindowShouldClose(window, GL_TRUE);

    if((key == GLFW_KEY_1 || key == GLFW_KEY_2 ||key == GLFW_KEY_3 
      ||key == GLFW_KEY_4 ||key == GLFW_KEY_5 ||key == GLFW_KEY_6)&& action == GLFW_RELEASE){
        circle.ModifyColor(key,vertexColorLocation);
    }
    if (key == GLFW_KEY_A && action == GLFW_RELEASE)
       circle.Scale(uniID,-1);
    
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