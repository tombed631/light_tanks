
#ifndef _ARCBALL_H_
#define _ARCBALL_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace p3d {
	////////////////////////////////////////////////////////
	/// A tool used to rotate objects with mouse.
	///
	///	version 1.1
	////////////////////////////////////////////////////////
	class ArcBall {
	public:

		///Creates ArcBall instance with given window parameters.
		///winWidth		Target window width
		///winHeight	Target window height
		ArcBall(float winWidth = 0.0, float winHeight = 0.0) {
			lastX = lastY = currentX = currentY = 0.0;
			this->winWidth = winWidth;
			this->winHeight = winHeight;
			arcballOn = false;
		}


		///Sets target window size.
		///winWidth		Target window width
		///winHeight	Target window height
		void setWindowSize(float winWidth, float winHeight) {
			this->winWidth = winWidth;
			this->winHeight = winHeight;
		}

		///Enables arcball.
		///curX		Current mouse x position.
		///curY		Current mouse y position.
		void enable(float curX, float curY) {
			arcballOn = true;
			lastX = currentX = curX;
			lastY = currentY = curY;
		}

		///Disables arcball.
		void disable() {
			arcballOn = false;
			lastX = lastY = currentX = currentY = 0.0;
		}

		///Returns true if arcball is enabled.
		bool isEnabled() const { return arcballOn; }

		///Sets current mouse position.
		///curX		Current mouse x position.
		///curY		Current mouse y position.
		void drag(float curX, float curY) {
			if (arcballOn) {
				currentX = curX;
				currentY = curY;
			}
		}

		///Calculates new model matrix based on current one. The new model matrix
		///includes rotation caused by mouse movement (result of using ArcBall).
		///modelMatrix		Model matrix used to transform target object (object to rotate by mouse)
		glm::mat4 getUpdatedModelMatrix(const glm::mat4 & modelMatrix);


	private:

		///Target window size parameters.
		float winWidth, winHeight;

		///Mouse position on the screen.
		float lastX, lastY, currentX, currentY;

		///Determines whether arcball is turned on or not.
		bool arcballOn;

		///Returns a normalized vector from the center of the arcball
		///to a point on the ball surface. If the point is too far away from the sphere
		///returns the nearest point on the ball surface.
		glm::vec3 getArcballVector(float x, float y);

	};

}


#endif // !_ARCBALL_H_
