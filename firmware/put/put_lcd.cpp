#include "put_lcd.h"

#include "node.h"
#include "put.h"

LiquidCrystal_I2C *p_lcd;

int put_lcd_setup(unsigned int start, LiquidCrystal_I2C *lcd){
    p_lcd = lcd; // safe reference to lcd

    node_set(start+0,  "cursor");
    add_put(start+0,   put_cursor);

    node_set(start+1,  "lcd");
    add_put(start+1,   put_lcd);

    return 2;
}

int put_cursor(const char *s){
    char args[MAX_ARG_LENGTH];
    strncpy(args, s, MAX_ARG_LENGTH);

    char *p_arg;
    p_arg = strtok ( args, "," );
    int x = atoi(p_arg);

    p_arg = strtok ( NULL, "," );
    int y = atoi(p_arg);

    p_lcd->setCursor(x,y);
    return 0;
}

int put_lcd(const char *s){
    char args[MAX_ARG_LENGTH];
    strncpy(args, s, MAX_ARG_LENGTH);
    p_lcd->print(args);
    return 0;
}
