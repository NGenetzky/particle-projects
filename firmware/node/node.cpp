#include "node.h"
#include <vector>

std::vector<Node> nodes;

Node::Node(Id uid, const char* s){
    this->uid = uid;
    strncpy(this->path, s, MAX_NAME_LENGTH);
}

// Getting and Setting the node.
int node_set(Id uid, const char *s){
    if(nodes.size() <= uid){
        // Assign to the next open index.
        Node new_node(uid, s);
        nodes.push_back(new_node);
        return nodes.size();

    } else if(uid < 0){ // Check if its negative.
        return -1;
        
    } else { 
        // Replace at a particular index.
        nodes[uid].uid = uid;
        strncpy(nodes[uid].path, s, MAX_NAME_LENGTH);
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

// Find an existing post from the name of its node.
Id find_key(const char *key){        
    unsigned int uid = strtoul(key, NULL, 10);
    if(uid == 0){
        return node_lookup(key);
    } else {
        return uid;
    }
}