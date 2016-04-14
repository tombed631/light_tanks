

#include "Model3d.h";
#include <iostream>

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

///Creates new mesh that is a copy of the other specified mesh.
Mesh::Mesh(const Mesh & mesh) {
	this->vertices = mesh.vertices;
	this->indices = mesh.indices;
	this->textures = mesh.textures;

	//create vertex and index buffer objects
	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->IBO);

	//send object's vertices to the buffer
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//send object's indices to the buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

///Deletes current mesh resources and assigns a new one that is a copy
///of specified mesh.
Mesh & Mesh::operator=(const Mesh & mesh) {

	if (this != &mesh) {
		glDeleteBuffers(1, &this->VBO);
		glDeleteBuffers(1, &this->IBO);

		this->vertices = mesh.vertices;
		this->indices = mesh.indices;
		this->textures = mesh.textures;

		//create vertex and index buffer objects
		glGenBuffers(1, &this->VBO);
		glGenBuffers(1, &this->IBO);

		//send object's vertices to the buffer
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		//send object's indices to the buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	return *this;
}

///Move constructor.
Mesh::Mesh(Mesh && mesh) {

	//Steal mesh resources
	this->vertices = std::move(mesh.vertices);
	this->indices = std::move(mesh.indices);
	this->textures = std::move(mesh.textures);

	this->VBO = mesh.VBO;
	this->IBO = mesh.IBO;

	mesh.VBO = 0;
	mesh.IBO = 0;
}

///Move assign operator.
Mesh & Mesh::operator=(Mesh && mesh) {
	
	if (this != &mesh) {
		
		//Delete currently used buffers.
		glDeleteBuffers(1, &this->VBO);
		glDeleteBuffers(1, &this->IBO);

		//Steal mesh resources
		this->vertices = std::move(mesh.vertices);
		this->indices = std::move(mesh.indices);
		this->textures = std::move(mesh.textures);

		this->VBO = mesh.VBO;
		this->IBO = mesh.IBO;

		mesh.VBO = 0;
		mesh.IBO = 0;

	}
	return *this;
}


///Draws the mesh
///shader	Shader used to draw the mesh
void Mesh::draw(const Shader & shader) const{
	
	GLuint diffuseNr = 1, specularNr = 1;

	////Set textures in shader program
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
		glUniform1i(glGetUniformLocation(shader.getProgram(), (type + number).c_str()), i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);	//bind texture to the active texture unit
	}

	//Bind vertex & indices buffers
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	//Get attributes locations
	GLuint texLoc, normLoc, posLoc;
	texLoc = glGetAttribLocation(shader.getProgram(), "in_TexCoord");
	normLoc = glGetAttribLocation(shader.getProgram(), "in_normal");
	posLoc = glGetAttribLocation(shader.getProgram(), "in_position");

	//set vertex position pointer
	glEnableVertexAttribArray(posLoc);
	glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	//set vertex normal pointer
	glEnableVertexAttribArray(normLoc);
	glVertexAttribPointer(normLoc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));

	//set vertex texture coordinates pointer
	glEnableVertexAttribArray(texLoc);
	glVertexAttribPointer(texLoc, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, textureCoords));


	//draw mesh
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

	//unbind buffers and disable attributes
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(posLoc);
	glDisableVertexAttribArray(normLoc);
	glDisableVertexAttribArray(texLoc);

	for (GLuint i = 0; i < this->textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
		
}

/////////////////////////////////////////////////////////////////////////////////


