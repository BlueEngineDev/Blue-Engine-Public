#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

//Vertex Shader
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.0f, 1.0f);\n"
"}\n\0";

const int WINDOW_HEIGHT = 600;      //GLFW window Height
const int WINDOW_WIDTH = 600;       //GLFW window Width

int main() {
    //Initialize glfw to use functions provided and create a window
    glfwInit();

    //Giving "HINTS" to glfw for window creation
    //In this context we are telling it about the specifications of openGL
    //In this case we will use OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLfloat vertices[] = {
        -0.5f,  -0.5f * float(sqrt(3)) / 3,     0.0f,       //Lower Right Corner
        0.5f,   -0.5f * float(sqrt(3)) / 3,     0.0f,       //Lower Left Corner
        0.0f,    0.5f * float(sqrt(3)) * 2 / 3, 0.0f        //Top Corner
    };

    //Creating an openGL window
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Blue Engine", NULL, NULL);

    //Error Handiling In this case we are achecking if window creation were succsessfull and return if it was not
    if (window == NULL) {
        std::cout << "Failed To Create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    //Adding window to OpenGL context
    glfwMakeContextCurrent(window);

    //Loading the GLAD "implementation" of opengl to use the functions
    gladLoadGL();

    //Specify the opengl Viewport
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);



    //Create Vertex Shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    //Create fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    //Attach shader source code
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    //Compile the vertex shader into matchine code
    glCompileShader(fragmentShader);

    //Create shaer program and get it's reference
    GLuint shaderProgram = glCreateProgram();

    //Attach the vertex shader and get it's reference
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    //Link the shader program into one shader
    glLinkProgram(shaderProgram);

    //Deleting the shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    GLuint VAO, VBO;

    //Generating VAO and VBO as 1 objects each
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    //Binding buffer array
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);



    //Redrawing the back buffer
    
    glfwSwapBuffers(window);


    //Managing the back buffer
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);

        glfwPollEvents();
    }


    //Terminating the window clearing memory
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}