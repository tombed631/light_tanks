
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <GL\glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>



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
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 front = glm::vec3(0.0f, 0.0f, 0.0f)):
		position(position), front(front), up(glm::vec3(0.0f, 1.0f, 0.0f)) {
	}
	

	///Returns view matrix, that is ready to use
	///to transform coordinates from world space to the view space.
	glm::mat4 getViewMatrix() const{
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




#endif // _CAMERA_H_
