#pragma once

#include "application.h" // Required for Particle.

namespace iot {
    
int PF_kb_println(String s)
{
    return Keyboard.println(s);
}

void setup_PF_kb_println(const char *name="kb_println")
{
    Particle.function(name, PF_kb_println);
}

KeyReport get_C_A_t()
{
    KeyReport kr;
    kr.modifiers |= MOD_LCTRL;
    kr.modifiers |= MOD_LALT;
    kr.keys[0] = UsbKeyboardScanCode::KEY_T;
    return kr;
}

// https://github.com/spark/firmware/blob/d30e03f9c9b638c87726f74832802eec3fe6f603/wiring/inc/spark_wiring_usbkeyboard.h
// https://github.com/spark/firmware/blob/develop/wiring/inc/spark_wiring_usbkeyboard_scancode.h#L5
int from_carrot_notation(KeyReport & kr, String s)
{
    if('<' != s.charAt(0)){ return -1; }
    for(unsigned i=1; i<s.length(); i++)
    {
        auto c = s.charAt(i);
        if('>' == c) { break; }
        switch(c)
        {
            case 'S': kr.modifiers |= MOD_LSHIFT; break;
            case 'C': kr.modifiers |= MOD_LCTRL; break;
            case 'A': kr.modifiers |= MOD_LALT; break;
            case '-': break;
        }
    }
    // kr.keys[0] = usb_hid_asciimap[c];
    kr.keys[0] = KEY_T;
    return 0;
}

int PF_kb_click(String s)
{
    auto kr = get_C_A_t();
    
    // auto kr = KeyReport();
    // auto rv = from_carrot_notation(kr,s);
    // if(0!=rv){ return rv; }
    
    Keyboard.click(kr.keys[0], kr.modifiers);
    return 0;
}

} // iot