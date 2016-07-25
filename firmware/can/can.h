#ifndef CAN_H
#define CAN_H

#include "application.h"
#include "global.h"

extern void info(const char * name, const char * data);
extern void error(int error_id);

// struct CANMessage
// {
//   uint32_t id;
//   bool     extended;
//   bool     rtr;
//   uint8_t  len;
//   uint8_t  data[8];
// }

// CAN public
int CAN_setup();
int CAN_event_handler(const char *event, const char *data);
int get_int_after_at_symbol(const char *event);

// CAN.out
void CAN_transmit_test();
void CAN_send_data_as_hex(int dest, const char *data);
void CAN_send_data_as_asci(int dest, const char *data);
    
// CAN.in
void CAN_receive_hex();
void CAN_receive_asci();
void CAN_publish_msg_as_hex(CANMessage msg);
void CAN_publish_msg_as_asci(CANMessage msg);

//Utility
void CAN_check_error_status();

#endif // CAN_H