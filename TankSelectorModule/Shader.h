
#ifndef _SHADER_H_
#define _SHADER_H_

#include <fstream>
#include <sstream>
#include <string>
#include <GL\glew.h>
#include "GLExceptions.h"


////////////////////////////////////////////////////////
///	Represents a openGL shader program. 
///	Reads vertex and framgent shaders from disk, 
///	compiles and links them to the shader program,
///	that is ready to use.
///
///	version 1.1
////////////////////////////////////////////////////////
class Shader final {

public:
	
	///Default constructor.
	///Note that if you create a shader object by this constructor,
	///you have to call bulid method first before you use this object.
	Shader() : shaderProgram(0) {}

	///Creates shader program from specified vertex and fragment shaders.
	///vertexShaderPath			path to the vertex shader source file
	///fragmentShaderPath		path to the fragment shader source file
	///Throws ShaderCompileError if compilation failed
	Shader(const GLchar * vertexShaderPath, const GLchar * fragmentShaderPath) : shaderProgram(0){
		build(vertexShaderPath, fragmentShaderPath);
	}

	///Deletes shader program.
	~Shader(){
		if (shaderProgram != 0)
			glDeleteProgram(shaderProgram);
	}

	///Creates shader program from specified vertex and fragment shaders.
	///Note that the current shader program will be deleted if existed
	///and the new one will be built.
	///vertexShaderPath			path to the vertex shader source file
	///fragmentShaderPath		path to the fragment shader source file
	///Throws ShaderCompileError if compilation failed
	void build(const GLchar * vertexShaderPath, const GLchar * fragmentShaderPath);

	///Sets this shader as the current active shader program.
	void use() const{
		glUseProgram(this->shaderProgram);
	}

	///Returns shader program reference id
	GLuint getProgram() const{
		return shaderProgram;
	}

private:

	///Shader program ID
	GLuint shaderProgram;

	//Shader non-copyable and non-movable
	Shader(const Shader &) = delete;
	Shader(Shader &&) = delete;
	Shader & operator=(const Shader &) = delete;
	Shader & operator=(Shader &&) = delete;

};



#endif //_SHADER_H_
