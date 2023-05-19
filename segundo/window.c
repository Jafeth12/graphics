#include <window.h>

//---------------

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

//---------------

int win_init_glfw() {
    if (!glfwInit()) {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    return 0;
}

window* win_create(int width, int height, char *title, char *vs_filename, char *fs_filename) {
    window *win = malloc(sizeof(window));
    for (int i = 0; i < MAX_TRIANGLES; i++) {
        win->triangles[i] = NULL;
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        return 0;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return 0;
    }

    win->window = window;

    shader *sh = shader_init(vs_filename, fs_filename);
    win->shader = sh;
    // shader_use(sh);

    return win;
}

void win_add_triangle(window *win, float red, float green, float blue, float scale) {
    for (int i = 0; i < MAX_TRIANGLES; i++) {
        if (win->triangles[i] == NULL) {
            triangle *tri = tri_new(red, green, blue, scale);
            win->triangles[i] = tri;
            break;
        }
    }
}

void win_draw_triangles(window *win) {
    for (int i = 0; i < MAX_TRIANGLES; i++) {
        if (win->triangles[i] != NULL) {
            tri_draw(win->triangles[i], win->shader);
        }
    }
}

void win_loop(window *win) {
    // TODO poner colorecitos
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    while (!glfwWindowShouldClose(win->window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // processInput(win);
        win_draw_triangles(win);

        // swap front and back buffers
        glfwSwapBuffers(win->window);
        // poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();
    free(win);
}
