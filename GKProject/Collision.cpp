
#include <SFML\Graphics.hpp>
#include "Collision.h"

namespace Collision
{

	class BoundingBox // Used in the BoundingBoxTest
	{
	public:
		BoundingBox(const sf::Sprite& Object) // Calculate the four points of the OBB from a transformed (scaled, rotated...) sprite
		{
			Transform trans = Object.getTransform();
			IntRect local = Object.getTextureRect();
			Points[0] = trans.transformPoint(0.f, 0.f);
			Points[1] = trans.transformPoint((float)(local.width), 0.f);
			Points[2] = trans.transformPoint((float)local.width, (float)local.height);
			Points[3] = trans.transformPoint(0.f, (float)local.height);
		}
		BoundingBox(const sf::RectangleShape& Object) // Calculate the four points of the OBB from a transformed (scaled, rotated...) sprite
		{
			Transform trans = Object.getTransform();
			IntRect local = Object.getTextureRect();
			Points[0] = trans.transformPoint(0.f, 0.f);
			Points[1] = trans.transformPoint((float)local.width, 0.f);
			Points[2] = trans.transformPoint((float)local.width, (float)local.height);
			Points[3] = trans.transformPoint(0.f, (float)local.height);
		}

		sf::Vector2f Points[4];

		void ProjectOntoAxis(const sf::Vector2f& Axis, float& Min, float& Max) // Project all four points of the OBB onto the given axis and return the dotproducts of the two outermost points
		{
			Min = (Points[0].x*Axis.x + Points[0].y*Axis.y);
			Max = Min;
			for (int j = 1; j<4; j++)
			{
				float Projection = (Points[j].x*Axis.x + Points[j].y*Axis.y);

				if (Projection<Min)
					Min = Projection;
				if (Projection>Max)
					Max = Projection;
			}
		}
	};

	bool PlayerWallCollision(const sf::Sprite& Object1, const sf::RectangleShape& Object2) {
		BoundingBox OBB1(Object1);
		BoundingBox OBB2(Object2);
		// Create the four distinct axes that are perpendicular to the edges of the two rectangles
		sf::Vector2f Axes[4] = {
			Vector2f(OBB1.Points[1].x - OBB1.Points[0].x,
			OBB1.Points[1].y - OBB1.Points[0].y),
			Vector2f(OBB1.Points[1].x - OBB1.Points[2].x,
			OBB1.Points[1].y - OBB1.Points[2].y),
			Vector2f(OBB2.Points[0].x - OBB2.Points[3].x,
			OBB2.Points[0].y - OBB2.Points[3].y),
			Vector2f(OBB2.Points[0].x - OBB2.Points[1].x,
			OBB2.Points[0].y - OBB2.Points[1].y)
		};

		for (int i = 0; i<4; i++) // For each axis...
		{
			float MinOBB1, MaxOBB1, MinOBB2, MaxOBB2;

			// ... project the points of both OBBs onto the axis ...
			OBB1.ProjectOntoAxis(Axes[i], MinOBB1, MaxOBB1);
			OBB2.ProjectOntoAxis(Axes[i], MinOBB2, MaxOBB2);

			// ... and check whether the outermost projected points of both OBBs overlap.
			// If this is not the case, the Seperating Axis Theorem states that there can be no collision between the rectangles
			if (!((MinOBB2 <= MaxOBB1) && (MaxOBB2 >= MinOBB1)))
				return false;
		}
		return true;
		}
}
