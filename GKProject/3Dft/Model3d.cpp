

#include "Model3d.h";
#include <iostream>

namespace p3d {

	///Creates buffer objects and sends data to this buffers.
	///vertices		Mesh vertices
	///indices		Mesh indices
	///textures		Mesh textures
	Mesh::Mesh(std::vector<Vertex> & vertices, std::vector<GLuint> & indices, std::vector<Texture> & textures, Material & material) {

		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;
		this->material = material;

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
		this->material = mesh.material;

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
			this->material = mesh.material;

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
		this->material = mesh.material;

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
			this->material = mesh.material;

			this->VBO = mesh.VBO;
			this->IBO = mesh.IBO;

			mesh.VBO = 0;
			mesh.IBO = 0;

		}
		return *this;
	}


	///Draws the mesh
	///shader	Shader used to draw the mesh
	void Mesh::draw(const Shader & shader) const {

		GLuint diffuseNr = 1, specularNr = 1;
		GLuint program = shader.getProgram();

		//Set textures if mesh has any
		if (textures.size() > 0) {
			
			glUniform1i(glGetUniformLocation(program, "isTextured"), 1);
			
			//Set textures in shader program
			for (GLuint i = 0; i < textures.size(); i++) {

				std::stringstream ss;
				std::string number;
				std::string type = textures[i].type;
				glActiveTexture(GL_TEXTURE0 + i);	//activate texture unit
				if (type == "texture_diffuse")
					number = std::to_string(diffuseNr++);
				else if (type == "texture_specular")
					number = std::to_string(specularNr++);
				//set specified sampler to active texture unit
				glUniform1i(glGetUniformLocation(program, (type + number).c_str()), i);
				glBindTexture(GL_TEXTURE_2D, textures[i].id);	//bind texture to the active texture unit
			}
		}else
			glUniform1i(glGetUniformLocation(program, "isTextured"), 0);

		//Set material
		glUniform3f(glGetUniformLocation(program, "material.color_ambient"), material.color_ambient.r, material.color_ambient.g, material.color_ambient.b);
		glUniform3f(glGetUniformLocation(program, "material.color_diffuse"), material.color_diffuse.r, material.color_diffuse.g, material.color_diffuse.b);
		glUniform3f(glGetUniformLocation(program, "material.color_specular"), material.color_specular.r, material.color_specular.g, material.color_specular.b);
		glUniform1f(glGetUniformLocation(program, "material.shininess"), material.shininess);

		//Bind vertex & indices buffers
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

		//Get attributes locations
		GLuint texLoc, normLoc, posLoc;
		texLoc = glGetAttribLocation(program, "in_TexCoord");
		normLoc = glGetAttribLocation(program, "in_normal");
		posLoc = glGetAttribLocation(program, "in_position");

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

}

