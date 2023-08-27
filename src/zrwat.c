#include <GL/glew.h>

#include "zrwat.h"
#include "log.h"
#include "shader.h"
#include "game.h"

int zrwat_init(struct game *g)
{
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
        LOG_E("Cannot initialize GLEW! %s\n", "");
        return -1;
    }

    glViewport(0, 0, g->width, g->height);

    g->program = create_program_from_files("./shaders/test/vertex.glsl", "./shaders/test/fragment.glsl");

    if(!g->program) {
        LOG_E("Failed to create program! %s\n", "");
        return -1;
    }

    return 0;
}


static unsigned int zrwat_event_handler(SDL_Event *ev, struct game *g)
{
    unsigned int should_quit = 0;

    switch(ev->type) {
        case SDL_QUIT:
            should_quit = 1;
            break;
        case SDL_MOUSEBUTTONDOWN:
            game_logic(&g->zrwat);
            break;
    }
    return should_quit;
}

void zrwat_render() {}

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

    g->zrwat = game_init();

    while(1) {
        SDL_Event ev;
        SDL_PollEvent(&ev);
        if(zrwat_event_handler(&ev, g))
            return;
        glClearColor(BG_GRAY, 1.0);
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
