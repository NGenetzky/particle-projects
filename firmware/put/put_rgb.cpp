#include "put_rgb.h"

#include "node.h"
#include "put.h"
#include "rgb.h"

int put_rgb_setup(unsigned int start){
    auto i = start;
    node_set(i, "rgb");
    add_put(i, put_rgb);
    return ++i-start;
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