
#include "Model3d.h";

///Creates buffer objects and sends data to this buffers.
///vertices		Mesh vertices
///indices		Mesh indices
///textures		Mesh textures
Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures){
	
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
	
	//create vertex and index buffer objects
	glGenBuffers(1, &VBO);	
	glGenBuffers(1, &IBO);

	//send object's vertices to the buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//send object's indices to the buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

///Binds vertex and index buffer objects and sets vertex attributes pointers.
void Mesh::bindVertexArray() const{

	//Bind vertex & indices buffers
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	//set vertex position pointer
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	//set vertex normal pointer
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));

	//set vertex texture coordinates pointer
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, textureCoords));
}

///Unbinds vertex and index buffer objects
void Mesh::unbindVertexArray() const{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

///Draws the mesh
///shader	Shader used to draw the mesh
void Mesh::draw(const Shader & shader) const{
	
	GLuint diffuseNr = 1, specularNr = 1;

	//Set textures in shader program
	for (GLuint i = 0; i < textures.size(); i++){

		std::stringstream ss;
		std::string number;
		std::string type = textures[i].type;
		glActiveTexture(GL_TEXTURE0 + i);	//activate texture unit
		if (type == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		else if (type == "texture_specular")
			number = std::to_string(specularNr++);
		//set specified sampler to active texture unit
		glUniform1f(glGetUniformLocation(shader.getProgram(), ("material." + type + number).c_str()), i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);	//bind texture to the active texture unit
	}
	glActiveTexture(GL_TEXTURE0);

	//draw mesh
	bindVertexArray();
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	unbindVertexArray();
		
}


///Draws the model.
///shader	Shader used to draw the mesh
void Model3D::draw(const Shader & shader) const{
	for (GLuint i = 0; i < meshes.size(); i++)
		meshes[i]->draw(shader);
}

void Model3D::loadModel(std::string path){
	
	//import scene object from file
	Assimp::Importer importer;
	const aiScene * scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	//Check if any error occured
	if ((!scene) || (scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE) || (!scene->mRootNode)){
		//
		// ERROR, importer.GetErrorString()
		//
	}

	//get path of the directory containing model file
	this->directory = path.substr(0, path.find_last_of('/'));

	this->processNode(scene->mRootNode, scene);
}

void Model3D::processNode(aiNode * node, const aiScene * scene){
	
	for (GLuint i = 0; i < node->mNumMeshes; i++){
		aiMesh * mesh = scene->mMeshes[node->mMeshes[i]];
		this->meshes.push_back(this->processMesh(mesh, scene));
	}

	for (GLuint i = 0; i < node->mNumChildren; i++){
		processNode(node->mChildren[i], scene);
	}

}

Mesh * Model3D::processMesh(aiMesh * mesh, const aiScene * scene)
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;
	Mesh * modelMesh;

	for (GLuint i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;

		//retrieve vertex data from mesh
		//position
		vertex.position.x = mesh->mVertices[i].x;
		vertex.position.y = mesh->mVertices[i].y;
		vertex.position.z = mesh->mVertices[i].z;
		//normal
		vertex.normal.x = mesh->mNormals[i].x;
		vertex.normal.y = mesh->mNormals[i].y;
		vertex.normal.z = mesh->mNormals[i].z;
		//textureCoords
		if (mesh->mTextureCoords[0]){
			vertex.textureCoords.x = mesh->mTextureCoords[0][i].x;
			vertex.textureCoords.y = mesh->mTextureCoords[0][i].y;
		}
		else
			vertex.textureCoords = glm::vec2(0.0f, 0.0f);
		
		vertices.push_back(vertex);
	}

	//process indices
	for (GLuint i = 0; i < mesh->mNumFaces; i++){
		aiFace face = mesh->mFaces[i];
		for (GLuint j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	//process material
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial * material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<Texture> diffuseMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		std::vector<Texture> specularMaps = this->loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}
	
	//return new Mesh
	modelMesh = new Mesh(vertices, indices, textures);
	return modelMesh;
}

std::vector<Texture> Model3D::loadMaterialTextures(aiMaterial * mat, aiTextureType type, std::string typeName){

	std::vector<Texture> textures;

	for (GLuint i = 0; i < mat->GetTextureCount(type); i++){

		aiString str;
		mat->GetTexture(type, i, &str);
		GLboolean skip = false;
		for (GLuint j = 0; j < textures_loaded.size(); j++){
			if (textures_loaded[j].path == str){
				textures.push_back(textures_loaded[j]);
				skip = true;
				break;
			}
		}
		if (!skip){
			Texture texture;
			texture.id = TextureFromFile(str.C_Str(), this->directory);
			texture.type = typeName;
			texture.path = str;
			textures.push_back(texture);
			textures_loaded.push_back(texture);
		}
		
	}
	return textures;

}