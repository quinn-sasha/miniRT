double clamp(double x, double lower_limit, double upper_limit)
{
	if (x < lower_limit)
		return (lower_limit);
	if (x > upper_limit)
		return (upper_limit);
	return (x);
}

//clamp クランプ（制限）　色の値を正しい表示可能な範囲内に収めるため
