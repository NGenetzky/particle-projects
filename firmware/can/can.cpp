
#include "can.h"

CANChannel can(CAN_D1_D2, 32, 32); // (pins, rxQueueSize, txQueueSize);

int CAN_setup(){
    can.begin(125000); // pick the baud rate for your network
    // accept one message. If no filter added by user then accept all messages
    // can.addFilter(0x100, 0x7FF); // (id, mask);
    bool success = Particle.subscribe("can", CAN_event_handler, MY_DEVICES);
    if( !success ){ error(1000); }
    return success;
}

int CAN_event_handler(const char *event, const char *data){
    int dest = 0x100; // Default destination
    
    if (strncmp(event, "can@", strlen("can@"))==0) {
        dest = String(&event[4]).toInt();
        CAN_send_data_as_asci(dest, data);
        return -2;
        
    } else if (strcmp(event, "can")==0) {
        CAN_send_data_as_asci(dest, data);
        return 0;
        
    } else if (strcmp(event, "can.test()")==0) {
        CAN_transmit_test();
        return 0;
        
    } else {
        return -1;
    }
    return 17;
}

void CAN_send_data_as_hex(int dest, const char *data){
    // union IntByte {
    //   byte b[8];
    //   int i[2];
    // } msgdata;
    int len = strlen(data);
    char one_byte[3] = {'\0','\0','\0'}; // 8 * (byte is 2 char) + \0
    CANMessage tx;
    // int good_scans;
    
    tx.id = dest;
    tx.len = 8;
    
    // Copy 8 bytes at a time, and then transmit them.
    for(auto i=0; i<len; i++){
        one_byte[0] = '\0'; // empty the dest string. Then use strncat as safe strncpy.
        strncat(one_byte, &data[i*2], 2);
        tx.data[i % 8]=atoi(one_byte);
        if((i % 8) == 7){
            can.transmit(tx);
        }
    }
}

void CAN_send_data_as_asci(int dest, const char *data){
    int len = strlen(data);
    CANMessage tx;
    
    tx.id = dest;
    tx.len = 8;
    
    // Copy 8 bytes at a time, and then transmit them.
    for(auto i=0; i<len; i=i+8){
        // Copy 8 bytes into msg.data
        for( auto j=0; j<8 ; j++){
            if(j+i < len){
                tx.data[j]= data[i+j];
            } else {
                tx.data[j]='~';
                tx.len = j;
                j=8; // End the loop
            }
        }
        // transmitt
        can.transmit(tx);
    }
}

void CAN_transmit_test(){
    CANMessage tx;
    tx.id = 101;
    tx.len = 8;
    tx.data[0] = 'C';
    tx.data[1] = 'a';
    tx.data[2] = 'n';
    tx.data[3] = 'W';
    tx.data[4] = 'o';
    tx.data[5] = 'r';
    tx.data[6] = 'k';
    tx.data[7] = 's';
    can.transmit(tx);
}

void CAN_receive_asci(){
    CANMessage rx;
    
    if(can.receive(rx)) { // message received
        CAN_publish_msg_as_asci(rx);
    }
}

void CAN_receive_hex(){
    CANMessage rx;
    
    if(can.receive(rx)) { // message received
        CAN_publish_msg_as_hex(rx);
    }
}

void CAN_publish_msg_as_hex(CANMessage msg){
    // http://stackoverflow.com/a/30606613
    union IntByte {
      byte b[8];
      int i[2];
    } msgdata;
    char name[13]; // {4:"can@"+ 9:id} because id can be 2^29 with extended.
    // char data[17]; // Max length of data is 8
    
    for( auto i = 0; i<8; i++){
         msgdata.b[i] = msg.data[i];
    }
    // Has been disabled
    // snprintf(data, 17, "%x%x", msgdata.i[1], msgdata.i[0]);
    String data = String::format("%x%x", msgdata.i[0], msgdata.i[1]);
    
    
    // format '%u' expects argument of type 'unsigned int', but argument 3 has
    // ...type 'uint32_t {aka long unsigned int}' [-Wformat=]
    sprintf(name, "CAN@%lu", msg.id);
    
    info(name, data);
}

void CAN_publish_msg_as_asci(CANMessage msg){
    char data[9]; // Max length of data is 8
    for( auto i = 0; i<8; i++){
        data[i] = msg.data[i];
    }
    data[8] = '\0'; // terminate with null.
    
    char name[13]; // {4:"can@"+ 9:id} because id can be 2^29 with extended.
    // format '%u' expects argument of type 'unsigned int', but argument 3 has
    // ...type 'uint32_t {aka long unsigned int}' [-Wformat=]
    sprintf(name, "CAN@%lu", msg.id);
    
    info(name, data);
}

void CAN_check_error_status(){
    switch(can.errorStatus()){
        case CAN_NO_ERROR:
            break;
        case CAN_ERROR_PASSIVE:
            Particle.publish("CAN_ERROR", "Not attempting to transmit messages but still acknowledging messages.");
            break;
        case CAN_BUS_OFF:
            Particle.publish("CAN_ERROR", "Not transmitting or acknowledging messages.");
            break;
        default:
            break;
    }
}
