
#ifndef COLLISION_H
#define COLLISION_H
 
#include "Includes.h"

class BoundingBox 
	{
	public:
		template <class T>
		BoundingBox(const T& object) 
		{
			Transform trans = object.getTransform();
			IntRect local = object.getTextureRect();
			points[0] = trans.transformPoint(0.f, 0.f);
			points[1] = trans.transformPoint((float)(local.width), 0.f);
			points[2] = trans.transformPoint((float)local.width, (float)local.height);
			points[3] = trans.transformPoint(0.f, (float)local.height);
		}
		sf::Vector2f points[4];
		void transformateToaxis(const sf::Vector2f& axis, float& min, float& max)
		{
			min = (points[0].x*axis.x + points[0].y*axis.y);
			max = min;
			for (int j = 1; j<4; j++)
			{
				float Projection = (points[j].x*axis.x + points[j].y*axis.y);

				if (Projection<min)
					min = Projection;
				if (Projection>max)
					max = Projection;
			}
		}
	};
class Collision{
public:
		template <class T>
		bool isCollision(const Sprite& object1, const T& object2) {
			BoundingBox OBB1(object1);
			BoundingBox OBB2(object2);
			sf::Vector2f axes[4] = {
				Vector2f(OBB1.points[1].x - OBB1.points[0].x,
				OBB1.points[1].y - OBB1.points[0].y),
				Vector2f(OBB1.points[1].x - OBB1.points[2].x,
				OBB1.points[1].y - OBB1.points[2].y),
				Vector2f(OBB2.points[0].x - OBB2.points[3].x,
				OBB2.points[0].y - OBB2.points[3].y),
				Vector2f(OBB2.points[0].x - OBB2.points[1].x,
				OBB2.points[0].y - OBB2.points[1].y)
			};

			for (int i = 0; i<4; i++)
			{
				float minOBB1, maxOBB1, minOBB2, maxOBB2;
				OBB1.transformateToaxis(axes[i], minOBB1, maxOBB1);
				OBB2.transformateToaxis(axes[i], minOBB2, maxOBB2);
				if (!((minOBB2 <= maxOBB1) && (maxOBB2 >= minOBB1)))
					return false;
			}
			return true;
	}
};

#endif