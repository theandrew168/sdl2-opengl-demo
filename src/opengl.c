#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "opengl.h"

// Define an OpenGL function. Until dynamically loaded, it will
// be set to NULL and should NOT be called. Doing so will cause
// a segfault.
//
// OPENGL_DEFINE(glCreateShader, PFNGLCREATESHADERPROC)
//
//   becomes
//
// PFNGLCREATESHADERPROC glCreateShader = NULL;
#define OPENGL_DEFINE(func_name, func_type)  \
    func_type func_name = NULL;

// Define all of the initally-NULL OpenGL functions.
#define OPENGL_FUNCTION OPENGL_DEFINE
OPENGL_FUNCTIONS
#undef OPENGL_FUNCTION

// Define a union that bridges the gap between object pointers
// and function pointers. This is needed because the C standard
// forbids assignment between function pointers and object pointers
// (void*, in our case). They are NOT guaranteed to be the same size.
// By pulling the void* from SDL_GL_GetProcAddress though this union,
// we ensure that the potential difference in pointer sizes is mitigated.
union bridge {
    void* proc_address;

    // Reuse the declaration macro from the header.
    #define OPENGL_FUNCTION OPENGL_DECLARE
    OPENGL_FUNCTIONS
    #undef OPENGL_FUNCTION
};

// Load an OpenGL function by passing it through the union. Check
// for errors and return from the load if something goes wrong. This
// expansion uses a C99 designated initializer to cleanly instantiate
// the union bridge. The OpenGL function pointer is then pulled out
// and assigned to the the definition that was initially NULL.
//
// In short, the void* goes in and the OpenGL function comes out.
// Using the union bridge is necesssary to keep the compilers happy
// (-std=c99 -Wall -Wextra -Wpedantic).
//
// OPENGL_LOAD(glCreateShader, PFNGLCREATESHADERPROC)
//
//   becomes
//
// glCreateShader = (union bridge){
//     .proc_address = SDL_GL_GetProcAddress("glCreateShader")
// }.glCreateShader;
// if (glCreateShader == NULL) {
//     fprintf(stderr, "failed to load func: %s\n", "glCreateShader);
//     return false;
// }
#define OPENGL_LOAD(func_name, func_type)                          \
    func_name = (union bridge){                                    \
        .proc_address = SDL_GL_GetProcAddress(#func_name)          \
    }.func_name;                                                   \
    if (func_name == NULL) {                                       \
        fprintf(stderr, "failed to load func: %s\n", #func_name);  \
        return false;                                              \
    }

bool
opengl_load_functions(void)
{
    // use SDL2's platform-agnostic loader to pull the "real" addresses
    //  out by name and assign to the definitions above
    // WARN: ISO C forbids assignment between function pointer and ‘void *’
    // the C standard defines func ptrs and object ptrs as different types
    //  that are potentially different sizes (though in practice they tend
    //  to be the same)
    //glCreateShader = SDL_GL_GetProcAddress("glCreateShader");

    // create a bridge union and pass the pointer through it

    // first way: declare bridge up top with everything and reuse an instance
//    union bridge bridge = { 0 };
//    bridge.proc_address = SDL_GL_GetProcAddress("glCreateShader");
//    glCreateShader = bridge.glCreateShader;

    // second way: create an anonymous union and init with the proc address
    //  this way would run into name collisions for the var, though
//    union {
//        void* proc_address;
//        PFNGLCREATESHADERPROC glCreateShader;
//    } bridge = { 
//        .proc_address = SDL_GL_GetProcAddress("glCreateShader"),
//    };
//    glCreateShader = bridge.glCreateShader;

    // third way: one-liner with pre-defined bridge union, uses no temp vars!
//    glCreateShader = (union bridge){
//        .proc_address = SDL_GL_GetProcAddress("glCreateShader")
//    }.glCreateShader;

    #define OPENGL_FUNCTION OPENGL_LOAD
    OPENGL_FUNCTIONS
    #undef OPENGL_FUNCTION

    return true;
}
bool
opengl_shader_compile_source(GLuint shader, const GLchar* source)
{
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success != GL_TRUE) {
        GLint info_log_length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);

        GLchar* info_log = malloc(info_log_length);
        glGetShaderInfoLog(shader, info_log_length, NULL, info_log);

        fprintf(stderr, "failed to compile shader:\n%s\n", info_log);
        free(info_log);

        return false;
    }

    return true;
}

bool
opengl_shader_link_program(GLuint program, GLuint vertex_shader, GLuint fragment_shader)
{
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (success != GL_TRUE) {
        GLint info_log_length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);

        GLchar* info_log = malloc(info_log_length);
        glGetProgramInfoLog(program, info_log_length, NULL, info_log);

        fprintf(stderr, "failed to link program:\n%s\n", info_log);
        free(info_log);

        glDetachShader(program, vertex_shader);
        glDetachShader(program, fragment_shader);

        return false;
    }

    glDetachShader(program, vertex_shader);
    glDetachShader(program, fragment_shader);
    return false;
}
