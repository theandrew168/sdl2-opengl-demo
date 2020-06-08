#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "opengl.h"

// implementation pointers for the opengl funcs
PFNGLCREATESHADERPROC glCreateShader = NULL;
PFNGLDELETESHADERPROC glDeleteShader = NULL;
PFNGLATTACHSHADERPROC glAttachShader = NULL;
PFNGLDETACHSHADERPROC glDetachShader = NULL;
PFNGLSHADERSOURCEPROC glShaderSource = NULL;
PFNGLCOMPILESHADERPROC glCompileShader = NULL;
PFNGLGETSHADERIVPROC glGetShaderiv = NULL;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = NULL;
PFNGLCREATEPROGRAMPROC glCreateProgram = NULL;
PFNGLDELETEPROGRAMPROC glDeleteProgram = NULL;
PFNGLUSEPROGRAMPROC glUseProgram = NULL;
PFNGLLINKPROGRAMPROC glLinkProgram = NULL;
PFNGLVALIDATEPROGRAMPROC glValidateProgram = NULL;
PFNGLGETPROGRAMIVPROC glGetProgramiv = NULL;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = NULL;
PFNGLUNIFORM1IPROC glUniform1i = NULL;
PFNGLUNIFORM1FPROC glUniform1f = NULL;
PFNGLUNIFORM3FPROC glUniform3f = NULL;
PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv = NULL;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = NULL;
PFNGLGENBUFFERSPROC glGenBuffers = NULL;
PFNGLDELETEBUFFERSPROC glDeleteBuffers = NULL;
PFNGLBINDBUFFERPROC glBindBuffer = NULL;
PFNGLBUFFERDATAPROC glBufferData = NULL;
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays = NULL;
PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays = NULL;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray = NULL;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = NULL;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = NULL;
PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray = NULL;

// union to bridge the gap between object and function pointers
union bridge {
    void* proc_address;
    PFNGLCREATESHADERPROC glCreateShader;
    PFNGLDELETESHADERPROC glDeleteShader;
    PFNGLATTACHSHADERPROC glAttachShader;
    PFNGLDETACHSHADERPROC glDetachShader;
    PFNGLSHADERSOURCEPROC glShaderSource;
    PFNGLCOMPILESHADERPROC glCompileShader;
    PFNGLGETSHADERIVPROC glGetShaderiv;
    PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
    PFNGLCREATEPROGRAMPROC glCreateProgram;
    PFNGLDELETEPROGRAMPROC glDeleteProgram;
    PFNGLUSEPROGRAMPROC glUseProgram;
    PFNGLLINKPROGRAMPROC glLinkProgram;
    PFNGLVALIDATEPROGRAMPROC glValidateProgram;
    PFNGLGETPROGRAMIVPROC glGetProgramiv;
    PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
    PFNGLUNIFORM1IPROC glUniform1i;
    PFNGLUNIFORM1FPROC glUniform1f;
    PFNGLUNIFORM3FPROC glUniform3f;
    PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
    PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
    PFNGLGENBUFFERSPROC glGenBuffers;
    PFNGLDELETEBUFFERSPROC glDeleteBuffers;
    PFNGLBINDBUFFERPROC glBindBuffer;
    PFNGLBUFFERDATAPROC glBufferData;
    PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
    PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
    PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
    PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
    PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
    PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
};

