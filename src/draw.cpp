#include "draw.hpp"

#include <omp.h>

//Maksimalni broj iteracija mandelbrotovog seta, veći broj, sporiji algoritam, detaljnija slika
#define n_of_iterations 255

int* pixel_colors = nullptr;

void draw_screen(int width, int height, Camera* camera, SDL_Renderer* gRenderer){

    if (pixel_colors == nullptr)
    {
        pixel_colors = new int[width * height * 3];
    }

    #pragma omp parallel for num_threads(width)
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            std::pair<long double, long double> pos = get_geometry_pos_from_pixels(x - width/2, y - height/2, camera);
            int iterations = mandelbrot_set(pos.first, pos.second, n_of_iterations);
            std::vector<int> color = get_color(iterations, n_of_iterations);
            pixel_colors[(x * height + y) * 3 + 0] = color[0];
            pixel_colors[(x * height + y) * 3 + 1] = color[1];
            pixel_colors[(x * height + y) * 3 + 2] = color[2];
        }
    }

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            draw_pixel(x, y, &pixel_colors[(x * height + y) * 3], gRenderer);
        }
    }
}

void draw_pixel(int x, int y, int* color, SDL_Renderer* gRenderer){

    SDL_SetRenderDrawColor(gRenderer, color[0], color[1], color[2], 255);
    SDL_RenderDrawPoint(gRenderer, x, y);
}

std::vector<int> get_color(int iteration, int max_iterations){

    float p = (float)iteration / (float)max_iterations;

    std::vector<int> color1;
    std::vector<int> color2;
    float percentage = 1.0f;

    if (p < 0.16)
    {
        color1 = {0, 7, 100};
        color2 = {32, 107, 203};
        percentage = p / 0.16;
    } else if (p < 0.42)
    {
        color1 = {32, 107, 203};
        color2 = {237, 255, 255};
        percentage = p / 0.42;
    } else if (p < 0.6425)
    {
        color1 = {237, 255, 255};
        color2 = {255, 170, 0};
        percentage = p / 0.6425;
    } else if (p < 0.8575)
    {
        color1 = {255, 170, 0};
        color2 = {0, 2, 0};
        percentage = p / 0.8575;
    } else if (p <= 1.0) {
        color1 = {0, 2, 0};
        color2 = {0, 7, 100};
        percentage = p / 1.0;
    }

    return {(int)(color1[0] * percentage + color2[0] * (1.0 - percentage)), (int)(color1[1] * percentage + color2[1] * (1.0 - percentage)), (int)(color1[2] * percentage + color2[2] * (1.0 - percentage))};
}