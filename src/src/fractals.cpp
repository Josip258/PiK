#include "fractals.hpp"


int mandelbrot_set(long double x, long double y, int max_iter){
	
	int iterations = 0;
	long double cur_x = 0;
	long double cur_y = 0;

	while (cur_x*cur_x + cur_y*cur_y < 4 && iterations < max_iter)
	{
		long double xtemp = cur_x*cur_x - cur_y*cur_y + x;
		cur_y = 2*cur_x*cur_y + y;
		cur_x = xtemp;
		iterations++;
	}
	
	return iterations;
}

std::pair<long double, long double> get_geometry_pos_from_pixels(int x, int y, Camera* camera){
	long double xg = camera->zoom * (long double)x + camera->pos.first;
	long double yg = camera->zoom * (long double)y + camera->pos.second;
	return {xg, yg};
}