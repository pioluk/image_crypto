#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <SDL.h>
#include <SDL_image.h>
#include <fstream>
#include "util.h"

int main(int argc, char *argv[])
{
  // TODO: use some CSPRNG, like bcrypt
  srand(time(NULL));

  if (argc != 5) {
    fprintf(stderr, "Error: usage %s filename x y color_depth\n", argv[0]);
    return 1;
  }

  const char *filename = argv[1];
  const int width = atoi(argv[2]);
  const int height = atoi(argv[3]);
  const int depth = atoi(argv[4]);

  if (depth != 0 && depth != 1) {
    fprintf(stderr, "Error: wrong color depth value, use 1 for color image or 0 for grayscale\n");
    return 1;
  }

  SDL_Surface *image = SDL_CreateRGBSurface(0,
                                            width,
                                            height,
                                            24,
                                            0,
                                            0,
                                            0,
                                            0);

  if (image == nullptr) {
    fprintf(stderr, "Error: %s\n", SDL_GetError());
    return 1;
  }

  for (int i = 0; i < width; ++i) {
    for (int j = 0; j < height; ++j) {
      if (depth == 1) {
        uint8_t r, g, b;
        r = (uint8_t) rand() % 256;
        g = (uint8_t) rand() % 256;
        b = (uint8_t) rand() % 256;

        set_pixel(image, i, j, SDL_MapRGB(image->format,
                  r, g, b));
      }
      else {
        uint8_t color;
        color = (uint8_t) rand() % 256;

        set_pixel(image, i, j, SDL_MapRGB(image->format,
                  color, color, color));
      }
    }
  }

  SDL_SaveBMP(image, filename);

  SDL_FreeSurface(image);

  return 0;
}

