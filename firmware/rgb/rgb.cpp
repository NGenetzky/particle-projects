
#include "application.h"
#include "rgb.h"

#include "cmd.h"

int rgb_release(){
    RGB.control(false); return 0;
}
int rgb_color(int v){ // Takes control and sets color
    RGB.control(true);
    // Uses Bit Masks and Bit shifting 
    // to extract the 3rd, 2nd, and 1st least significant bytes of the int v.
    RGB.color((v & 0x00FF0000) >> 16, (v & 0x0000FF00) >> 8, (v & 0x000000FF));
    return 0;
}

int rgb_create_value(int r, int g, int b){
    return ((0<<24)|(r<<16)|(g<<8)|(b));
}

int rgb_white(){
    return rgb_color(COLOR_WHITE);
}
int rgb_silver(){
    return rgb_color(COLOR_SILVER);
}
int rgb_grey(){
    return rgb_color(COLOR_GRAY);
}
int rgb_black(){
    return rgb_color(COLOR_BLACK);
}
int rgb_red(){
    return rgb_color(COLOR_RED);
}
int rgb_maroon(){
    return rgb_color(COLOR_MAROON);
}
int rgb_yellow(){
    return rgb_color(COLOR_YELLOW);
}
int rgb_olive(){
    return rgb_color(COLOR_OLIVE);
}
int rgb_lime(){
    return rgb_color(COLOR_LIME);
}
int rgb_green(){
    return rgb_color(COLOR_GREEN);
}
int rgb_aqua(){
    return rgb_color(COLOR_AQUA);
}
int rgb_teal(){
    return rgb_color(COLOR_TEAL);
}
int rgb_blue(){
    return rgb_color(COLOR_BLUE);
}
int rgb_navy(){
    return rgb_color(COLOR_NAVY);
}
int rgb_fuchsia(){
    return rgb_color(COLOR_FUCHSIA);
}
int rgb_purple(){
    return rgb_color(COLOR_PURPLE);
}