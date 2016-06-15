#include "put_do.h"

#include "node.h"
#include "put.h"
#include "cmd.h"

int put_do_setup(unsigned int start){
    auto i = start;
    
    node_set(i, "do");
    add_put(i, put_do);
    
    return ++i-start;
}

int put_do(const char *s){
    do_function(String(s));
    return 0;
}
