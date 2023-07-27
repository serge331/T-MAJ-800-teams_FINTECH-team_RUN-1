#include <stdint.h>

#include <Wire.h>

#include "LoRa.h"
#include "LoRaHandler/LoRaHandler.h"
#include "Protocol/Protocol.h"

void LoRaHandler::setupModule()
{
    LoRa.setPins(SS, RST, DIO0);
    if (!LoRa.begin(FREQUENCY)) {
        Serial.println("Starting LoRa failed!");
        while (1);
    }
    LoRa.setSignalBandwidth(BANDWIDTH);
    LoRa.setSpreadingFactor(SPREADING_FACTOR);
    LoRa.setCodingRate4(CODING_RATE_DENOM);
    
}

// TODO error handling
size_t LoRaHandler::receiveHeader(Protocol::HeaderPacket_t *header)
{
    uint8_t buffer[sizeof(Protocol::HeaderPacket_t)];
    receivePacket(header, sizeof(Protocol::HeaderPacket_t));
    return sizeof(Protocol::HeaderPacket_t);
}