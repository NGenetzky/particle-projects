#pragma once
#include "global.h"

#include "node.h"

typedef int (*PostF)(const char *);

int post_setup();

// Exposed to end user
int post_function(String args);
void post_handler(const char *topic, const char *data);

// Calls the relevant post.
int post(Id uid, const char *data);

// Adds a new post endpoint.
int add_post(Id uid, PostF f );
