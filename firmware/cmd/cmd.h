#ifndef CMD_H
#define CMD_H

#include "application.h"

extern void error(int error_id);

int ndef(); // Used in the struct initilizer.
const int NO_CMD = -1;
struct Cmd {
    int uid;
    char const *name; // Characters are immutable. The pointer is mutable. 
    int (*f) (void);
    
    // Do these constructors automatiically get moved to cpp?
    Cmd():uid(NO_CMD), name("ndef"), f(ndef) { }
    Cmd(int i, char const *c, int (*f) (void)):uid(i),name(c), f(f) { }
};

//Functions
int cmd_setup();
int do_function(String args);
void do_handler(const char *topic, const char *data);

// interacting with the Cmd struct
int cmd_set(unsigned int uid, char const * s, int (*f) (void) );
Cmd cmd_get(unsigned int uid);
Cmd cmd_get(String name);
int execute(Cmd cmd);
int execute(unsigned int uid);

int cmd_publish();
int cmd_update();

#endif // CMD_H