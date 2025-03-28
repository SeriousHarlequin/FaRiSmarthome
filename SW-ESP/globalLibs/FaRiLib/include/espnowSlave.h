#ifndef ESPNOW_SLAVE_HEADER_GUARD
#define ESPNOW_SLAVE_HEADER_GUARD

#include "espnow.h"

class EspNowSlave : public EspNow {
public:
    uint8_t macMaster[6];

    bool lookForMaster();
    bool addMaster(const uint8_t*);
};

extern EspNowSlave espnowSlave;

#endif