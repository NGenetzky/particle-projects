
#include "node_setup.h"
#include "cmd.h"
#include "put.h"
#include "post.h"

extern void info(const char * name, const char * data);

extern void wreg_setup();
extern int wreg_set(const char* s);
extern int put_rgb(const char* s);
extern char* wreg_get();

namespace NODE_V1 {

int node_setup(Id node){
    int i = node;
    
    node_set(++i, "wreg");
    add_put(i, wreg_set);
    // Return the cached value of wreg. Check that it is the same value.
    cmd_set(i, "wreg", get_wreg);
    add_post(i, post_wreg);
    
    // node_set(++i, "led");
    // // Set the RGB color and cache what value it was.
    // add_put(i, put_led);
    // // Before: Output the pinMode of D7 and current value.
    // // After: Output the last value set. Check that is is same as current value.
    // cmd_set(i, "led", get_led);
    
    node_set(++i, "rgb");
    // Set the RGB color and cache what value it was.
    add_put(i, put_rgb);
    // Before: Output the status of rgb.
    // After: Output the current value.
    cmd_set(i, "rgb", get_rgb);
    add_post(i, put_rgb);
    
    // node_set(++i, "serial0");
    // // Should set the baud rate and enable.
    // add_put(i, put_serial0); 
    // // Before: This should inform the serial to call a set with args "baudrate".
    // cmd_set(i, "serial0", get_serial0);
    // add_post(++i, post_serial0);
    
    // node_set(++i, "serial1");
    // add_put(i, put_serial1);
    // cmd_set(i, "serial1", get_serial1);
    // add_post(++i, post_serial1);
    
    return i - node;
}

int wreg_set(const char *s){
    // strncpy(wreg, s, MAX_PUBLISH_LENGTH);
    // Particle.variable("var_wreg", wreg);
    info("wreg.debug", s);
    
    // wreg_setup();
    // wreg_set(s);
    return 0;
}

//      Return the cached value of wreg. Check that it is the same value.
int get_wreg(){
    char *p_wreg = wreg_get();
    info("wreg", p_wreg);
    return 0;
}

int post_wreg(const char *s ){
    // strcat?
    wreg_set(s);
    return 0;   
}

// RGB

int rgb_status= 0x00;
char rgb[MAX_PUBLISH_LENGTH +1];

int rgb_set(const char *s){
    strncpy(NODE_V1::rgb, s, MAX_PUBLISH_LENGTH);
    // Particle.variable("rgb", rgb);
    
    return put_rgb(s);
}

int get_rgb(){
    info("get_rgb", NODE_V1::rgb);
    return 0;
}



} // END NODE_V1