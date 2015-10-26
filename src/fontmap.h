#ifndef FONTMAP_H
#define FONTMAP_H

#include <stdlib.h>
#include <stdio.h>

#include <SDL/SDL.h>

#define FONTMAP_SIZE    7
#define FONTMAP_NB      38

static char font_layout[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '!', '-'};
static SDL_Surface* p_surface_font;

void fontmap_init();
inline size_t find_layout(char character);
void fontmap_print(int x,int y, SDL_Surface* destination, const char *text);
int fontmap_printf(int x,int y, SDL_Surface* destination, const char *format, ...);

#endif
