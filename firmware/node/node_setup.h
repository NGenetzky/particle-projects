#include "application.h"
#include "node.h"

const int NODE_SERIAL_START = 200;

namespace NODE_V1 {
    
int node_setup(Id node = NODE_SERIAL_START);
    
// namespace WREG {
int wreg_set(const char *);
int get_wreg();
int post_wreg(const char *);
// } namespace WREG

// namespace RGB {
int rgb_set(const char *);
int get_rgb();
// } namespace RGB


// // namespace WREG {
// int wreg_set(const char *));
// //      Return the cached value of wreg. Check that it is the same value.
// int get_wreg();
// int post_wreg(const char *));
// // } namespace WREG


} // End NODE_V1

// EOF

// int node_setup(){
//     int i = NODE_SERIAL_START;
    
//     node_set(++i, "wreg");
//     add_put(i, wreg_set);
//     // Return the cached value of wreg. Check that it is the same value.
//     cmd_set(i, "wreg", get_wreg);
//     add_post(++i, post_wreg);
    
//     node_set(++i, "led");
//     // Set the RGB color and cache what value it was.
//     add_put(i, put_led);
//     // Before: Output the pinMode of D7 and current value.
//     // After: Output the last value set. Check that is is same as current value.
//     cmd_set(i, "led", get_led);
    
//     node_set(++i, "rgb");
//     // Set the RGB color and cache what value it was.
//     add_put(i, put_rgb);
//     // Before: Output the status of rgb.
//     // After: Output the current value.
//     cmd_set(i, "rgb", get_rgb);
    
//     node_set(++i, "serial0");
//     // Should set the baud rate and enable.
//     add_put(i, put_serial0); 
//     // Before: This should inform the serial to call a set with args "baudrate".
//     cmd_set(i, "serial0", get_serial0);
//     add_post(++i, post_serial0);
    
//     node_set(++i, "serial1");
//     add_put(i, put_serial1);
//     cmd_set(i, "serial1", get_serial1);
//     add_post(++i, post_serial1);
    
//     return i - NODE_SERIAL_START;
// }
