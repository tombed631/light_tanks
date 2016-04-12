
#ifndef _MODEL_LOADER_H_
#define _MODEL_LOADER_H_

#include "Model3d.h"
#include "GLExceptions.h"

#include <string>
#include <vector>

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include <SOIL\SOIL.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

////////////////////////////////////////////////////////
/// Provides an interface to load 3D models from
///	file.
///
///	version 1.0
////////////////////////////////////////////////////////
class ModelLoader{
public:

	///Loads model from specified file.
	///Note that model texture file paths have to be relative to the model object path.
	///path		Path to the file to read from
	///Throws	LoadModelError if failed.
	static Model3D loadFromFile(const std::string path);

private:

	///Retrieves all meshes from this node and repeats this process on its children
	///if any exists.
	///node		Node to be processed
	///scene	Scene that is owner of the specified node
	///texL		Vector containing loaded textures
	///dir		Path to the model directory.
	static void processNode(aiNode * node, const aiScene * scene, std::vector<Mesh> & meshes, std::vector<Texture> & texL, const std::string & dir);

	///Converts ASSIMP mesh to the Model3D acceptable mesh object
	///mesh		Assimp mesh to be transformed
	///scene	Scene imported from file, that is being processed
	///texL		Vector containing loaded textures
	///dir		Path to the model directory.
	static Mesh processMesh(aiMesh * mesh, const aiScene * scene, std::vector<Texture> & texL, const std::string & dir);

	///Checks all material textures of a specified type and loads them if they are not loaded yet.
	///mat		Material, which textures are loaded
	///type		Type of the texture (diffuse, specular etc.)
	///typeName	Name of the texture type
	///texL		Vector containing loaded textures
	///dir		Path to the model directory.
	static std::vector<Texture> loadMaterialTextures(aiMaterial * mat, aiTextureType type, std::string typeName, std::vector<Texture> & texL, const std::string & dir);

	///Reads Texture from file.
	///path			Path to the source file (relative to the directory)
	///directory	Path to the directory containing model source file
	static GLint readTextureFromFile(const char * path, const std::string directory);
};



#endif //_MODEL_LOADER_H_