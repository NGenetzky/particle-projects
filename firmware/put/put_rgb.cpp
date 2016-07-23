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

    char *p_arg;
    p_arg = strtok ( args, "," );
    auto r = atoi(p_arg);

    p_arg = strtok ( NULL, "," );
    auto g = atoi(p_arg);

    p_arg = strtok ( NULL, "," );
    auto b = atoi(p_arg);

    rgb_color(r,g,b);
    return 0;
}
