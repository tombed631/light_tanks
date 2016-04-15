
#ifndef _TANK_TYPES_
#define _TANK_TYPES_

#include <glm\glm.hpp>

namespace p3d {

	/// Defines player id's
	enum class Player : char { PLAYER_1, PLAYER_2 };


	///Stores colors of player 1&2 tanks.
	struct PlTankColors {
		glm::vec3 firstPlayerColor;
		glm::vec3 secondPlayerColor;
	};

}

#endif