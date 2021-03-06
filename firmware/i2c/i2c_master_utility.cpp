#include "i2c_master_utility.h"
#include "application.h"

extern void info(const char * name, const char * data);

static bool is_master = false;
static uint8_t last_slave = 0;

namespace i2c_master {

    int setup(){
        if ( Wire.isEnabled() ) {
            Wire.end();
            info("I2C.setup", "reset;begin(Master)");
        } else {
            info("I2C.setup", "begin(Master)");
        }

        is_master = true;
        Wire.begin();
        return 0;
    }

    int open(uint8_t new_slave){
        auto old = last_slave;
        last_slave = new_slave;
        return old;
    }

    int write(std::vector<uint8_t> d){
        auto len = d.size();
        if( 32 < len ){
            len = 32;
            info("i2c_master", "Write is limited to first 32 bytes.");
        }
        auto data = d.data();
        Wire.beginTransmission(last_slave); // transmit to slave device #4
        Wire.write(data, len);             // send data from vector.
        return Wire.endTransmission();    // stop transmitting
    }

    std::vector<uint8_t> read(unsigned bytes_requested){
        std::vector<uint8_t> data;
        auto requested = bytes_requested; 
        if( 32 < requested ){
            requested = 32;
            info("i2c_master", "Read is limited to first 32 bytes.");
        }

        auto received = Wire.requestFrom(last_slave, requested);
        // slave may send less than requested
        while(Wire.available()) {
            char c = Wire.read();    // receive a byte as character
            data.push_back(c);
        }
        if(requested != data.size()){
            info("i2c_master", "Read did not receive expected number of bytes.");
        }
        return data;
    }

    void print_end_transmission_rv(int ret_code){
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

    int scan(){
        char I2C_slaves[40]; // 10 address array * 4 char max.
        int error;
        int slaves[10]= {0};
        int i_slaves=0;
        
        if ( Wire.isEnabled() ) {
            //info("I2C.setup", "reset;begin(Master)");
            // #warning Assumes that device is acting as master.
            if(!is_master){
                setup(); // Must be master to scan.
            }
        } else {
            scan(); // Must be master to scan.
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

} // i2c_master
