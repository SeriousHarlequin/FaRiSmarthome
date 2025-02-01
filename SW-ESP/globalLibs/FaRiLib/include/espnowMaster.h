#include "espnow.h"
#include <vector>

class EspNowMaster : public EspNow {
public:
    std::vector<std::array<uint8_t, 6>> peers;

    bool addPeer(const uint8_t * mac);
};