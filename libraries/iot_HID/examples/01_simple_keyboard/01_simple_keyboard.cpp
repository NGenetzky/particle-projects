
#include "iot/PF_keyboard.h"

STARTUP(Keyboard.begin());

void setup()
{
    iot::setup_PF_kb_println();
    Particle.function("kb_click", iot::PF_kb_click);
}

void loop()
{

}