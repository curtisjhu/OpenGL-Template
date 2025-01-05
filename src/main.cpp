#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_metal.h>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shader.h"

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(640, 480, "Template", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // GLEW INIT
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        printf("Error: %s\n", glewGetErrorString(err));
        return -1;
    }
    if (!GLEW_VERSION_2_1) {
        printf("Error: OpenGL 2.1 not supported\n");
        return -1;
    }

    Shader myShader("shaders/vert.glsl", "shaders/frag.glsl");
    float vertices[] = {
        // positions (tri)   // colors (red, green, blue)
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
    };

    // Vertex Buffer Object, Vertex Array Object
    unsigned int VBO, VAO; 
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    // buffer rotates with VAO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    while (!glfwWindowShouldClose(window))
    {

		glClear(GL_COLOR_BUFFER_BIT);

        // Uniforms
        myShader.setFloat("u_time", static_cast<float>(glfwGetTime()));
        int w, h;
        glfwGetWindowSize(window, &w, &h);
        float w_f = static_cast<float>(w);
        float h_f = static_cast<float>(h);
        glVertex2f(w_f, h_f);
        myShader.setVec2("u_resolution", w_f, h_f);
        myShader.use();

        // Draw Rectangle
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);


    glfwTerminate();
    return 0;
}