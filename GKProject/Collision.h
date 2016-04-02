
#ifndef COLLISION_H
#define COLLISION_H

#endif  
#include "Includes.h"
namespace Collision {

	bool PlayerWallCollision(const Sprite& Object1, const RectangleShape& Object2);
	bool PlayerPlayerCollision(const Sprite& object1, const Sprite& object2);
}