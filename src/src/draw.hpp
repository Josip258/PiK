#pragma once

#include <SDL2/SDL.h>
#include <vector>

#include "camera.hpp"
#include "fractals.hpp"

/*
    Crta fraktal na ekran
    \param width,height velicina prozora
    \param camera camera
*/
void draw_screen(int width, int height, Camera* camera, SDL_Renderer* gRenderer);

/*
    \param x,y koordinate ekrana
    \param camera camera
*/
void draw_pixel(int x, int y, int* color, SDL_Renderer* gRenderer);

/*
    \itaration iteracija trenutnog piksela
    \max_iterations maksimalni postavljeni broj iteracija, potrebno za računanje postotka boje
*/
std::vector<int> get_color(int iteration, int max_iterations);