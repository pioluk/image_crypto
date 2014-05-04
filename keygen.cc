#include <cstdio>
#include <cstdlib>
#include <SDL.h>
#include <SDL_image.h>
#include <fstream>
#include "util.h"

int main(int argc, char *argv[])
{
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

  std::ifstream random("/dev/urandom");

  if (!random.is_open()) {
    fprintf(stderr, "Error opening random");
    return 1;
  }

  for (int i = 0; i < width; ++i) {
    for (int j = 0; j < height; ++j) {
      if (depth == 1) {
        uint8_t rgb[3];
        random.read(reinterpret_cast<char*>(&rgb), 3);

        set_pixel(image, i, j, SDL_MapRGB(image->format,
                  rgb[0], rgb[1], rgb[2]));
      }
      else {
        uint8_t color;
        random.read(reinterpret_cast<char*>(&color), 1);

        set_pixel(image, i, j, SDL_MapRGB(image->format,
                  color, color, color));
      }
    }
  }

  SDL_SaveBMP(image, filename);

  SDL_FreeSurface(image);

  return 0;
}

