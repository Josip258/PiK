#pragma once

#include <vector>
#include <iostream>

#include "camera.hpp"

/*
    \param x,y geometrijske koordinate tocke koja se provjerava
    \param max_iter maksimalni broj iteracija provjere pripadnosti skupu, default = 5
    \return broj iteracija potrebnih da se potvrdi pripadnost tocke skupu, -1 ako tocka ne pripada
*/
int mandelbrot_set(long double x, long double y, int max_iter = 5);

/*
    \param x,y koordinate piksela na ekranu
    \param camera camera
    \return koordinate tocke u geometrijskom sustavu
*/
std::pair<long double, long double> get_geometry_pos_from_pixels(int x, int y, Camera* camera);