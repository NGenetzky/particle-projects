#pragma once

#include "application.h" // Required for Particle.

namespace iot {
    
int PF_kb_println(String s)
{
    return Keyboard.println(s);
}

void setup_PF_kb_println(const char *name="kb_println")
{
    Particle.function(name, PF_println);
}

} // iot