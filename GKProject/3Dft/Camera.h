
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <GL\glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace p3d {

	////////////////////////////////////////////////////////
	/// Represents a camera.
	///
	///	version 1.1
	////////////////////////////////////////////////////////
	class Camera {
	public:


		///Creates camera object.
		///position		Camera position in world space.
		///front		Camera target direction.
		Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 front = glm::vec3(0.0f, 0.0f, 0.0f)) :
			position(position), front(front), up(glm::vec3(0.0f, 1.0f, 0.0f)) {
		}

		///Returns camera position in world space.
		glm::vec3 getPosition() const {
			return this->position;
		}

		///Sets camera position in world space.
		void setPosition(const glm::vec3 pos) {
			this->position = pos;
		}

		///Returns camera front vector.
		glm::vec3 getFront() const {
			return this->front;
		}

		///Sets camera front vector.
		void setFront(const glm::vec3 front) {
			this->front = front;
		}

		///Returns view matrix, that is ready to use
		///to transform coordinates from world space to the view space.
		glm::mat4 getViewMatrix() const {
			return glm::lookAt(this->position, this->front, this->up);
		}

	private:

		///Camera position
		glm::vec3 position;

		///Camera up vector
		glm::vec3 up;

		///Camera target direction
		glm::vec3 front;
	};


}

#endif // _CAMERA_H_
