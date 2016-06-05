
#include "application.h"
#include "cmd_rgb.h"

#include "rgb.h"
#include "cmd.h"

const int CMD_RGB_START = 550;

int cmd_rgb_setup(){
    int i=CMD_RGB_START;
    
    cmd_set(i++, "release", rgb_release);
    
    // (white, red, yellow, lime) are the most distinguishable
    cmd_set(i++, "white", rgb_white);
    cmd_set(i++, "silver", rgb_silver);
    cmd_set(i++, "grey", rgb_grey);
    cmd_set(i++, "black", rgb_black);
    cmd_set(i++, "red", rgb_red);
    cmd_set(i++, "maroon", rgb_maroon);
    cmd_set(i++, "yellow", rgb_yellow);
    cmd_set(i++, "olive", rgb_olive);
    cmd_set(i++, "lime", rgb_lime);
    cmd_set(i++, "green", rgb_green);
    cmd_set(i++, "aqua", rgb_aqua);
    cmd_set(i++, "teal", rgb_teal);
    cmd_set(i++, "blue", rgb_blue);
    cmd_set(i++, "navy", rgb_navy);
    cmd_set(i++, "fuchsia", rgb_fuchsia);
    cmd_set(i++, "purple", rgb_purple);
    
    return i-CMD_RGB_START;
}

// Example
// white,silver,grey,black,red,maroon,yellow,olive,lime,green,aqua,teal,blue,navy,fuchsia,purple,
