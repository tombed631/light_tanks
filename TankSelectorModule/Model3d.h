
#ifndef _MODEL_3D_H_
#define _MODEL_3D_H_

#include <glm\glm.hpp>
#include <GL\glew.h>
#include <string>
#include <vector>
#include "Shader.h"

////////////////////////////////////////////////////////
/// Represents a single vertex. 
///
///	version 1.0
////////////////////////////////////////////////////////
struct Vertex{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textureCoords;
};

////////////////////////////////////////////////////////
/// Represents a single texture. 
///
///	version 1.0
////////////////////////////////////////////////////////
struct Texture{
	GLuint id;
	std::string type;
};

////////////////////////////////////////////////////////
/// Represents a single drawable object.  
///
///	version 1.0
////////////////////////////////////////////////////////
class Mesh{
public:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);

	void draw(Shader & shader) const;

private:

	GLuint VBO, EBO;

};



#endif //_MODEL_3D_H_