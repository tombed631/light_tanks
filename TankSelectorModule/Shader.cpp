
#include "Shader.h"

using namespace std;

///Creates shader program from specified vertex and fragment shaders.
///Note that the current shader program will be deleted if existed
///and the new one will be built.
///vertexShaderPath			path to the vertex shader source file
///fragmentShaderPath		path to the fragment shader source file
///Throws ShaderCompileError if compilation failed
void Shader::build(const GLchar * vertexShaderPath, const GLchar * fragmentShaderPath){

	const GLchar *  vertexShaderCode, * fragmentShaderCode;	//contains source code of shaders
	ifstream vertexShaderFile, fragmentShaderFile;	//for reading code from file

	GLuint vertexShader, fragmentShader;	//shader id's
	GLint success; //to determine whether compilation was succesful or not
	std::string fragmentShaderCodeStr, vertexShaderCodeStr;

	//set exception flags
	vertexShaderFile.exceptions(ifstream::badbit | ifstream::failbit);

	if (shaderProgram != 0)
		glDeleteProgram(shaderProgram);

	try{
		//open files
		vertexShaderFile.open(vertexShaderPath);	
		fragmentShaderFile.open(fragmentShaderPath);
		stringstream stream;

		//read code from files
		stream << vertexShaderFile.rdbuf();
		vertexShaderCodeStr = stream.str();
		vertexShaderCode = vertexShaderCodeStr.c_str();
		stream.clear();
		stream.str(string());	//clear sstream
		stream << fragmentShaderFile.rdbuf();
		fragmentShaderCodeStr = stream.str();
		fragmentShaderCode = fragmentShaderCodeStr.c_str();
		
		//close files
		vertexShaderFile.close();
		fragmentShaderFile.close();
	}
	catch (ifstream::failure &){
		if (vertexShaderFile.is_open())
			vertexShaderFile.close();
		if (fragmentShaderFile.is_open())
			fragmentShaderFile.close();
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
		glDeleteShader(vertexShader);
		GLchar errmsg[536] = "VERTEX:\n\n";
		strcat_s(errmsg, infoLog);
		throw ShaderCompileError(errmsg);
	}

	//Compile fragment shader
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success){
		GLchar infoLog[512];
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		GLchar errmsg[536] = "FRAGMENT:\n\n";
		strcat_s(errmsg, infoLog);
		throw ShaderCompileError(errmsg);
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
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		glDeleteProgram(shaderProgram);
		shaderProgram = 0;
		GLchar errmsg[536] = "SHD_LINK:\n\n";
		strcat_s(errmsg, infoLog);
		throw ShaderCompileError(errmsg);
	}

	//delete shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}