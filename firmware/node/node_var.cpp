#include "node_var.h"
#include "node.h"

extern void info(const char * name, const char * data);

char nodes_str[MAX_VARIABLE_LENGTH];

void node_var_setup(){
    nodes_to_str(nodes_str);
    Particle.variable("nodes", nodes_str);
}

int print_node_var(){
    nodes_to_str(nodes_str);
    Particle.publish("nodes=", nodes_str);
    return strlen(nodes_str);
}
