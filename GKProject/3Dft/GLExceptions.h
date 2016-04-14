
#ifndef _GL_EXCEPTIONS_
#define _GL_EXCEPTIONS_

#include <stdexcept>

namespace p3d {

	////////////////////////////////////////////////////////
	/// An Exception class that is thrown when
	/// an error occured during GLEW initialization
	///
	///	version 1.0
	////////////////////////////////////////////////////////
	class GLEWInitError : public std::runtime_error
	{
	public:
		GLEWInitError() : runtime_error("Failed to initialize GLEW") {}
	};

	////////////////////////////////////////////////////////
	/// An Exception class that is thrown when
	/// an error occured during Shader compilation.
	///
	///	version 1.0
	////////////////////////////////////////////////////////
	class ShaderCompileError : public std::runtime_error
	{
	public:
		ShaderCompileError(const char * msg) : runtime_error(msg) {}
	};


	////////////////////////////////////////////////////////
	/// An Exception class that is thrown when
	/// an error occured during loading 3D model.
	///
	///	version 1.0
	////////////////////////////////////////////////////////
	class LoadModelError : public std::runtime_error
	{
	public:
		LoadModelError(const char * msg) : runtime_error(msg) {}
	};


}
#endif //_GL_EXCEPTIONS_
