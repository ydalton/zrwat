#include <GL/glew.h>

#include "zrwat.h"
#include "log.h"
#include "shader.h"

int zrwat_init(struct game *g)
{
    const char *vertex_src, *fragment_src;

    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        LOG_E("SDL failed to initialise: %s\n", SDL_GetError());
        return -1;
    }

    g->win = SDL_CreateWindow(g->name,
                           SDL_WINDOWPOS_UNDEFINED,
                           SDL_WINDOWPOS_UNDEFINED,
                           g->width,
                           g->height,
                           SDL_WINDOW_OPENGL);
    if(!g->win) {
        LOG_E("Cannot create window: %s\n", SDL_GetError());
        return -1;
    }

    SDL_GL_CreateContext(g->win);

    if(glewInit() != GLEW_OK) {
        LOG_E("Cannot initialize GLEW! %s", "");
        return -1;
    }

    glViewport(0, 0, g->width, g->height);

    vertex_src = create_shader_source("./shaders/test/vertex.glsl");
    fragment_src = create_shader_source("./shaders/test/fragment.glsl");

    g->program = create_program(vertex_src, fragment_src);

    destroy_shader_source(vertex_src);
    destroy_shader_source(fragment_src);

    if(!g->program) {
        LOG_E("Failed to create program!\n");
        return -1;
    }

    return 0;
}


unsigned int zrwat_event_handler(SDL_Event *ev)
{
    unsigned int should_quit = 0;

    switch(ev->type) {
        case SDL_QUIT:
            should_quit = 1;
            break;
    }
    return should_quit;
}

void zrwat_render(struct game *g)
{

}

void zrwat_loop(struct game *g)
{
    unsigned int vao, vbo;

    float verts[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };

    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
    glEnableVertexAttribArray(0);

    while(1) {
        SDL_Event ev;
        SDL_PollEvent(&ev);
        if(zrwat_event_handler(&ev))
            return;
        glClearColor(0.0, 0.5, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        /* zrwat_render(g); */
        glUseProgram(g->program);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        SDL_GL_SwapWindow(g->win);
    }
}

void zrwat_end(struct game *g)
{
    SDL_DestroyWindow(g->win);
    SDL_Quit();
}
