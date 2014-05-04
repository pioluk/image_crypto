#ifndef IMAGE_CRYPTO_UTIL_H
#define IMAGE_CRYPTO_UTIL_H

#include <SDL.h>

void set_pixel(SDL_Surface *surface, int x, int y, uint32_t pixel)
{
  int bpp = surface->format->BytesPerPixel;

  // finding address of the pixel
  uint8_t *p = (uint8_t *) surface->pixels + y * surface->pitch + x * bpp;

  switch (bpp) {
    // 8 bit
    case 1:
      *p = pixel;
      break;

    // 16 bit
    case 2:
      *(uint16_t *) p = pixel;
      break;

    // 24 bit
    case 3:
      if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
        p[0] = (pixel >> 16) & 0xff;
        p[1] = (pixel >> 8) & 0xff;
        p[2] = pixel & 0xff;
      }
      else {
        p[0] = pixel & 0xff;
        p[1] = (pixel >> 8) & 0xff;
        p[2] = (pixel >> 16) & 0xff;
      }
      break;

    // 32 bit
    case 4:
      *(uint32_t *) p = pixel;
      break;
  }
}

uint32_t get_pixel(SDL_Surface *surface, int x, int y)
{
  int bpp = surface->format->BytesPerPixel;

  // finding address of the pixel
  uint8_t *p = (uint8_t *) surface->pixels + y * surface->pitch + x * bpp;

  switch (bpp) {
    // 8 bit
    case 1:
      return *(uint8_t *)p;
      break;

    // 16 bit
    case 2:
      return *(uint16_t *)p;
      break;

    // 24 bit
    case 3:
      if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
        return p[0] << 16 | p[1] << 8 | p[2];
      }
      else {
        return p[0] | p[1] << 8 | p[2] << 16;
      }

      break;

    // 32 bit
    case 4:
      return *(uint32_t *)p;
      break;

    default:
      return 0;
  }
}

#endif

