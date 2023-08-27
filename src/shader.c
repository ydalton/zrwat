#include <stdlib.h>

#include <GL/glew.h>

#include "shader.h"
#include "log.h"

static unsigned int compile_shader(unsigned int type, const char *src)
{
    unsigned int shader;
    int compile_ok;

    shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_ok);
    if(compile_ok == GL_FALSE) {
        LOG_E("Failed to compile shader! %s\n", "");
        return -1;
    }

    return shader;
}

static unsigned int create_program(const char *vertex, const char *fragment)
{
    unsigned int program, vs, fs;
    int link_ok;

    if(!vertex || !fragment)
        return 0;

    program = glCreateProgram();
    vs = compile_shader(GL_VERTEX_SHADER, vertex);
    if(!vs) {
        LOG_E("Failed to compile vertex shader! %s\n", "");
        return 0;
    }
    fs = compile_shader(GL_FRAGMENT_SHADER, fragment);
    if(!fs) {
        LOG_E("Failed to compile fragment shader! %s\n", "");
        return 0;
    }

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
    if(link_ok == GL_FALSE)
        return 0;

    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
}


static const char *create_shader_source(const char *path)
{
    char *shader;
    size_t file_size;
    FILE *fp;

    fp = fopen(path, "r");
    if(!fp) {
        perror("Failed to open file");
        return NULL;
    }

    /* get file size */
    fseek(fp, 0, SEEK_END);
    file_size = ftell(fp);
    rewind(fp);

    shader = (char *) malloc(file_size * sizeof(char));
    fread(shader, file_size, sizeof(char), fp);

    return shader;
}

static void destroy_shader_source(const char *ptr)
{
    if(!ptr)
        return;
    free((void *) ptr);
}

/**
 * Creates an OpenGL object handle from a vertex and fragment shader file.
 *
 * @param vertex Path to a vertex shader file.
 * @param fragment Path to a fragment shader file.
 * @return 0 if there was an error.
 */
unsigned int create_program_from_files(const char *vertex, const char *fragment)
{
    unsigned int program;
    const char *vert_src, *frag_src;

    vert_src = create_shader_source(vertex);
    if(!vert_src)
        return 0;

    frag_src = create_shader_source(fragment);
    if(!frag_src)
        return 0;

    program = create_program(vert_src, frag_src);

    destroy_shader_source(vert_src);
    destroy_shader_source(frag_src);

    return program;
}