/////Draws the model.
/////shader	Shader used to draw the mesh
//void Model3D::draw(const Shader & shader) const{
//	for (GLuint i = 0; i < meshes.size(); i++)
//		meshes[i]->draw(shader);
//}
//
/////Loads model from specified file.
/////Note that model texture file paths have to be relative to the model object path.
/////path		Path to the file to read from
/////Throws LoadModelError if failed.
//void Model3D::loadModel(std::string path){
//	
//	//import scene object from file
//	Assimp::Importer importer;
//	const aiScene * scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
//
//	//Check if any error occured
//	if ((!scene) || (scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE) || (!scene->mRootNode)){
//		throw LoadModelError(importer.GetErrorString());
//	}
//
//	//get path of the directory containing model file
//	this->directory = path.substr(0, path.find_last_of('/'));
//
//	//Process scene nodes, start from root node
//	this->processNode(scene->mRootNode, scene);
//}
//
/////Retrieves all meshes from this node and repeats this process on its children
/////if any exists.
/////node		Node to be processed
/////scene	Scene that is owner of the specified node
//void Model3D::processNode(aiNode * node, const aiScene * scene){
//	
//	//Store all meshes from this node in vector
//	for (GLuint i = 0; i < node->mNumMeshes; i++){
//		aiMesh * mesh = scene->mMeshes[node->mMeshes[i]];
//		this->meshes.push_back(this->processMesh(mesh, scene));
//	}
//
//	//Do the same for this node's children
//	for (GLuint i = 0; i < node->mNumChildren; i++){
//		processNode(node->mChildren[i], scene);
//	}
//
//}
//
/////Converts ASSIMP mesh to the Model3D acceptable mesh object
/////mesh		Assimp mesh to be transformed
/////scene	Scene imported from file, that is being processed
//Mesh * Model3D::processMesh(aiMesh * mesh, const aiScene * scene)
//{
//	std::vector<Vertex> vertices;
//	std::vector<GLuint> indices;
//	std::vector<Texture> textures;
//	Mesh * modelMesh;	//mesh to return
//
//	//Get all vertices data
//	for (GLuint i = 0; i < mesh->mNumVertices; i++)
//	{
//		Vertex vertex;
//
//		//retrieve vertex data from mesh
//		//position
//		vertex.position.x = mesh->mVertices[i].x;
//		vertex.position.y = mesh->mVertices[i].y;
//		vertex.position.z = mesh->mVertices[i].z;
//		//normal
//		if (mesh->HasNormals()) {
//			vertex.normal.x = mesh->mNormals[i].x;
//			vertex.normal.y = mesh->mNormals[i].y;
//			vertex.normal.z = mesh->mNormals[i].z;
//		}
//		else
//			vertex.normal = glm::vec3(0.0f, 0.0f, 0.0f);
//
//		//textureCoords
//		if (mesh->HasTextureCoords(0)){
//			vertex.textureCoords.x = mesh->mTextureCoords[0][i].x;
//			vertex.textureCoords.y = mesh->mTextureCoords[0][i].y;
//		}
//		else
//			vertex.textureCoords = glm::vec2(0.0f, 0.0f);
//		
//		vertices.push_back(vertex);
//	}
//
//	//Get indices data
//	//for each face (primitive)...
//	for (GLuint i = 0; i < mesh->mNumFaces; i++){
//		aiFace face = mesh->mFaces[i];
//		//...get its indices and store in vector
//		for (GLuint j = 0; j < face.mNumIndices; j++)
//			indices.push_back(face.mIndices[j]);
//	}
//
//	//process materials
//	if (mesh->mMaterialIndex >= 0)
//	{
//		aiMaterial * material = scene->mMaterials[mesh->mMaterialIndex];
//
//		//get diffuse maps
//		std::vector<Texture> diffuseMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
//		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
//		//get specular maps
//		std::vector<Texture> specularMaps = this->loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
//		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
//	}
//	
//	//return new Mesh
//	modelMesh = new Mesh(vertices, indices, textures);
//	return modelMesh;
//}
//
//
/////Reads Texture from file.
/////path			Path to the source file (relative to the directory)
/////directory	Path to the directory containing model source file
//GLint readTextureFromFile(const char * path, std::string directory)
//{
//	std::string filename = std::string(path);
//	filename = directory + '/' + filename;
//	GLuint textureID;
//	int width, height;
//	//read image from file
//	unsigned char * image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
//	glGenTextures(1, &textureID);	//create texture object
//	glBindTexture(GL_TEXTURE_2D, textureID);
//	//Create texture from image
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
//	glGenerateMipmap(GL_TEXTURE_2D); //generate mipmap for texture
//
//	//set texture parameters
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glBindTexture(GL_TEXTURE_2D, 0);
//	SOIL_free_image_data(image); //free image
//	return textureID;
//
//}
//
//
/////Checks all material textures of a specified type and loads them if they are not loaded yet.
/////mat		Material, which textures are loaded
/////type		Type of the texture (diffuse, specular etc.)
/////typeName	Name of the texture type
//std::vector<Texture> Model3D::loadMaterialTextures(aiMaterial * mat, aiTextureType type, std::string typeName){
//
//	std::vector<Texture> textures;
//
//	for (GLuint i = 0; i < mat->GetTextureCount(type); i++){
//
//		aiString str;	//texture file location, relative to the model object location
//		mat->GetTexture(type, i, &str);	//get Texture info
//		GLboolean skip = false;
//		//check if texture is already loaded
//		for (GLuint j = 0; j < textures_loaded.size(); j++){
//			if (textures_loaded[j].path == str){
//				textures.push_back(textures_loaded[j]);
//				skip = true;
//				break;
//			}
//		}
//		//load if not loaded
//		if (!skip){
//			Texture texture;
//			texture.id = readTextureFromFile(str.C_Str(), this->directory);
//			texture.type = typeName;
//			texture.path = str;
//			textures.push_back(texture);
//			textures_loaded.push_back(texture);
//		}
//		
//	}
//	return textures;
//
//}
//
