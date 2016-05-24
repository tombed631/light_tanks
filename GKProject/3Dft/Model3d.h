
#ifndef _MODEL_3D_H_
#define _MODEL_3D_H_

#include "Drawable.h"

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

namespace p3d {

	////////////////////////////////////////////////////////
	/// Represents a single vertex. 
	///
	///	version 1.0
	////////////////////////////////////////////////////////
	struct Vertex {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 textureCoords;
	};

	////////////////////////////////////////////////////////
	/// Represents a single texture. 
	///
	///	version 1.1
	////////////////////////////////////////////////////////
	struct Texture {
		GLuint id;
		std::string type;	//diffuse/specular
		aiString path;	//path of the texture (relative to the model directory)
	};

	////////////////////////////////////////////////////////
	/// Represents a single material. 
	///
	///	version 1.0
	////////////////////////////////////////////////////////
	struct Material {
		glm::vec3 color_diffuse;
		glm::vec3 color_specular;
		glm::vec3 color_ambient;
		float shininess;
	};

	////////////////////////////////////////////////////////
	/// Represents a single drawable object.  
	///
	///	version 1.2
	////////////////////////////////////////////////////////
	class Mesh : public Drawable {
	public:

		///Creates buffer objects and sends data to this buffers.
		///vertices		Mesh vertices
		///indices		Mesh indices
		///textures		Mesh textures
		Mesh(std::vector<Vertex> & vertices, std::vector<GLuint> & indices, std::vector<Texture> & textures, Material & material);

		///Creates new mesh that is a copy of the other specified mesh.
		Mesh(const Mesh &);

		///Deletes current mesh resources and assigns a new one that is a copy
		///of specified mesh.
		Mesh & operator=(const Mesh &);

		///Move constructor.
		Mesh(Mesh &&);

		///Move assign operator.
		Mesh & operator=(Mesh &&);

		///Delete mesh buffer objects.
		~Mesh() {
			glDeleteBuffers(1, &VBO);
			glDeleteBuffers(1, &IBO);
		}

		///Draws the mesh.
		///shader	Shader used to draw the mesh
		void draw(const Shader & shader) const override;

	private:

		///Vertex and Index Buffer Objects
		GLuint VBO, IBO;

		///Contains object's vertices
		std::vector<Vertex> vertices;

		///Contains object's indices
		std::vector<GLuint> indices;

		///Contains object's textures
		std::vector<Texture> textures;

		///Contains properties of the object material.
		Material material;

	};


	////////////////////////////////////////////////////////
	/// Represents a drawable 3D model.  
	///
	///	version 1.2
	////////////////////////////////////////////////////////
	class Model3D : public Drawable {
	public:

		///Creates 3D model that has no meshes (empty model).
		///You can call draw function on this model, however
		///in the result nothing will be rendered.
		Model3D() = default;

		///Creates 3D model from specified meshes.
		///meshes	Meshes that creates 3D model.
		explicit Model3D(std::vector<Mesh> meshes) {
			this->meshes = std::move(meshes);
		}

		virtual ~Model3D() = default;

		///Creates a new model that is a copy of other specified model.
		Model3D(const Model3D & other) {
			this->meshes = other.meshes;
		}

		///Move constructor.
		Model3D(Model3D && other) {
			this->meshes = std::move(other.meshes);
		}

		///Assigns copy of specified model to this model.
		Model3D & operator=(const Model3D & other) {
			if (this != &other)
				this->meshes = other.meshes;
			return *this;
		}

		///Move assignment operator.
		Model3D & operator=(Model3D && other) {
			if (this != &other)
				this->meshes = std::move(other.meshes);
			return *this;
		}

		///Draws the object on the screen.
		///shader	Shader used to draw.
		void draw(const Shader & shader) const override {
			for (unsigned int i = 0; i < this->meshes.size(); i++)
				meshes[i].draw(shader);
		}


	private:

		///Meshes that are parts of the model.
		std::vector<Mesh> meshes;

	};

}

#endif //_MODEL_3D_H_