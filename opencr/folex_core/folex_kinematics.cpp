//

#include "folex_kinematics.h"


FolexKinematics::FolexKinematics()
{
	vector_x.clear();
	vector_x.push_back(129.7739);
	vector_x.push_back(129.7739);
	vector_x.push_back(118.0078);
	vector_x.push_back(113.7858);
	vector_x.push_back(118.0078);
	vector_x.push_back(129.7739);

	vector_y.clear();
	vector_y.push_back(-15.9013);
	vector_y.push_back(15.9);
	vector_y.push_back(1.8957);
	vector_y.push_back(-15.9013);
	vector_y.push_back(-33.6984);
	vector_y.push_back(-47.7027);
}

FolexKinematics::~FolexKinematics()
{

}

void FolexKinematics::solveKinematics(uint16_t point)
{
	cosineTheta2_ = (pow(vector_x.at(point), 2) + pow(vector_y.at(point), 2) - pow(LEG1, 2) - pow(LEG2, 2)) / (2 * LEG1 * LEG2);
	sineTheta2_ = sqrt(1 - pow(cosineTheta2_, 2)) * -1;
	theta1_ = atan2(vector_y.at(point), vector_x.at(point)) - atan2((LEG2 * sineTheta2_), (LEG1 + LEG2 * cosineTheta2_));
	theta2_ = atan2(sineTheta2_, cosineTheta2_);
}


