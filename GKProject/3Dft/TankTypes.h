
#ifndef _TANK_TYPES_
#define _TANK_TYPES_

namespace p3d {

	//
	//	Defines possible types of the tanks.
	//
	enum class TankType : char { RED_FLAMINGO, GREEN_DESTROYER, WHITE_NIGGA };


	//
	//	Structure that stores types of tanks for two players.
	//
	struct PlTankTypes {
		TankType firstPlayerTankType;
		TankType secondPlayerTankType;
	};

}

#endif