bool
opengl_load_functions(void)
{
    // TODO: Make this less repetitive (macros?)
    // TODO: Check for failed func grabs

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
    glCreateShader = (union bridge){
        .proc_address = SDL_GL_GetProcAddress("glCreateShader")
    }.glCreateShader;

    glCreateShader = (union bridge){
        .proc_address = SDL_GL_GetProcAddress("glCreateShader")
    }.glCreateShader;

    glDeleteShader = (union bridge){
        .proc_address = SDL_GL_GetProcAddress("glDeleteShader")
    }.glDeleteShader;

    glAttachShader = (union bridge){
        .proc_address = SDL_GL_GetProcAddress("glAttachShader")
    }.glAttachShader;

    glDetachShader = (union bridge){
        .proc_address = SDL_GL_GetProcAddress("glDetachShader")
    }.glDetachShader;

    glShaderSource = (union bridge){
        .proc_address = SDL_GL_GetProcAddress("glShaderSource")
    }.glShaderSource;

    glCompileShader = (union bridge){
        .proc_address = SDL_GL_GetProcAddress("glCompileShader")
    }.glCompileShader;

    glGetShaderiv = (union bridge){
        .proc_address = SDL_GL_GetProcAddress("glGetShaderiv")
    }.glGetShaderiv;

    glGetShaderInfoLog = (union bridge){
        .proc_address = SDL_GL_GetProcAddress("glGetShaderInfoLog")
    }.glGetShaderInfoLog;

    glCreateProgram = (union bridge){
        .proc_address = SDL_GL_GetProcAddress("glCreateProgram")
    }.glCreateProgram;

    glDeleteProgram = (union bridge){
        .proc_address = SDL_GL_GetProcAddress("glDeleteProgram")
    }.glDeleteProgram;

    glUseProgram = (union bridge){
        .proc_address = SDL_GL_GetProcAddress("glUseProgram")
    }.glUseProgram;

    glLinkProgram = (union bridge){
        .proc_address = SDL_GL_GetProcAddress("glLinkProgram")
    }.glLinkProgram;

    glValidateProgram = (union bridge){
        .proc_address = SDL_GL_GetProcAddress("glValidateProgram")
    }.glValidateProgram;

    glGetProgramiv = (union bridge){
        .proc_address = SDL_GL_GetProcAddress("glGetProgramiv")
    }.glGetProgramiv;

    glGetProgramInfoLog = (union bridge){
        .proc_address = SDL_GL_GetProcAddress("glGetProgramInfoLog")
    }.glGetProgramInfoLog;

    glUniform1i = (union bridge){
        .proc_address = SDL_GL_GetProcAddress("glUniform1i")
    }.glUniform1i;

    glUniform1f = (union bridge){
        .proc_address = SDL_GL_GetProcAddress("glUniform1f")
    }.glUniform1f;

    glUniform3f = (union bridge){
        .proc_address = SDL_GL_GetProcAddress("glUniform3f")
    }.glUniform3f;

    glUniformMatrix4fv = (union bridge){
        .proc_address = SDL_GL_GetProcAddress("glUniformMatrix4fv")
    }.glUniformMatrix4fv;

    glGetUniformLocation = (union bridge){
        .proc_address = SDL_GL_GetProcAddress("glGetUniformLocation")
    }.glGetUniformLocation;

    glGenBuffers = (union bridge){
        .proc_address = SDL_GL_GetProcAddress("glGenBuffers")
    }.glGenBuffers;

    glDeleteBuffers = (union bridge){
        .proc_address = SDL_GL_GetProcAddress("glDeleteBuffers")
    }.glDeleteBuffers;

    glBindBuffer = (union bridge){
        .proc_address = SDL_GL_GetProcAddress("glBindBuffer")
    }.glBindBuffer;

    glBufferData = (union bridge){
        .proc_address = SDL_GL_GetProcAddress("glBufferData")
    }.glBufferData;

    glGenVertexArrays = (union bridge){
        .proc_address = SDL_GL_GetProcAddress("glGenVertexArrays")
    }.glGenVertexArrays;

    glDeleteVertexArrays = (union bridge){
        .proc_address = SDL_GL_GetProcAddress("glDeleteVertexArrays")
    }.glDeleteVertexArrays;

    glBindVertexArray = (union bridge){
        .proc_address = SDL_GL_GetProcAddress("glBindVertexArray")
    }.glBindVertexArray;

    glVertexAttribPointer = (union bridge){
        .proc_address = SDL_GL_GetProcAddress("glVertexAttribPointer")
    }.glVertexAttribPointer;

    glEnableVertexAttribArray = (union bridge){
        .proc_address = SDL_GL_GetProcAddress("glEnableVertexAttribArray")
    }.glEnableVertexAttribArray;

    glDisableVertexAttribArray = (union bridge){
        .proc_address = SDL_GL_GetProcAddress("glDisableVertexAttribArray")
    }.glDisableVertexAttribArray;

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
