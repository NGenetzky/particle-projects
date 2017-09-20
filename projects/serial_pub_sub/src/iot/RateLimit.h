

#pragma once
#include "application.h" // Required for Particle.

// #define RATELIMIT_PUBLISH_WHEN_GET_FAILS

namespace iot {
    
    // Based off the idea of printk_ratelimit used in the linux kernel.
    class RateLimit
    {
        public:
        
        RateLimit(
            unsigned burst_limit = 3,
            unsigned ms_between_bursts=5000
        )
            : ratelimit_burst(burst_limit)
            , timer(ms_between_bursts, &iot::RateLimit::refresh_limit, *this, false)
        {
            
        }
        
        int setup()
        {
            this->timer.start();
            return 0;
        }
        
        // The function returns true as long as the limit of number of messages printed does not excedd the limit set. Once the limit exceeds the functions starts retuning "0" . 
        bool ratelimit()
        {
            return (0!=counter);
        }
        
        bool get()
        {
            if(this->counter)
            {
                --this->counter;
                return true;
            }
#ifdef RATELIMIT_PUBLISH_WHEN_GET_FAILS
            Particle.publish("RateLimit", "Exceeded limit");
#endif
            return false;
        }
        
        void refresh_limit()
        {
            this->counter = this->ratelimit_burst;
        }
        
        private:
        const unsigned ratelimit_burst = 3;
        Timer timer;
        unsigned counter=0;
    };
};