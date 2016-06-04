#ifndef RGB_H
#define RGB_H

// Alternative to bit shifting/masking
// union RGBColor {
//     byte r,g,b;
//     int v;
// };

int rgb_release();
int rgb_color(int r, int g, int b); // Takes control and sets color
int rgb_create_value(int r, int g, int b);

// Colors from "https://en.wikipedia.org/wiki/Web_colors#HTML_color_names"
// (white, red, yellow, lime) are the most distinguishable
const int COLOR_WHITE=0xFFFFFF;
const int COLOR_SILVER=0xC0C0C0;
const int COLOR_GRAY=0x808080;
const int COLOR_BLACK=0x000000;
const int COLOR_RED=0xFF0000;
const int COLOR_MAROON=0x800000;
const int COLOR_YELLOW=0xFFFF00;
const int COLOR_OLIVE=0x808000;
const int COLOR_LIME=0x00FF00;
const int COLOR_GREEN=0x008000;
const int COLOR_AQUA=0x00FFFF;
const int COLOR_TEAL=0x008080;
const int COLOR_BLUE=0x0000FF;
const int COLOR_NAVY=0x000080;
const int COLOR_FUCHSIA=0xFF00FF;
const int COLOR_PURPLE=0x800080;

int rgb_white(); 
int rgb_silver();
int rgb_grey();
int rgb_black();
int rgb_red();
int rgb_maroon();
int rgb_yellow();
int rgb_olive();
int rgb_lime();
int rgb_green();
int rgb_aqua();
int rgb_teal();
int rgb_blue();
int rgb_navy();
int rgb_fuchsia();
int rgb_purple();

#endif // CMD_RGB_H
