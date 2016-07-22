#include "put.h"
#include <vector>
#include <map>

std::map<Id, PutF> vars;

extern void error(int error_id);
extern void info(const char * name, const char * data);

int put_setup(){
    bool success;
    Particle.function("put", put_function);

    success = Particle.subscribe("put", put_handler, MY_DEVICES); // Requires --private flag.
    if( !success ){ error(1000); }

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
    Id uid = find_key(path);

    char debug[MAX_PUBLISH_LENGTH];
    sprintf(debug, "(%u:%s)=%s", uid, path, p_value);
    info("echo_PUT", debug);

    // Put the value.
    return put(uid, p_value);
}

// Using the put functions.
int put(Id uid, const char *data){
    PutF f = vars[uid];
    if(f != NULL){
        return f(data);
    } else {
        return -1;
    }
}

// Adding new put functions
int add_put(Id uid, PutF f ){
    vars[uid] = f;
    return uid;
}
