// #include "h4main.h"
// int main(int argc, char *argv[]) {
//   h4main(read_bmp, write_bmp, write_data_to_ACC, read_data_from_ACC, height, width, bytes_per_pixel, source_bitmap, SOBELFILTER_START_ADDR, SOBELFILTER_READ_ADDR);
// }
#define INCLUDE_H4MAIN_H
#ifdef INCLUDE_H4MAIN_H
#include "get.h"
#include "set.h"
template <
	typename T, typename T1,
	typename U, typename U1,
	typename V, typename V1, typename V2, typename V3,
	typename W, typename W1, typename W2, typename W3,
	typename X, typename Y, typename Z, typename A, typename B, typename C>
auto h4main(
	T read_bmp(T1),
	U write_bmp(U1),
	V write_data_to_ACC(V1, V2, V3),
	W read_data_from_ACC(W1, W2, W3),
	X height, Y width, Z bytes_per_pixel, A *source_bitmap, B SOBELFILTER_START_ADDR, C SOBELFILTER_READ_ADDR)
{
	read_bmp("lena_std_short.bmp");
	for (X row{}; row < height; row++)
	{
		for (Y col{}; col < width + 4; col++)
		{
			const std::array<A, 15> tb_to_dut{
				get(source_bitmap, height, width, bytes_per_pixel, row - 2, col - 2, 0),
				get(source_bitmap, height, width, bytes_per_pixel, row - 2, col - 2, 1),
				get(source_bitmap, height, width, bytes_per_pixel, row - 2, col - 2, 2),
				get(source_bitmap, height, width, bytes_per_pixel, row - 1, col - 2, 0),
				get(source_bitmap, height, width, bytes_per_pixel, row - 1, col - 2, 1),
				get(source_bitmap, height, width, bytes_per_pixel, row - 1, col - 2, 2),
				get(source_bitmap, height, width, bytes_per_pixel, row + 0, col - 2, 0),
				get(source_bitmap, height, width, bytes_per_pixel, row + 0, col - 2, 1),
				get(source_bitmap, height, width, bytes_per_pixel, row + 0, col - 2, 2),
				get(source_bitmap, height, width, bytes_per_pixel, row + 1, col - 2, 0),
				get(source_bitmap, height, width, bytes_per_pixel, row + 1, col - 2, 1),
				get(source_bitmap, height, width, bytes_per_pixel, row + 1, col - 2, 2),
				get(source_bitmap, height, width, bytes_per_pixel, row + 2, col - 2, 0),
				get(source_bitmap, height, width, bytes_per_pixel, row + 2, col - 2, 1),
				get(source_bitmap, height, width, bytes_per_pixel, row + 2, col - 2, 2),
			};
			write_data_to_ACC(SOBELFILTER_START_ADDR, tb_to_dut.data(), tb_to_dut.size());
			const std::array<A, 1> dut_to_tb{};
			read_data_from_ACC(SOBELFILTER_READ_ADDR, dut_to_tb.data(), dut_to_tb.size());
			set(source_bitmap, height, width, bytes_per_pixel, row, col - 4, 0, dut_to_tb[0]);
			set(source_bitmap, height, width, bytes_per_pixel, row, col - 4, 1, dut_to_tb[0]);
			set(source_bitmap, height, width, bytes_per_pixel, row, col - 4, 2, dut_to_tb[0]);
		}
	}
	write_bmp("lena_std_out.bmp");
}
#endif