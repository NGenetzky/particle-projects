
#pragma once
#include "application.h"

namespace iot {
namespace particle {
    
bool setup_PF_tinker();

/* Function prototypes -------------------------------------------------------*/
int tinkerDigitalRead( String pin );
int tinkerDigitalWrite( String command );
int tinkerAnalogRead( String pin );
int tinkerAnalogWrite( String command );

}
}
