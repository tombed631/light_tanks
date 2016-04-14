
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
///	version 1.2
////////////////////////////////////////////////////////
class Shader{

public:
	
	///Default constructor.
	///Note that if you create a shader object by this constructor,
	///you have to call compile method first before you use this object.
	Shader() : shaderProgram(0) {}
	
	///Creates a new shader which is a copy of other specified shader object.
	///Note that if the specified shader is not compiled, this one will not be too.
	///shader	Shader used to create a copy.
	///Throws ShaderCompileError if compilation failed.
	Shader(const Shader &);

	///Moves shader program from specified shader objects to this shader object.
	///Note that if the specified shader is not compiled, this one will not be too.
	Shader(Shader &&);

	///Assigns a copy of other specified shader object to this shader object.
	///Note that if the specified shader is not compiled, this one will not be too.
	///shader	Shader used to create a copy.
	///Throws ShaderCompileError if compilation failed.
	Shader & operator=(const Shader &);

	///Moves shader program from specified shader objects to this shader object.
	///Note that if the specified shader is not compiled, this one will not be too.
	Shader & operator=(Shader &&);


	///Creates shader program from specified vertex and fragment shaders.
	///vertexShaderPath			path to the vertex shader source file
	///fragmentShaderPath		path to the fragment shader source file
	///Throws ShaderCompileError if compilation failed
	Shader(const std::string vertexShaderPath, const std::string fragmentShaderPath) : shaderProgram(0){
		this->vertexShaderPath = vertexShaderPath;
		this->fragmentShaderPath = fragmentShaderPath;
		build();
	}

	///Deletes shader program.
	virtual ~Shader(){
		if (shaderProgram != 0)
			glDeleteProgram(shaderProgram);
	}

	///Creates shader program from specified vertex and fragment shaders.
	///Note that the current shader program will be deleted if existed
	///and the new one will be built.
	///vertexShaderPath			path to the vertex shader source file
	///fragmentShaderPath		path to the fragment shader source file
	///Throws ShaderCompileError if compilation failed
	void compile(const std::string vertexShaderPath, const std::string fragmentShaderPath) {
		this->vertexShaderPath = vertexShaderPath;
		this->fragmentShaderPath = fragmentShaderPath;
		build();
	}

	///Sets this shader as the current active shader program.
	void use() const{
		glUseProgram(this->shaderProgram);
	}

	///Returns shader program reference id.
	GLuint getProgram() const{
		return shaderProgram;
	}

	///Returns true if this shader object is compiled/built.
	bool isCompiled() const{
		return shaderProgram != 0;
	}

private:

	///Paths to the shader source files.
	std::string vertexShaderPath;
	std::string fragmentShaderPath;
	
	///Shader program ID
	GLuint shaderProgram;

	///Creates shader program from specified vertex and fragment shaders.
	///Note that the current shader program will be deleted if existed
	///and the new one will be built.
	///Throws ShaderCompileError if compilation failed.
	void build();

};



#endif //_SHADER_H_
