#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <shader.h>

#include <stdio.h>
#include <stdlib.h>

unsigned int VAO;
unsigned int VBO;
unsigned int shader_program;

void setup() {
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left
        0.5f, -0.5f, 0.0f, // right
        0.0f, 0.5f, 0.0f, // top

        // -0.5f, 0.5f, 0.0f,
        // 0.5f, 0.5f, 0.0f,
        // 0.0f, 1.5f, 0.0f
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void render(shader *sh, unsigned int VAO) {
    // glUseProgram(shader_program);
    shader_use(sh);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

int initGLFW() {
    // init glfw
    if (!glfwInit()) {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, 1);
    }
}

int main() {
    if (initGLFW() < 0) {
        return -1;
    }

    // create window
    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        return -1;
    }

    // make window's context current
    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // gladLoadGL();
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return -1;
    }

    glClearColor(1.0f, 1.0f, 0.0f, 0.0f);

    // init_shaders(&shader_program, "shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");
    shader *sh = shader_init("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");
    shader_use(sh);
    // glUseProgram(shader_program);

    setup();

    // loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        processInput(window);

        render();

        // swap front and back buffers
        glfwSwapBuffers(window);
        // poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();
}
