#ifndef _LIGHT_CUBE_H_
#define _LIGHT_CUBE_H_

#include <GL\glew.h>
#include "Shader.h"
#include "Drawable.h"
#include <vector>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

namespace p3d {

	////////////////////////////////////////////////////////
	///	Represents a light.Includes intensity of different
	/// light types and position in world space.
	///
	///	version 1.0
	////////////////////////////////////////////////////////
	struct Light {
		glm::vec3 ambientIntensity;
		glm::vec3 diffuseIntensity;
		glm::vec3 specularIntensity;
		glm::vec3 position;
	};


	///Cube vertices positions
	extern const std::vector<GLfloat> lightCubeVertices;



	////////////////////////////////////////////////////////
	///	A cube that is a graphical representation of a light.
	///
	///	version 1.1
	////////////////////////////////////////////////////////
	class LightCube : public Drawable {

	public:

		///Creates LightCube.
		LightCube() {
			//Create vertex buffer object and send data to the GPU memory
			glGenBuffers(1, &VBO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, lightCubeVertices.size() * sizeof(GLfloat), &lightCubeVertices[0], GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		///Creates LightCube.
		///light	Light object containing light properties.
		explicit LightCube(Light light) {
			this->light = light;

			//Create vertex buffer object and send data to the GPU memory
			glGenBuffers(1, &VBO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, lightCubeVertices.size() * sizeof(GLfloat), &lightCubeVertices[0], GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		///Creates LightCube that is a copy of other specified LightCube object.
		LightCube(const LightCube & other) {
			this->light = other.light;

			//Create vertex buffer object and send data to the GPU memory
			glGenBuffers(1, &this->VBO);
			glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
			glBufferData(GL_ARRAY_BUFFER, lightCubeVertices.size() * sizeof(GLfloat), &lightCubeVertices[0], GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		///Move constructor.
		LightCube(LightCube && other) {
			this->light = other.light;
			this->VBO = other.VBO;
			other.VBO = 0;
		}

		///Releases all current resources and assigns a copy of specified light cube.
		LightCube & operator=(const LightCube & other) {
			if (this != &other) {
				glDeleteBuffers(1, &this->VBO);

				this->light = other.light;
				glGenBuffers(1, &this->VBO);
				glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
				glBufferData(GL_ARRAY_BUFFER, lightCubeVertices.size() * sizeof(GLfloat), &lightCubeVertices[0], GL_STATIC_DRAW);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}
			return *this;
		}

		///Move assignment operator.
		LightCube & operator=(LightCube && other) {
			if (this != &other) {
				glDeleteBuffers(1, &this->VBO);

				this->light = other.light;
				this->VBO = other.VBO;
				other.VBO = 0;
			}
			return *this;
		}

		///Deletes vertex buffer object.
		~LightCube() {
			glDeleteBuffers(1, &VBO);
		}

		///Sets specified light properties set.
		void setLight(const Light & light) {
			this->light = light;
		}

		///Returns light properties set.
		Light getLight() const { return this->light; }

		///Draws the light cube.
		///shader	Shader used to draw the mesh 
		void draw(const Shader & shader) const override {
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			GLuint posLoc = glGetAttribLocation(shader.getProgram(), "in_position");
			glEnableVertexAttribArray(posLoc);
			glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (GLvoid*)0);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glDisableVertexAttribArray(posLoc);
		}

	private:

		///Contains light properties
		Light light;

		///Vertex buffer object.
		GLuint VBO;

	};

}

#endif //_LIGHT_CUBE_H_