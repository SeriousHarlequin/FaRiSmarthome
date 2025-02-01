#include "espnow.h"

class EspNowSlave : public EspNow {
public:
    uint8_t macMaster[6];

    bool lookForMaster();
};