#include "espnow_send.h"

int espNowAddPeer(const uint8_t *peerMac, const uint8_t channel, const bool encrypt){
    esp_now_peer_info_t peerInfo;
    memcpy(peerInfo.peer_addr, peerMac, 6);
    peerInfo.channel = channel;
    peerInfo.encrypt = encrypt;
    return esp_now_add_peer(&peerInfo);
}