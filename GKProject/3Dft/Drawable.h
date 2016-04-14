
#ifndef _DRAWABLE_H_
#define _DRAWABLE_H_

#include "Shader.h"

namespace p3d{

	////////////////////////////////////////////////////////
	///	Abstract class that represents something 
	/// that can be drawn on the screen.
	///
	///	version 1.0
	////////////////////////////////////////////////////////
	class Drawable {

	public:

		///Draws the object on the screen.
		///shader	Shader used to draw.
		virtual void draw(const p3d::Shader & shader) const = 0;

		virtual ~Drawable() = default;

	};

}

#endif	//_DRAWABE_H_
