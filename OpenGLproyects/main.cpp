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
unsigned int shaderProgram;
GLuint uniID, ourColorID;
GLfloat escala = 1.0f, aumento = 0.1f;
Circle circle(30,0.5f,1.0f,0.0f,0.0f); 
//OpenGlShadder shader(vertexShaderSource,fragmentShaderSource);
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
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // link shaders
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
//    glDeleteShader(vertexShader);
//    glDeleteShader(fragmentShader);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    /*float vertices[] = {
         -0.75f, -0.75f, 0.0f,  // bottom right
          0.75f, -0.75f, 0.0f,  // bottom left
          0.0f,  0.75f, 0.0f   // top 
    };*/
    /*
    float vertices2[] = {
         -0.5f, -0.05f, 0.0f,  // bottom right
          0.5f, -0.05f, 0.0f,  // bottom left
          0.0f,  0.5f, 0.0f   // top 
    };
    *//*
    const int numSegments = 30; // Number of segments in the circle
    float radius = 0.5f;
    float vertices[numSegments * 3]; // Each vertex has 3 coordinates

    // Calculate vertices for the circle
    for (int i = 0; i < numSegments; ++i) {
        float theta = 2.0f * 3.1415926f * float(i) / float(numSegments);
        float x = radius * cosf(theta);
        float y = radius * sinf(theta);
        vertices[i * 3] = x;
        vertices[i * 3 + 1] = y;
        vertices[i * 3 + 2] = 0.0f; // Z coordinate is 0 for 2D drawing
    }
    */

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
    
    uniID = glGetUniformLocation(shaderProgram, "scale");
    printf("uniID: %d\n", shader.GetID());
    int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
    printf("ourColor: %d\n", shader.GetIDColor());
    
    while (!glfwWindowShouldClose(window))
    {
        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // be sure to activate the shader before any calls to glUniform

        glUseProgram(shaderProgram);
        glUniform1f(uniID, escala);
        //colorTriangle();

        //Codigo normal
        //glUseProgram(shaderProgram);
        //glUniform1f(uniID, circle.GetScale());
        //Codigo con clase OpenGlShadder
        shader.Use(circle.GetScale());

        // update shader uniform
        //Codigo normal
        //circle.ModifyColor(0,glGetUniformLocation(shaderProgram, "ourColor"));
        //Codigo con clase OpenGlShadder
        circle.ModifyColor(0,shader.GetIDColor());
                // render the triangle   
        glDrawArrays(GL_TRIANGLE_FAN, 0, circle.GetNumOfSegments());
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    //lineas para eliminar el segundo triangulo 
 //   glDeleteVertexArrays(1, &VAO2);
   // glDeleteBuffers(1, &VBO2);
    //Codigo normal
    //glDeleteProgram(shaderProgram);
    //Codigo del codigo
    shader.DeleteProgram();
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}
/*
void colorTriangle(){
    double  timeValue = glfwGetTime();
    float greenValue = static_cast<float>(sin(timeValue) / 2.0 + 0.5);
    float redValue = static_cast<float>(sin(timeValue) / 2.0 + 0.5);
    float blueValue = static_cast<float>(sin(timeValue) / 2.0 + 0.5);
    int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
    
    //if (vertexColorLocation >=0)
    //  cout << "Ubicación Color " << vertexColorLocation << "\n";
    //else
    //   cout << "Ubicación Color No Encontrada" << "\n";
    
    glUniform4f( vertexColorLocation,redValue , greenValue, 0.0f, 1.0f);
}
*/


void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
		glfwSetWindowShouldClose(window, GL_TRUE);
    
    if((key == GLFW_KEY_1 && action == GLFW_RELEASE)||(key == GLFW_KEY_2 && action == GLFW_RELEASE)||
       (key == GLFW_KEY_3 && action == GLFW_RELEASE)||(key == GLFW_KEY_4 && action == GLFW_RELEASE)||
       (key == GLFW_KEY_5 && action == GLFW_RELEASE)||(key == GLFW_KEY_6 && action == GLFW_RELEASE)){
        //circle.ModifyColor(key,shader.GetIDColor());
    }
    

    if (key == GLFW_KEY_A && action == GLFW_RELEASE){}
        //sizeTriangle(1);
        circle.Scale(uniID,-1);
    
    if (key == GLFW_KEY_B && action == GLFW_RELEASE){}
        //sizeTriangle(-1);
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