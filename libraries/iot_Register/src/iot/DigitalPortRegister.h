
#include "iot/DigitalPort.h"
#include "iot/Register.h"

namespace iot {
    
iot::Register RegisterFactory( DigitalPort &dp ){
    return iot::Register(
        [&]() { return dp.get(); },
        [&]( int v ) { return dp.set( v ); }
    );
}

}