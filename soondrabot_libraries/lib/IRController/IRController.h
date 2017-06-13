#ifndef IRCONTROLLER_H
#define IRCONTROLLER_H

#include <Arduino.h>
#include <IRremote.h>

class IRController {
    int IRsend_pin;
    IRrecv *irrecvs[5];
    decode_results results;
public:
    IRController(int RECV1_PIN,int RECV2_PIN,int RECV3_PIN,int RECV4_PIN,int RECV5_PIN);
    int receive(int recv_num);
};

#endif
