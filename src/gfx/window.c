#include "window.h"

void win_framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int win_init_glfw(void) {
    if (!glfwInit()) {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    return 0;
}

window *win_create(GLuint width, GLuint height, const char *title, void (*custom_loop)(void*arg), void* args) {
    if (win_init_glfw() < 0) return NULL;

    window *win = malloc(sizeof(window));
    win->width = width;
    win->height = height;
    win->title = title;
    win->custom_loop = custom_loop;
    win->custom_args = args;

    GLFWwindow *handle = glfwCreateWindow(width, height, title, NULL, NULL);
    win->handle = handle;

    glfwMakeContextCurrent(handle);
    glfwSetFramebufferSizeCallback(handle, win_framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        win_destroy(win);
        return 0;
    }

    return win;
}

void win_mouse_set_grabbed(window *win, char grabbed) {
    win->mouse_grabbed = grabbed;
    // glfwSetInputMode(win->handle, GLFW_CURSOR, grabbed ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}

void win_loop(window *win) {
    glClearColor(0.2f, 1.0f, 1.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);

    void (*custom_loop)(void*arg) = win->custom_loop;

    float last_frame = 0.0f;
    float delta_time = 0.0f;

    while (!glfwWindowShouldClose(win->handle)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float current_frame = glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;
        win->delta_time = delta_time;

        win->elapsed_time += delta_time;

        if (custom_loop != NULL) (*custom_loop)(win->custom_args);

        // swap front and back buffers
        glfwSwapBuffers(win->handle);
        // poll for and process events
        glfwPollEvents();
    }
}

void win_destroy(window *win) {
    glfwDestroyWindow(win->handle);
    glfwTerminate();
    free(win);
}
