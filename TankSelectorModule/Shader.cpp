
#include "Shader.h"

using namespace std;

///Creates a new shader which is a copy of other specified shader object.
///Note that if the specified shader is not compiled, this one will not be too.
///shader	Shader used to create a copy.
///Throws ShaderCompileError if compilation failed.
Shader::Shader(const Shader & shader) {
	this->vertexShaderPath = shader.vertexShaderPath;
	this->fragmentShaderPath = shader.fragmentShaderPath;
	if (shader.isCompiled())
		build();
	else
		this->shaderProgram = 0;
}

///Moves shader program from specified shader objects to this shader object.
///Note that if the specified shader is not compiled, this one will not be too.
Shader::Shader(Shader && shader) {
	this->vertexShaderPath = shader.vertexShaderPath;
	this->fragmentShaderPath = shader.fragmentShaderPath;
	this->shaderProgram = shader.shaderProgram;
	shader.shaderProgram = 0;
}


///Assigns a copy of other specified shader object to this shader object.
///Note that if the specified shader is not compiled, this one will not be too.
///shader	Shader used to create a copy.
///Throws ShaderCompileError if compilation failed.
Shader & Shader::operator=(const Shader & shader) {
	if (this != &shader) {
		this->vertexShaderPath = shader.vertexShaderPath;
		this->fragmentShaderPath = shader.fragmentShaderPath;
		if (shader.isCompiled())
			build();	//no need to remove shader program if any exists, because bulid method do this.
		else {
			if (this->shaderProgram != 0)
				glDeleteProgram(this->shaderProgram);
			this->shaderProgram = 0;
		}
	}
	return *this;
}


///Moves shader program from specified shader objects to this shader object.
///Note that if the specified shader is not compiled, this one will not be too.
Shader & Shader::operator=(Shader && shader) {
	if (this != &shader) {
		if (this->isCompiled())
			glDeleteProgram(this->shaderProgram);
		this->vertexShaderPath = shader.vertexShaderPath;
		this->fragmentShaderPath = shader.fragmentShaderPath;
		this->shaderProgram = shader.shaderProgram;

		shader.shaderProgram = 0;
	}
	return *this;
}



///Creates shader program from specified vertex and fragment shaders.
///Note that the current shader program will be deleted if existed
///and the new one will be built.
///Throws ShaderCompileError if compilation failed.
void Shader::build(){

	const GLchar *  vertexShaderCode, * fragmentShaderCode;	//contains source code of shaders
	ifstream vertexShaderFile, fragmentShaderFile;	//for reading code from file

	GLuint vertexShader, fragmentShader;	//shader id's
	GLint success; //to determine whether compilation was succesful or not
	std::string fragmentShaderCodeStr, vertexShaderCodeStr;

	//set exception flags
	vertexShaderFile.exceptions(ifstream::badbit | ifstream::failbit);

	if (this->shaderProgram != 0)
		glDeleteProgram(shaderProgram);

	try{
		//open files
		vertexShaderFile.open(this->vertexShaderPath);	
		fragmentShaderFile.open(this->fragmentShaderPath);
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