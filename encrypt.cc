#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <SDL.h>
#include <SDL_image.h>
#include "util.h"

int main(int argc, char *argv[])
{
  assert(argc == 4);

  SDL_Surface *image = IMG_Load(argv[1]);
  if (image == nullptr) {
    fprintf(stderr, "Error: %s\n", IMG_GetError());
    return 1;
  }

  SDL_Surface *key   = IMG_Load(argv[2]);
  if (key == nullptr) {
    fprintf(stderr, "Error: %s\n", IMG_GetError());
    return 1;
  }

  const int key_width  = key->w;
  const int key_height = key->h;
  const int width      = image->w;
  const int height     = image->h;

  for (int kj = 0; kj < key_height; ++kj) {
    for (int ki = 0; ki < key_width; ++ki) {
      for (int j = 0; j < height; ++j) {
        // for (int i = width - 1; i >= 0; --i) {
        for (int i = 0; i < width; ++i) {
          int32_t offset = 0;
          uint8_t r, g, b;
          SDL_GetRGB(get_pixel(key, (i/* + ki*/) % key_width, (j/* + kj*/) % key_height), key->format,
                     &r, &g, &b);
          offset = (r * b * g);

          int32_t offset_x = static_cast<int>(log2(offset + i * r * b - j * g)) % width;
          int32_t offset_y = static_cast<int>(log2(offset + j * r * b - j * g)) % height;

          uint32_t pixel1 = get_pixel(image, i, j);
          uint32_t pixel2 = get_pixel(image, offset_x, offset_y);

          pixel1 ^= r * g * b * i;
          pixel2 ^= (~r) * (~g) * (~b) * j;

          set_pixel(image, i, j, pixel2);
          set_pixel(image, offset_x, offset_y, pixel1);
        }
      }
    }
  }

  SDL_SaveBMP(image, argv[3]);

  SDL_FreeSurface(key);
  SDL_FreeSurface(image);

  return 0;
}
