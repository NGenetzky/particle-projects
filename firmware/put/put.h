#pragma once
#include "global.h"

typedef unsigned int Id;
typedef int (*PutF)(const char *);
const unsigned int MAX_PATH_LENGTH = MAX_NAME_LENGTH;

struct Node {
    Id uid;
    char path[MAX_PATH_LENGTH];
    PutF put;
    Node() = default;
    Node(Id, const char*);
};

int put_setup();

// Exposed to end user
int put_function(String args);
void put_handler(const char *topic, const char *data);

// Putting values to the nodes.
int put_kv_pairs(const char *data);
int put(Id uid, const char *data);

// Getting and Setting the node.
int node_set(Id uid, const char *s, PutF f );
Node node_get(Id uid);
Id node_lookup(const char *path);
