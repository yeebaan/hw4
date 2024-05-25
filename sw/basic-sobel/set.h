#define INCLUDE_SET_H
#ifdef INCLUDE_SET_H
template<
  typename T,
  typename U,
  typename V,
  typename W,
  typename X,
  typename Y,
  typename Z>
auto set(
  T * array,
  U height,
  V width,
  W depth,
  X row,
  Y column,
  Z channel,
  T data) {
  if ((X{} < row && row < height) &&
      (Y{} < column && column < width) &&
      (Z{} < channel && channel < depth)) {
    return array[(row * width + column) * depth + channel] = data;
  }
  else {
  }
  return T();
}
#endif