#include <cassert>
#include <cstdlib>
#include <ctime>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "util.h"

int main(int argc, char *argv[])
{
  srand(time(NULL));

  assert(argc == 3);

  SDL_Surface *image = IMG_Load(argv[1]);
  if (image == NULL) {
    std::cerr << "Error opening image: " << IMG_GetError() << std::endl;
  }

  const int w = image->w;
  const int h = image->h;

  int count = 100000;

  while(count--) {
    int x1 = rand() % w;
    int y1 = rand() % h;

    int x2 = rand() % w;
    int y2 = rand() % h;

    int pixel = get_pixel(image, x1, y1);
    int pixel2 = get_pixel(image, x2, y2);

    set_pixel(image, x2, y2, pixel);
    set_pixel(image, x1, y1, pixel2);
  }

  SDL_SaveBMP(image, argv[2]);

  SDL_FreeSurface(image);

  return 0;
}

