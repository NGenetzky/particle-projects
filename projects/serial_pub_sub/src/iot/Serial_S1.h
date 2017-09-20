
#pragma once
#include "application.h" // Required for Particle.

namespace iot {
    
    int PF_s1_write( String msg )
    {
        return Serial1.write(msg);
    }
    
    bool setup_PF_s1_write( const char *name = "s0")
    {
        return Particle.function(name, iot::PF_s1_write);
    }
    
    void PS_s1_write(const char *event, const char *data)
    {
        Serial1.write(data);
    }
    
    bool setup_PS_s1_write( const char *name = "ttyS0")
    {
        return Particle.subscribe(name, iot::PS_s1_write, MY_DEVICES);
    }
    
    class Serial_S1
    {
        public:
        
        int setup(int baud=9600)
        {
            Serial1.begin(baud); // via TX/RX pins
            return 0;
        }
        
        void publish_buffer( const char *name = "s1")
        {
            this->buffer.push_back('\0');
            Particle.publish(name, this->buffer.data());
            this->buffer.clear();
        }
        
        void on_serial_event()
        {
            delay(100);
            auto char_available = Serial1.available();
            if(char_available==0){
                return;
            }
            for(auto i=0; i< char_available; i++){
                this->buffer.push_back(Serial1.read());
            }
            this->publish_buffer();
        }
        
        private:
        
        std::vector<char> buffer;
    };
};