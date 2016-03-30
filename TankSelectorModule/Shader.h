
#ifndef _SHADER_H_
#define _SHADER_H_

#include <fstream>
#include <sstream>
#include <string>
#include <GL\glew.h>
#include "GLExceptions.h"

////////////////////////////////////////////////////////
///	Represents a openGL shader program. 
/// Reads vertex and framgent shaders from disk, 
/// compiles and links them to the shader program,
///	that is ready to use.
///
///	version 1.0
////////////////////////////////////////////////////////
class Shader {


public:
	
	/// Default constructor.
	/// Note that if you create a shader object by this constructor,
	/// you have to call bulid method first before you use this object.
	Shader() = default;

	/// Creates shader program from specified vertex and fragment shaders.
	///	vertexShaderPath		path to the vertex shader source file
	///	fragmentShaderPath		path to the fragment shader source file
	Shader(const GLchar * vertexShaderPath, const GLchar * fragmentShaderPath){
		build(vertexShaderPath, fragmentShaderPath);
	}

	/// Creates shader program from specified vertex and fragment shaders.
	///	vertexShaderPath		path to the vertex shader source file
	///	fragmentShaderPath		path to the fragment shader source file
	void build(const GLchar * vertexShaderPath, const GLchar * fragmentShaderPath);

	///	Sets this shader as the current active shader program.
	void use() const{
		glUseProgram(this->shaderProgram);
	}

	/// Returns shader program reference id
	GLuint getProgram() const{
		return shaderProgram;
	}

private:

	///Shader program ID
	GLuint shaderProgram;
};



#endif //_SHADER_H_
