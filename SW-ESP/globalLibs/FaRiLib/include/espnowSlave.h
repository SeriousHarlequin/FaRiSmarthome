#ifndef ESPNOW_SLAVE_HEADER_GUARD
#define ESPNOW_SLAVE_HEADER_GUARD

#include "espnow.h"

class EspNowSlave : public EspNow {
public:
    uint8_t macMaster[6];

    bool lookForMaster();
};

extern EspNowSlave espnowSlave;

#endif