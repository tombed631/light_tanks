/*
* File:   collision.h
* Authors: Nick Koirala (original version), ahnonay (SFML2 compatibility)
*
* Collision Detection and handling class
* For SFML2.

Notice from the original version:

(c) 2009 - LittleMonkey Ltd

This software is provided 'as-is', without any express or
implied warranty. In no event will the authors be held
liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute
it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented;
you must not claim that you wrote the original software.
If you use this software in a product, an acknowledgment
in the product documentation would be appreciated but
is not required.

2. Altered source versions must be plainly marked as such,
and must not be misrepresented as being the original software.

3. This notice may not be removed or altered from any
source distribution.

*
* Created on 30 January 2009, 11:02
*/

#ifndef COLLISION_H
#define COLLISION_H

#include "Includes.h"
namespace Collision {

	bool PlayerWallCollision(const sf::Sprite& Object1, const sf::RectangleShape& Object2);

	bool intersects(float cx, float cy, float radius, float left, float top, float right, float bottom);
	bool collideCircleRect(const sf::CircleShape & circle, const sf::RectangleShape & rect);
	bool collide(const sf::Vector2f & circlePositon, float radius, const sf::FloatRect & rectangle);
}

#endif  