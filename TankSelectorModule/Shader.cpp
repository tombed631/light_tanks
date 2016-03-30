
#include "Shader.h"

using namespace std;

/// Creates shader program from specified vertex and fragment shaders.
///	vertexShaderPath		path to the vertex shader source file
///	fragmentShaderPath		path to the fragment shader source file
void Shader::build(const GLchar * vertexShaderPath, const GLchar * fragmentShaderPath){

	const GLchar *  vertexShaderCode, * fragmentShaderCode;	//contains source code of shaders
	ifstream vertexShaderFile, fragmentShaderFile;	//for reading code from file

	GLuint vertexShader, fragmentShader;	//shader id's
	GLint success; //to determine whether compilation was succesful or not

	//set exception flags
	vertexShaderFile.exceptions(ifstream::badbit | ifstream::failbit);

	try{
		//open files
		vertexShaderFile.open(vertexShaderPath);	
		fragmentShaderFile.open(fragmentShaderPath);
		stringstream stream;

		//read code from files
		stream << vertexShaderFile.rdbuf();
		vertexShaderCode = stream.str().c_str();
		stream.clear();
		stream.str(string());	//clear sstream
		stream << fragmentShaderFile.rdbuf();
		fragmentShaderCode = stream.str().c_str();
		
		//close files
		vertexShaderFile.close();
		fragmentShaderFile.close();
	}
	catch (ifstream::failure & e){
		throw ShaderCompileError("An error occured during reafing shader source files");
	}

	//Compile vertex shader
	vertexShader = glCreateShader(GL_VERTEX_SHADER);	//create shader
	glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);	//set shader source
	glCompileShader(vertexShader);	//compile shader
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);	//check if any error occured
	if (!success){
		GLchar infoLog[512];
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		throw ShaderCompileError(infoLog);
	}

	//Compile fragment shader
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success){
		GLchar infoLog[512];
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		throw ShaderCompileError(infoLog);
	}

	//Create program
	this->shaderProgram = glCreateProgram();
	glAttachShader(this->shaderProgram, vertexShader);	//attach shaders
	glAttachShader(this->shaderProgram, fragmentShader);
	glLinkProgram(this->shaderProgram);	//link shaders in the shader program
	glGetProgramiv(this->shaderProgram, GL_LINK_STATUS, &success);
	if (!success){
		GLchar infoLog[512];
		glGetProgramInfoLog(this->shaderProgram, 512, NULL, infoLog);
		throw ShaderCompileError(infoLog);
	}

	//delete shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}