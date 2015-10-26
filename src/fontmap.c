#include "fontmap.h"

void fontmap_init()
{
    p_surface_font = SDL_LoadBMP("./res/font.bmp");
}

static size_t find_layout(char character){
    for(int i=0;i<FONTMAP_NB;i++){
        if(character == font_layout[i])
            return i;
    }
    return -1;
}

void fontmap_print(int x,int y, SDL_Surface* destination, const char *text)
{
    SDL_Rect rect_src;
    SDL_Rect rect_dest;
    rect_dest.x = x;
    rect_dest.y = y;
    rect_dest.h = FONTMAP_SIZE;
    rect_dest.w = FONTMAP_SIZE;

    rect_src.x = 0;
    rect_src.y = 0;
    rect_src.h = FONTMAP_SIZE;
    rect_src.w = FONTMAP_SIZE;

    for( int show = 0; text[ show ] != '\0'; show++ ){
        int index = find_layout(text [show]);

        if(text[show] == '\n'){
            rect_dest.y += FONTMAP_SIZE + 1;
            rect_dest.x = x;
        }
        else if(text[show] == ' ' || index == -1){
            rect_dest.x += FONTMAP_SIZE + 1;
        }

        else{
            rect_src.x = index * FONTMAP_SIZE;
            SDL_BlitSurface(p_surface_font , &rect_src, destination, &rect_dest);
            rect_dest.x += FONTMAP_SIZE + 1;
        }
    }
}

int fontmap_printf(int x,int y, SDL_Surface* destination, const char *format, ...)
{
	va_list list;
	va_start(list,format);
	char text[BUFSIZ];
	vsprintf(text,format,list);
    fontmap_print(x, y, destination, text);
	va_end(list);
	return strlen(text);
}
