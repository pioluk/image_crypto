#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <SDL.h>
#include <SDL_image.h>
#include "util.h"

int main(int argc, char *argv[])
{
  srand(time(NULL));

  if (argc != 2) {
    fprintf(stderr, "Usage %s image\n", argv[0]);
    return 1;
  }

  SDL_Surface *image = IMG_Load(argv[1]);
  if (image == nullptr) {
    fprintf(stderr, "Error: %s\n", IMG_GetError());
    return 1;
  }

  for (int i = 0; i < image->w; i += 8) {
    for (int j = 0; j < image->h; j += 8) {
      int x = rand() % image->w;
      int y = rand() % image->h;

      int pixel = get_pixel(image, i, j);
      int pixel2 = get_pixel(image, x, y);

      set_pixel(image, i, j, pixel2);
      set_pixel(image, x, y, pixel);
    }
  }

  SDL_SaveBMP(image, "out.bmp");

  SDL_FreeSurface(image);

  return 0;
}

