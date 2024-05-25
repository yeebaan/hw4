#define INCLUDE_GET_H
#ifdef INCLUDE_GET_H
template<
  typename T,
  typename U,
  typename V,
  typename W,
  typename X,
  typename Y,
  typename Z>
auto get(
  T * array,
  U height,
  V width,
  W depth,
  X row,
  Y column,
  Z channel) {
  if ((X{} < row && row < height) &&
      (Y{} < column && column < width) &&
      (Z{} < channel && channel < depth)) {
    return array[(row * width + column) * depth + channel];
  }
  else {
  }
  return T();
}
#endif