#ifndef SHADER_H_
#define SHADER_H_

unsigned int create_program(const char *, const char *);
const char *create_shader_source(const char *);
void destroy_shader_source(const char *);

#endif
