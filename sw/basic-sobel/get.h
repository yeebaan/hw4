// #include "get.h"
// get(source_bitmap, height, width, bytes_per_pixel, row, col, 0)
#define INCLUDE_GET_H
#ifdef INCLUDE_GET_H
template <
	typename T,
	typename U,
	typename V,
	typename W,
	typename X,
	typename Y,
	typename Z>
auto get(
	T *source_bitmap,
	U height,
	V width,
	W bytes_per_pixel,
	X row,
	Y col,
	Z channel)
{
	if ((X{} < row && row < height) &&
		(Y{} < col && col < width) &&
		(Z{} < channel && channel < bytes_per_pixel))
	{
		return source_bitmap[(row * width + col) * bytes_per_pixel + channel];
	}
	else
	{
	}
	return T();
}
#endif