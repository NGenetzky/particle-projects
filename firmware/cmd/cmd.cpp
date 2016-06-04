#include "cmd.h"

#include <vector>

#include "global.h"

// DO_FUNCTION in unique per device and supports return value.
// DO_SUBSCRIBE is a general to all devices and does not support return value.
#define DO_VARAIBLE
#define DO_FUNCTION 
#define DO_SUBSCRIBE 
    // Subscribe allows the command to be process by multiple photons.

std::vector<Cmd> cmds;
const int BUFF_LENGTH = MAX_VARIABLE_LENGTH; // https://community.particle.io/t/variable-of-string-type/6365/4?u=ngenetzky
char cmds_var[BUFF_LENGTH]; 
    
int ndef(){
    Particle.publish("CMD","ndef");
    return NO_CMD;
}

int cmd_setup(){
    bool success;
    #ifdef DO_VARAIBLE
        Particle.variable("cmds", cmds_var);
    #endif
    #ifdef DO_FUNCTION
        Particle.function("do", do_function);
    #endif
    #ifdef DO_SUBSCRIBE
        success = Particle.subscribe("do", do_handler, MY_DEVICES); // Requires --private flag.
        if( !success ){ error(1000); }
    #endif
    
    cmds.push_back( Cmd(0, "ndef", ndef) ); // Default function defined for ndef commands.
    cmds.push_back( Cmd(1, "cmd_publish", cmd_publish) ); // Outputs cmds
    return success;
}

// Exposed to end user
int do_function(String args){
    // If args is a number then will execute cmd that relates to that number.
    int cmdid = args.toInt();
    if(cmdid != 0){
        return execute(cmdid);
    }
    
    // Searches for command with name=args.
    return execute(cmd_get(args));
}

void do_handler(const char *topic, const char *data){
    if (strcmp(topic, "do")==0) {
        do_function(data);
    } else {
        error(9);
    }
}

// Exposed to other files.
int cmd_set(unsigned int uid, const char *s, int (*f) (void) ){
    if(cmds.size() < uid){
        // Assign the command to the next open index.
        cmds.push_back( Cmd(uid, s, f) );
        return cmds.size();

    } else if(uid < 0){ // Check if its negative.
        return -1;
        
    } else { 
        // Replace the commmand at a particular index.
        cmds[uid].uid = uid;
        cmds[uid].name = s;
        cmds[uid].f = f;
        return uid;
    }
}

int execute(Cmd cmd){
    return cmd.f();
}

int execute(unsigned int uid){
    return execute(cmd_get(uid));
}

/// Private (ish)
Cmd cmd_get(unsigned int uid){
    if(cmds.size() < uid){
        // Get Command by uid.
        for (auto c : cmds){
            if (c.uid == uid) {
                return c;
            }
        }
        return cmds[0];
    } else if(uid < 0){
        return cmds[0];

    } else { 
        // Get Command by index.
        return cmds[uid];
    }
}

Cmd cmd_get(String name){
    for (auto c : cmds){
        if (strcmp(name, c.name)==0) {
            return c;
        }
    }
    return cmds[0];
}

// Commands exported by this module.
// TODO: Change to use info(). Fix so that only 255 char of data is sent at time.
int cmd_publish(){
    cmd_update();
    Particle.publish("cmds=", cmds_var);
    return strlen(cmds_var);
}

int cmd_update(){
    strcpy(cmds_var, ""); // Empty the string
    char prefix = '[';
    int len;
    
    for( auto c : cmds){
        len =strlen(cmds_var);
        if(BUFF_LENGTH < len){
            error(19);
            break;
        }
        sprintf(cmds_var + len,"%c\"%d:%s\"",prefix, c.uid, c.name);
        prefix=',';
    }
    sprintf(cmds_var + strlen(cmds_var),"]");
    return strlen(cmds_var);
}
