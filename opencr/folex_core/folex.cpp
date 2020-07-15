//

#include "folex.h"


Folex::Folex()
{

}

Folex::~Folex()
{

}

bool Folex::initFolex()
{
	diagnosis.init();
	
	dynamixel_driver.init();
	dynamixel_driver.enableDynamixel();
	//dynamixel_driver.initPosition();

	return true;
}

void Folex::testFolex()
{
	uint16_t index = 0;

	// 6-Point trajectory
	for (uint16_t i = 0; i < 6; i++)
	{
		kinematics.solveKinematics(i);

		std::vector<uint16_t> value;
		value.clear();
  	value.push_back(dynamixel_driver.convertRadianToValue(kinematics.theta1_));
  	value.push_back(dynamixel_driver.convertRadianToValue(kinematics.theta2_));

		index = 0;
		// DYNAMIXEL ID 1, 2
		for (uint8_t id = 1; id < 3; id++)
  	{
			dynamixel_driver.writeValue(id, ADDR_AX_MOVING_SPEED, dynamixel_driver.convertRpmToValue(AX_12A, 15.0));
  	  dynamixel_driver.writeValue(id, ADDR_AX_GOAL_POSITION, value.at(index));
			index++;
  	}

		index = 0;
		// DYNAMIXEL ID 7, 8
		for (uint8_t id = 7; id < 9; id++)
  	{
			dynamixel_driver.writeValue(id, ADDR_AX_MOVING_SPEED, dynamixel_driver.convertRpmToValue(AX_12A, 15.0));
  	  dynamixel_driver.writeValue(id, ADDR_AX_GOAL_POSITION, value.at(index));
			index++;
  	}

		delay(150);
	}
}
