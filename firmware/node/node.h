#pragma once
#include "global.h"

typedef unsigned int Id;
const unsigned int MAX_PATH_LENGTH = MAX_NAME_LENGTH;

struct Node {
    Id uid;
    char path[MAX_PATH_LENGTH];

    Node() = default;
    Node(Id, const char*);
};

// Getting and Setting the node.
int node_set(Id uid, const char *s);
Node node_get(Id uid);
Id node_lookup(const char *path);

// Find an existing post from the name of its node.
Id find_key(const char *key);

int nodes_to_str(char *nodes_str);

// Approximatiely the virtual data of this node. Minus the path.
// struct NodeData{
//     Id node;
//     PutF set;
//     PostF post;
//     int (*get) (void);
// };
