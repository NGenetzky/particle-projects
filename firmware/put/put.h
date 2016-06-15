#pragma once
#include "global.h"

#include "node.h"

typedef int (*PutF)(const char *);

int put_setup();

// Exposed to end user
int put_function(String args);
void put_handler(const char *topic, const char *data);

// Putting values to the nodes.
int put_kv_pairs(const char *data);
int put(Id uid, const char *data);

int add_put(Id uid, PutF f );