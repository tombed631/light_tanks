#include "ModelLoader.h"

namespace p3d {

	Model3D ModelLoader::loadFromFile(const std::string path)
	{
		std::vector<Mesh> meshes;	//contains loaded meshes;
		std::vector<Texture> textures_loaded;	//contains textures, that has been already loaded.
		std::string modelDirectory;	//path to the model directory.

		//import scene object from file
		Assimp::Importer importer;
		const aiScene * scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

		//Check if any error occured
		if ((!scene) || (scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE) || (!scene->mRootNode)) {
			throw LoadModelError(importer.GetErrorString());
		}

		//get path of the directory containing model file
		modelDirectory = path.substr(0, path.find_last_of('/'));

		//Process scene nodes, start from root node
		processNode(scene->mRootNode, scene, meshes, textures_loaded, modelDirectory);

		return Model3D(std::move(meshes));
	}

	///Retrieves all meshes from this node and repeats this process on its children
	///if any exists.
	///node		Node to be processed
	///scene	Scene that is owner of the specified node
	///texL		Vector containing loaded textures
	///dir		Path to the model directory.
	void ModelLoader::processNode(aiNode * node, const aiScene * scene, std::vector<Mesh>& meshes, std::vector<Texture> & texL, const std::string & dir)
	{
		//Store all meshes from this node in vector
		for (GLuint i = 0; i < node->mNumMeshes; i++) {
			aiMesh * mesh = scene->mMeshes[node->mMeshes[i]];
			meshes.push_back(processMesh(mesh, scene, texL, dir));
		}

		//Do the same for this node's children
		for (GLuint i = 0; i < node->mNumChildren; i++) {
			processNode(node->mChildren[i], scene, meshes, texL, dir);
		}
	}

	///Converts ASSIMP mesh to the Model3D acceptable mesh object
	///mesh		Assimp mesh to be transformed
	///scene	Scene imported from file, that is being processed
	///texL		Vector containing loaded textures
	///dir		Path to the model directory.
	Mesh ModelLoader::processMesh(aiMesh * mesh, const aiScene * scene, std::vector<Texture> & texL, const std::string & dir)
	{
		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;
		std::vector<Texture> textures;
		Material mesh_material;

		//Get all vertices data
		for (GLuint i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;

			//retrieve vertex data from mesh
			//position
			vertex.position.x = mesh->mVertices[i].x;
			vertex.position.y = mesh->mVertices[i].y;
			vertex.position.z = mesh->mVertices[i].z;
			//normal
			if (mesh->HasNormals()) {
				vertex.normal.x = mesh->mNormals[i].x;
				vertex.normal.y = mesh->mNormals[i].y;
				vertex.normal.z = mesh->mNormals[i].z;
			}
			else
				vertex.normal = glm::vec3(0.0f, 0.0f, 0.0f);

			//textureCoords
			if (mesh->HasTextureCoords(0)) {
				vertex.textureCoords.x = mesh->mTextureCoords[0][i].x;
				vertex.textureCoords.y = mesh->mTextureCoords[0][i].y;
			}
			else
				vertex.textureCoords = glm::vec2(0.0f, 0.0f);

			vertices.push_back(vertex);
		}

		//Get indices data
		//for each face (primitive)...
		for (GLuint i = 0; i < mesh->mNumFaces; i++) {
			aiFace face = mesh->mFaces[i];
			//...get its indices and store in vector
			for (GLuint j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}

		//process materials
		if (mesh->mMaterialIndex >= 0)
		{
			aiMaterial * material = scene->mMaterials[mesh->mMaterialIndex];

			//get material properties
			aiColor3D color;
			material->Get(AI_MATKEY_COLOR_AMBIENT, color);
			mesh_material.color_ambient.r = color.r;
			mesh_material.color_ambient.g = color.g;
			mesh_material.color_ambient.b = color.b;
			material->Get(AI_MATKEY_COLOR_DIFFUSE, color);
			mesh_material.color_diffuse.r = color.r;
			mesh_material.color_diffuse.g = color.g;
			mesh_material.color_diffuse.b = color.b;
			material->Get(AI_MATKEY_COLOR_SPECULAR, color);
			mesh_material.color_specular.r = color.r;
			mesh_material.color_specular.g = color.g;
			mesh_material.color_specular.b = color.b;
			material->Get(AI_MATKEY_SHININESS, mesh_material.shininess);

			//get diffuse maps
			std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse", texL, dir);
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
			//get specular maps
			std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular", texL, dir);
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		}

		//return new Mesh
		return Mesh(vertices, indices, textures, mesh_material);
	}

	///Checks all material textures of a specified type and loads them if they are not loaded yet.
	///mat		Material, which textures are loaded
	///type		Type of the texture (diffuse, specular etc.)
	///typeName	Name of the texture type
	///texL		Vector containing loaded textures
	///dir		Path to the model directory.
	std::vector<Texture> ModelLoader::loadMaterialTextures(aiMaterial * mat, aiTextureType type, std::string typeName, std::vector<Texture> & texL, const std::string & dir)
	{
		std::vector<Texture> textures;

		for (GLuint i = 0; i < mat->GetTextureCount(type); i++) {

			aiString str;	//texture file location, relative to the model object location
			mat->GetTexture(type, i, &str);	//get Texture info
			GLboolean skip = false;
			//check if texture is already loaded
			for (GLuint j = 0; j < texL.size(); j++) {
				if (texL[j].path == str) {
					textures.push_back(texL[j]);
					skip = true;
					break;
				}
			}
			//load if not loaded
			if (!skip) {
				Texture texture;
				texture.id = readTextureFromFile(str.C_Str(), dir);
				texture.type = typeName;
				texture.path = str;
				textures.push_back(texture);
				texL.push_back(texture);
			}

		}
		return textures;
	}

	///Reads Texture from file.
	///path			Path to the source file (relative to the directory)
	///directory	Path to the directory containing model source file
	GLint ModelLoader::readTextureFromFile(const char * path, const std::string directory)
	{
		std::string filename = std::string(path);
		filename = directory + '/' + filename;
		GLuint textureID;
		int width, height;
		//read image from file
		unsigned char * image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
		glGenTextures(1, &textureID);	//create texture object
		glBindTexture(GL_TEXTURE_2D, textureID);
		//Create texture from image
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D); //generate mipmap for texture

		//set texture parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
		SOIL_free_image_data(image); //free image
		return textureID;
	}

}