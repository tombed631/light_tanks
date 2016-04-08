
#ifndef _MODEL_3D_H_
#define _MODEL_3D_H_

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <GL\glew.h>

#include <string>
#include <vector>

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include <SOIL\SOIL.h>

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
///	version 1.1
////////////////////////////////////////////////////////
struct Texture{
	GLuint id;
	std::string type;	//diffuse/specular
	aiString path;	//path of the texture (relative to the model directory)
};

////////////////////////////////////////////////////////
/// Represents a single drawable object.  
///
///	version 1.1
////////////////////////////////////////////////////////
class Mesh final{
public:

	///Creates buffer objects and sends data to this buffers.
	///vertices		Mesh vertices
	///indices		Mesh indices
	///textures		Mesh textures
	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);

	///Delete mesh buffer objects.
	~Mesh(){
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &IBO);
	}

	///Draws the mesh.
	///shader	Shader used to draw the mesh
	void draw(const Shader & shader) const;

private:

	///Vertex and Index Buffer Objects
	GLuint VBO, IBO;

	///Contains object's vertices
	std::vector<Vertex> vertices;

	///Contains object's indices
	std::vector<GLuint> indices;

	///Contains object's textures
	std::vector<Texture> textures;

	///Binds vertex and index buffer objects and sets vertex attributes pointers.
	void bindVertexArray() const;

	///Unbinds vertex and index buffer objects and disables vertex attribute array.
	void unbindVertexArray() const;

	//Mesh non-copyable and non-movable
	Mesh(const Mesh &) = delete;
	Mesh(Mesh &&) = delete;
	Mesh & operator=(const Mesh &) = delete;
	Mesh & operator=(Mesh &&) = delete;

};


////////////////////////////////////////////////////////
/// Represents a drawable 3D model.  
///
///	version 1.0
////////////////////////////////////////////////////////
class Model3D{
public:

	///Loads 3D model from specified file;
	///path		Path to the file containing model.
	///Throws LoadModelError if failed.
	explicit Model3D(const GLchar * path){
		loadModel(path);
	}

	///Frees memory used by this model.
	virtual ~Model3D(){
		for (GLuint i = 0; i < meshes.size(); i++)
			delete meshes[i];
	}

	///Draws the model.
	///shader	Shader used to draw the mesh
	void draw(const Shader & shader) const;

private:

	///Contains model meshes.
	std::vector<Mesh*> meshes;
	std::vector<Texture> textures_loaded;

	///Path to the model object file directory
	std::string directory;

	///Loads model from specified file.
	///Note that model texture file paths have to be relative to the model object path.
	///path		Path to the file to read from
	///Throws LoadModelError if failed.
	void loadModel(const std::string path);

	///Retrieves all meshes from this node and repeats this process on its children
	///if any exists.
	///node		Node to be processed
	///scene	Scene that is owner of the specified node
	void processNode(aiNode * node, const aiScene * scene);

	///Converts ASSIMP mesh to the Model3D acceptable mesh object
	///mesh		Assimp mesh to be transformed
	///scene	Scene imported from file, that is being processed
	Mesh * processMesh(aiMesh * mesh, const aiScene * scene);

	///Checks all material textures of a specified type and loads them if they are not loaded yet.
	///mat		Material, which textures are loaded
	///type		Type of the texture (diffuse, specular etc.)
	///typeName	Name of the texture type
	std::vector<Texture> loadMaterialTextures(aiMaterial * mat, aiTextureType type, std::string typeName);

};


#endif //_MODEL_3D_H_