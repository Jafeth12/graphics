#include <world.h>

int points = 0;

//---------------

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

//---------------

int w_init_glfw() {
    if (!glfwInit()) {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    return 0;
}

world* w_create(int width, int height, char *title, char *vs_filename, char *fs_filename) {
    if (w_init_glfw() != 0) {
        printf("Error initializing GLFW\n");
        return 0;
    }

    world *w = malloc(sizeof(world));
    for (int i = 0; i < MAX_TRIANGLES; i++) {
        w->triangles[i] = NULL;
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

    w->window = window;

    shader *sh = shader_init(vs_filename, fs_filename);
    w->shader = sh;

    shader_use(sh);

    w->camera = camera_create(sh);

    return w;
}

// int win_add_triangle(window *win, triangle *tri) {
//     for (int i = 0; i < MAX_TRIANGLES; i++) {
//         if (win->triangles[i] == NULL) {
//             if (i == TRI_PLAYER) tri_move_random(tri);
//             win->triangles[i] = tri;
//             return 0;
//         }
//     }
//
//     return -1;
// }

// void win_draw_triangles(window *win) {
//     for (int i = 0; i < MAX_TRIANGLES; i++) {
//         if (win->triangles[i] != NULL) {
//             tri_draw(win->triangles[i], win->shader);
//         }
//     }
// }

// void processCollision(window *win) {
//     if (win->triangles[TRI_PLAYER] == NULL || win->triangles[TRI_APPLE] == NULL) {
//         return;
//     }
//
//     if (tri_collision(win->triangles[TRI_PLAYER], win->triangles[TRI_APPLE])) {
//         tri_move_random(win->triangles[TRI_APPLE]);
//         ++points;
//         printf("Points: %d\n", points);
//     }
// }

// ---------------
void processInput(world *w) {
    float movement = 0.02f;

    if (glfwGetKey(w->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(w->window, 1);
    } 

    // if (glfwGetKey(world->window, GLFW_KEY_D) == GLFW_PRESS) {
    //     tri_move_right(world->triangles[TRI_PLAYER], movement);
    // } 
    //
    // if (glfwGetKey(world->window, GLFW_KEY_A) == GLFW_PRESS) {
    //     tri_move_left(world->triangles[TRI_PLAYER], movement);
    // } 
    //
    // if (glfwGetKey(world->window, GLFW_KEY_W) == GLFW_PRESS) {
    //     tri_move_up(world->triangles[TRI_PLAYER], movement);
    // } 
    //
    // if (glfwGetKey(world->window, GLFW_KEY_S) == GLFW_PRESS) {
    //     tri_move_down(world->triangles[TRI_PLAYER], movement);
    // }

    if (glfwGetKey(w->window, GLFW_KEY_UP) == GLFW_PRESS) {
        cam_move_forward(w->camera);
    }

    if (glfwGetKey(w->window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        cam_move_backward(w->camera);
    }

    if (glfwGetKey(w->window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        cam_move_left(w->camera);
    }

    if (glfwGetKey(w->window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        cam_move_right(w->camera);
    }

    // processCollision(world);
}
// ---------------

void w_loop(world *w) {
    // TODO poner colorecitos
    glClearColor(0.1f, 0.4f, 0.2f, 0.0f);
    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(w->window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        processInput(w);
        // win_draw_triangles(world);

        // swap front and back buffers
        glfwSwapBuffers(w->window);
        // poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();

    // free(world);
}

void w_free(world *w) {
    free(w);
}
