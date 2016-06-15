#include "device.h"
#include "application.h"

int device = UNKNOWN;

const char device_alias = ['M', 'P', 'C', 'L', 'E',
                          '?'];

char get_alias(){
    return device_alias[device];
}

int id_device(){
    char first_unique = System.deviceID().charAt(0);
    switch(first_unique){
        case '2':
            return ELI;
        case '3':
            if(System.deviceID().charAt(1) == 9){
                return LOGAN
            } else {
                return MATT;
            }
        case '4':
            return PARKER;
        case '5':
            return COMRAD;
        case '5':
            return COMRAD;
        case '5':
            return COMRAD;
        default:
            return UNKNOWN;
    }
}