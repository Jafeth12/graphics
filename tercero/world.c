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

world* w_create(char *title, char *vs_filename, char *fs_filename) {
    if (w_init_glfw() != 0) {
        printf("Error initializing GLFW\n");
        return 0;
    }

    world *w = malloc(sizeof(world));
    // for (int i = 0; i < MAX_TRIANGLES; i++) {
    //     w->triangles[i] = NULL;
    // }

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Hello World", NULL, NULL);
    if (!window) {
        return 0;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwTerminate();
        free(window);
        free(w);
        return 0;
    }

    w->window = window;

    shader *sh = shader_init(vs_filename, fs_filename);
    w->shader = sh;

    shader_use(sh);

    w->camera = cam_create(sh);

    float pos[] = {
        //6 porque son dos triangulos
        5, 0, 5,        // El de delante del todo a la derecha (vista de la camara, izquierda vista del homer).
        5, 0, -5,       // El de detras a la derecha (vista camara).
        -5, 0, -5,      // El de detras a la izquierda
        
        -5, 0, -5,       // Detras a la izquierda
        5, 0, 5,        // Delante a la derecha
        -5, 0, 5       // Delante a la izquierda.
    };

    glGenVertexArrays(1, &w->floor_VAO);
    glBindVertexArray(w->floor_VAO);

    glGenBuffers(1, &w->floor_VBO);

    glBindBuffer(GL_ARRAY_BUFFER, w->floor_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pos), pos, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    return w;
}

// ---------------
void processInput(world *w) {
    float movement = 0.02f;

    if (glfwGetKey(w->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(w->window, 1);
    } 

    if (glfwGetKey(w->window, GLFW_KEY_W) == GLFW_PRESS) {
        cam_move_up(w->camera);
    }

    if (glfwGetKey(w->window, GLFW_KEY_S) == GLFW_PRESS) {
        cam_move_down(w->camera);
    }

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

}
// ---------------

void w_loop(world *w) {
    // TODO poner colorecitos
    glClearColor(0.1f, 0.4f, 0.2f, 0.0f);
    glEnable(GL_DEPTH_TEST);

    shader_use(w->shader);

    while (!glfwWindowShouldClose(w->window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        processInput(w);
        w_render(w);

        // swap front and back buffers
        glfwSwapBuffers(w->window);
        // poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();
}

void w_render(world *w) {
    shader_use(w->shader);

    cam_update(w->camera);
    
    glBindVertexArray(w->floor_VAO);

    mat4 mat;
    glm_mat4_identity(mat);
    shader_set_mat4(w->shader, "model", mat);

    float col[3] = {1.0f, 0.0f, 0.0f};
    shader_set_vec3(w->shader, "color", col);

    glDrawArrays(GL_TRIANGLES, 0, 6);

}

void w_free(world *w) {
    free(w);
}
