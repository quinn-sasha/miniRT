#include "math_utils.h"

double	degrees_to_radians(double degrees)
{
	return (degrees * (M_PI / 180.0));
}

double schlick(double cosine, double refract_idx)
{
	//垂直に入射するときの反射率
	double r0 = (1.0 - refract_idx) / (1 + refract_idx);
	r0 *= r0;
	return r0 + (1.0 - r0) * pow((1.0 - cosine), 5.0);
}
