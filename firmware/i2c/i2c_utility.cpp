#include "i2c_utility.h"
#include "application.h"

#include <vector>

std::vector<char> i2c_data;

extern void info(const char * name, const char * data);
const int I2C_BUFFER_SIZE = 32;

int I2C_setup_master(){
    if ( Wire.isEnabled() ) {
        Wire.end();
        info("I2C.setup", "reset;begin(Master)");
    } else {
        info("I2C.setup", "begin(Master)");
    }

    Wire.begin();
    return 0;
}

int I2C_setup_slave(int my_address){
    char setup_string[20];
    if ( Wire.isEnabled() ) {
        Wire.end();
        sprintf(setup_string, "reset;begin(%d)", my_address);
        // Particle.publish("I2C.setup", String("reset;begin("+String(my_address)+")"));
    } else{
        sprintf(setup_string, "begin(%d)", my_address);
        // Particle.publish("I2C.setup", String("begin("+String(my_address)+")"));
    }
    info("I2C.setup", setup_string);

    Wire.begin(my_address);                  // join i2c bus
    Wire.onReceive(I2C_on_receive_default); // register default event
    
    return my_address;
}

void I2C_on_receive_default(int bytes){
    for(int i=0; i< bytes; i++){
        i2c_data.push_back(Wire.read());
    }
    
    // char buff[I2C_BUFFER_SIZE +1]; buff[I2C_BUFFER_SIZE] ='\0';
    // if(I2C_BUFFER_SIZE < bytes){
    //     bytes = I2C_BUFFER_SIZE;
    // }
    // if(0 < bytes){
    //     for(int i=0; i< bytes; i++){
    //         buff[i] = Wire.read();
    //     }
        
    //     info("i2c_in", buff);
    // }
}

void I2C_end_transmission_debug(int ret_code){
  char error_string[65];
  switch(ret_code){
    case 0: sprintf(error_string,"0: success"); break;
    case 1: sprintf(error_string,"1: busy timeout upon entering endTransmission()"); break;
    case 2: sprintf(error_string,"2: START bit generation timeout"); break;
    case 3: sprintf(error_string,"3: end of address transmission timeout"); break;
    case 4: sprintf(error_string,"4: data byte transfer timeout"); break;
    case 5: sprintf(error_string,"5: data byte transfer succeeded, busy timeout immediately after"); break;
  }
  if(ret_code != 0){
    info("I2C_END_TRANSMISSION", error_string);
  }
}

int I2C_scan(){
    char I2C_slaves[40]; // 10 address array * 4 char max.
    int error;
    int slaves[10]= {0};
    int i_slaves=0;
    
    if ( Wire.isEnabled() ) {
        //info("I2C.setup", "reset;begin(Master)");
        #warning Assumes that device is acting as master.
    } else {
        I2C_setup_master(); // Must be master to scan.
    }
    
    for(int address = 1; address < 127; address++ ){
        Wire.beginTransmission(address);
        error = Wire.endTransmission();
        
        if(error==0){ // Ack from slave
            slaves[i_slaves] = address;
            i_slaves++;
        }
    }

    if(i_slaves==0){
        info("I2C.SCAN", "No Slaves found");
    } else{
        sprintf(I2C_slaves, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
                slaves[0], slaves[1], slaves[2], slaves[3], slaves[4],
                slaves[5], slaves[6], slaves[7], slaves[8], slaves[9]);
        info("I2C.SCAN", I2C_slaves); 
    }
    return i_slaves;
}
