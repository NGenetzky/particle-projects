#include "put_rgb.h"

#include "put.h"
#include "rgb.h"

int setup_put_rgb(){
    node_set(575, "rgb", put_rgb);
    return 1;
}

int put_rgb(const char *s){
    char args[MAX_ARG_LENGTH];
    strncpy(args, s, MAX_ARG_LENGTH);
    
    int r;
    int g;
    int b;
    
    char *p_arg;
    p_arg = strtok ( args, "," );
    r = atoi(p_arg);
    
    p_arg = strtok ( NULL, "," );
    g = atoi(p_arg);
    
    p_arg = strtok ( NULL, "," );
    b = atoi(p_arg);
    
    rgb_color(r,g,b);
    return 0;
}