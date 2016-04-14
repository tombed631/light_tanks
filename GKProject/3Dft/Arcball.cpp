
#include "Arcball.h"
using namespace p3d;
namespace p3d {

	///Calculates new model matrix based on current one. The new model matrix
	///includes rotation caused by mouse movement (result of using ArcBall).
	///modelMatrix		Model matrix used to transform target object (object to rotate by mouse)
	glm::mat4 ArcBall::getUpdatedModelMatrix(const glm::mat4 & modelMatrix) {
		//if mouse moved
		if (currentX != lastX || currentY != lastY) {
			glm::vec3 va = getArcballVector(lastX, lastY);	//get previous mouse vector mapped to arcball surface
			glm::vec3 vb = getArcballVector(currentX, currentY);	//current
			float angle = acos(glm::min(1.0f, glm::dot(va, vb)));	//calculate angle btw vectors
			glm::vec3 axisInWorldCoord = glm::cross(va, vb);	//calulate rotation axis
			glm::mat4 camera2object = inverse(modelMatrix);	//get matrix...
			glm::vec4 axisInObjectCoord = camera2object * glm::vec4(axisInWorldCoord, 1.0);	//...to transform axis to object local coords
			//calculate new model matrix including arcball rotation
			glm::mat4 newModelMatrix = glm::rotate(modelMatrix, angle, glm::vec3(axisInObjectCoord.x, axisInObjectCoord.y, axisInObjectCoord.z));

			//update mouse position
			lastX = currentX;
			lastY = currentY;
			return newModelMatrix;	//return updated model matrix
		}
		else
			return modelMatrix;	//nothing changed
	}

	///Returns a normalized vector from the center of the arcball
	///to a point on the ball surface. If the point is too far away from the sphere
	///returns the nearest point on the ball surface.
	glm::vec3 ArcBall::getArcballVector(float x, float y) {
		glm::vec3 point = glm::vec3(x / winWidth * 2 - 1.0, y / winHeight * 2 - 1.0, 0.0); //normalize point
		point.y = -point.y;	//reverse y (SFML:OY: up<down, openGL:OY up>down)

		//calculate z
		float opLengthSqared = point.x * point.x + point.y * point.y;
		if (opLengthSqared <= 1.0)
			point.z = sqrt(1.0 - opLengthSqared);
		else
			point = glm::normalize(point);

		return point;
	}
}