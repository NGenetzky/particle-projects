#include "put.h"
#include <vector>

#define PUT_FUNCTION
#define PUT_SUBSCRIBE

std::vector<Node> nodes;
extern void error(int error_id);
extern void info(const char * name, const char * data);
    
static
int info_echo(const char *msg){
    info("echo", msg);
    return 0;
}

Node::Node(Id uid, const char* s){
    this->uid = uid;
    strncpy(this->path, s, MAX_NAME_LENGTH);
}

int put_setup(){
    bool success;
    #ifdef PUT_FUNCTION
        Particle.function("put", put_function);
    #endif
    #ifdef PUT_SUBSCRIBE
        success = Particle.subscribe("put", put_handler, MY_DEVICES); // Requires --private flag.
        if( !success ){ error(1000); }
    #endif
    
    auto echo = Node(0,"echo");
    echo.put=info_echo;
    nodes.push_back(echo);
    
    return success;
}

// Exposed to end user
int put_function(String args){
    char argbuffer[MAX_ARG_LENGTH +1]; argbuffer[MAX_ARG_LENGTH]='\0';
    args.toCharArray(argbuffer, MAX_ARG_LENGTH);
    return put_kv_pairs(argbuffer);
}

void put_handler(const char *topic, const char *data){
    put_kv_pairs(data);
}

int put_kv_pairs(const char *data){
    // Copy portion containing path into a mutatable buffer
    char path[MAX_PATH_LENGTH+1]; path[MAX_PATH_LENGTH]='\0';
    strncpy(path, data, MAX_PATH_LENGTH);
    
    // Find first = sign.
    char* p_equal = strchr(path, '=');
    // End the string at the = sign.
    *p_equal = '\0';
    
    // Set value to characters after the equal sign.
    char *p_value = strchr(data, '='); p_value++;
    
    // Identify the key with a lookup.
    Id uid = node_lookup(path);
    
    char debug[MAX_PUBLISH_LENGTH];
    sprintf(debug, "(%u:%s)=%s", uid, path, p_value);
    Particle.publish("PUT_debug", debug);
    
    // Put the value.
    return put(uid, p_value);
}

int put(Id uid, const char *data){
    return node_get(uid).put(data);
}

// Getting and Setting the node.
int node_set(Id uid, const char *s, PutF f ){
    if(nodes.size() <= uid){
        // Assign to the next open index.
        Node new_node(uid, s);
        new_node.put = f;
        nodes.push_back(new_node);
        return nodes.size();

    } else if(uid < 0){ // Check if its negative.
        return -1;
        
    } else { 
        // Replace at a particular index.
        nodes[uid].uid = uid;
        strncpy(nodes[uid].path, s, MAX_NAME_LENGTH);
        nodes[uid].put = f;
        return uid;
    }
}

Node node_get(Id uid){
    if(nodes.size() < uid){
        // Get Command by uid.
        for (auto n : nodes){
            if (n.uid == uid) {
                return n;
            }
        }
        return nodes[0];
    } else if(uid < 0){
        return nodes[0];

    } else { 
        // Get Command by index.
        return nodes[uid];
    }
}


Id node_lookup(const char *path){
    for (auto n : nodes){
        if (strcmp(path, n.path)==0) {
            return n.uid;
        }
    }
    return 0; // Otherwise echo what they put.
}