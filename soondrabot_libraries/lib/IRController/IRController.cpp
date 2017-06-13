#include "IRController.h"

IRController::IRController(int RECV1_PIN,int RECV2_PIN,int RECV3_PIN,int RECV4_PIN,int RECV5_PIN) {
    irrecvs[0] = new IRrecv(RECV1_PIN);
    irrecvs[1] = new IRrecv(RECV2_PIN);
    irrecvs[2] = new IRrecv(RECV3_PIN);
    irrecvs[3] = new IRrecv(RECV4_PIN);
    irrecvs[4] = new IRrecv(RECV5_PIN);
    for (int i = 0; i < 5; i++)
        irrecvs[i]->enableIRIn();
}

int IRController::receive(int recv_num) {
    int did_receive;
    if (irrecvs[recv_num]->decode(&results))
    {
        did_receive = 1;
        irrecvs[recv_num]->resume();
    } else {
        did_receive = 0;
    }

    return did_receive;
}
