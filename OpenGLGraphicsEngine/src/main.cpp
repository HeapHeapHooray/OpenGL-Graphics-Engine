#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window,int width,int height)
{
    glViewport(0,0,width,height);
}

void initialize()
{
    glfwInit();
}

void terminate()
{
    glfwTerminate();
}

void clear_window()
{
    glClearColor(0.0f,0.5f,0.5f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void update_window(GLFWwindow* window)
{
    glfwSwapBuffers(window);
    glfwPollEvents();
}

unsigned int create_vertex_shader()
{
    const char *source = 
    R"(#version 330 core
    layout (location = 0) in vec3 vertexPosition;
    
    void main()
    {
     gl_Position = vec4(vertexPosition.x,vertexPosition.y,vertexPosition.z,1.0);   
    })";

    const unsigned int shader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(shader,1,&source,NULL);
    glCompileShader(shader);

    return shader;
}

unsigned int create_fragment_shader()
{
    const char *source =
    R"(#version 330 core
    out vec4 fragColor;
    
    void main()
    {
        fragColor = vec4(1.0f,1.0f,1.0f,1.0f);
    })";

    const unsigned int shader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(shader,1,&source,NULL);
    glCompileShader(shader);

    return shader;
}

unsigned int create_shader_program(const unsigned int vertexShader,const unsigned int fragmentShader)
{
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);

    return shaderProgram;
}

void draw_loop()
{
    initialize();
    GLFWwindow* window = glfwCreateWindow(800,600,"Test",NULL,NULL);
    glfwMakeContextCurrent(window);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);

    float vertices[] = {-0.5f,-0.5f,0.0f,
                         0.5f,-0.5f,0.0f,
                         0.0f,0.5f,0.0f};

    unsigned int vbo;
    glGenBuffers(1,&vbo);

    unsigned int vao;
    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER,vbo);

    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);


    unsigned int vertexShader = create_vertex_shader();
    unsigned int fragmentShader = create_fragment_shader();

    unsigned int shaderProgram = create_shader_program(vertexShader,fragmentShader);

    glUseProgram(shaderProgram);

    while(!glfwWindowShouldClose(window))
    {
        clear_window();
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES,0,3);
        update_window(window);
    }
    terminate();
}

int main()
{
    draw_loop();
    return 0;
}