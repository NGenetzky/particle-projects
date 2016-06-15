#include "post.h"

#include <vector>
#include <map>

std::map<Id, PostF> streams;
char post_default[MAX_NAME_LENGTH+1];

extern void error(int error_id);
extern void info(const char * name, const char * data);

int post_setup(){
    bool success;
    success = Particle.function("post", post_function);
    strncpy(post_default, "ndef", MAX_NAME_LENGTH);
    
    success = Particle.subscribe("@", post_handler, MY_DEVICES); // Requires --private flag.
    if( !success ){ error(1000); }
    return success;
}

// Exposed to end user
int post_function(String args){
    char argbuffer[MAX_ARG_LENGTH +1]; argbuffer[MAX_ARG_LENGTH]='\0';
    args.toCharArray(argbuffer, MAX_ARG_LENGTH);
    
    post_handler(post_default, argbuffer);
    return 0;
}

void post_handler(const char *topic, const char *data){
    Id key = find_key(&topic[1]);
    Serial1.printf("%s:%s", &topic[1], data);
    Particle.publish(&topic[1], data);
    post(key, data);
}

// Using the post functions.
int post(Id uid, const char *data){
    PostF f = streams[uid];
    if(f != NULL){
        return f(data);
    } else {
        return -1;
    }
}

// Adding new post functions
int add_post(Id uid, PostF f ){
    streams[uid] = f;
    return 0;
}

