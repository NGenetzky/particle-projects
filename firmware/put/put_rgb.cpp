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

