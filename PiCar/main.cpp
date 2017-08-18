#include <SDL2/SDL.h>
#include <SDL2/SDL_opengles2.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "GLES2/gl2.h"
#include "EGL/egl.h"
#include "EGL/eglext.h"
using namespace std;
void print_gl_string(GLenum name)
{
    const GLubyte* ret = glGetString(name);
    if (ret == 0)
    {
        std::cerr << "error getting string: " << name << std::endl;
    }
    else
    {
        std::cerr << name << ": " << ret << std::endl;
    }
}

void set_gl_attribute(SDL_GLattr attr, int value)
{
    if (SDL_GL_SetAttribute(attr, value) != 0)
    {
        std::cerr << "SDL_GL_SetAttribute(" << attr << ", " << value << ") failed: " << SDL_GetError() << std::endl;
    }
}
GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path){

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if(VertexShaderStream.is_open()){
		std::string Line = "";
		while(getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}else{
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
		getchar();
		return 0;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if(FragmentShaderStream.is_open()){
		std::string Line = "";
		while(getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;


	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}



	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}



	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}


	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}
int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL_Init() failed: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    SDL_DisplayMode videomode;
    if (SDL_GetCurrentDisplayMode (0, &videomode) != 0)
    {
        std::cerr << "Error getting current display mode: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Current screen mode: " << videomode.w << "x" << videomode.h << std::endl;

    set_gl_attribute(SDL_GL_RED_SIZE, 5);
    set_gl_attribute(SDL_GL_GREEN_SIZE, 6);
    set_gl_attribute(SDL_GL_BLUE_SIZE, 5);
    //set_gl_attribute(SDL_GL_DEPTH_SIZE, 8);
    set_gl_attribute(SDL_GL_DOUBLEBUFFER, 1);

    set_gl_attribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    set_gl_attribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    set_gl_attribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);

    SDL_Window* window = SDL_CreateWindow("Minimal SDL2 Example",
                                            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                            720, 576,
                                            SDL_WINDOW_OPENGL);
    if (!window)
    {
        std::cerr << "Could not create window: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    SDL_GLContext gl_context = SDL_GL_CreateContext(window);

    print_gl_string(GL_RENDERER);
    print_gl_string(GL_SHADING_LANGUAGE_VERSION);
    print_gl_string(GL_VERSION);
    print_gl_string(GL_EXTENSIONS);

    glClearColor(1.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    //
    GLuint programID = LoadShaders( "vt.txt", "fr.txt" );
    glUseProgram(programID);
    GLfloat vVertices[] =
    {
    0.0f, 1.0f, 0.0f,
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f
    };

    // Set the viewport
    glViewport(0, 0, videomode.w, videomode.h);

    glClear(GL_COLOR_BUFFER_BIT);
    // Load the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
    glEnableVertexAttribArray(0);
    //=====

    glDrawArrays(GL_TRIANGLES, 0, 3);
    //
    SDL_GL_SwapWindow(window);

    SDL_Delay(5000);

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();

  return 0;
}
