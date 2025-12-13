double clamp(double x, double lower_limit, double upper_limit) {
  if (x < lower_limit)
    return lower_limit;
  if (x > upper_limit)
    return upper_limit;
  return x;
}

double min_double(double a, double b) {
  if (a < b)
    return a;
  return b;
}
