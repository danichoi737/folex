//

#ifndef FOLEX_KINEMATICS_H
#define FOLEX_KINEMATICS_H

#if defined(__OPENCR__)
	#include <Eigen.h>
#else
	#include <eigen3/Eigen/Eigen>
	#include <eigen3/Eigen/LU>
#endif
#include <math.h>
#include <vector>


#define LEG1 		67.5			// Leg-1 length 67.50 mm = 0.06750 m
#define LEG2 		82.35			// Leg-2 length 82.35 mm = 0.08235 m


class FolexKinematics
{
private:
	std::vector<double> vector_x;
	std::vector<double> vector_y;
	double sineTheta2_, cosineTheta2_;

public:
	FolexKinematics();
	~FolexKinematics();
	void solveKinematics(uint16_t point);
	double theta1_, theta2_;
};

#endif // FOLEX_KINEMATICS_H
