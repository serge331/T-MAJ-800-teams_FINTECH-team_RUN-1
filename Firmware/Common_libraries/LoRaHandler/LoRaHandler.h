#ifndef LORAHANDLER_H
#define LORAHANDLER_H

#include <stdint.h>

#include <Wire.h>

#include "LoRa.h"
#include "Protocol/Protocol.h"


/**
 * This utilise the LoRa library Wire singleton /!\ act in consequences !
*/
class LoRaHandler {
private:
    const int SCK = 3;
    const int MISO = 7;
    const int MOSI = 6;
    const int SS = 2;
    const int RST = 0;
    const int DIO0 = 1;

    // LoRa parameters
    const double FREQUENCY = 433E6;
    const double BANDWIDTH = 125E3;
    const int SPREADING_FACTOR = 7;
    const int CODING_RATE_DENOM = 8;
    const int PREAMBLE_LENGTH = 8;

public:
    void setupModule();

    size_t receiveHeader(Protocol::HeaderPacket_t *header);

    template<typename T>
    size_t sendPacket(const T *packet, size_t packetSize) // TODO Error handling
    {
        uint8_t buffer[packetSize];
        Protocol::serializePacket(packet, buffer);
        LoRa.write(buffer, packetSize);
        return packetSize;
    }

    template<typename T>
    size_t receivePacket(T *packet, size_t packetSize) // TODO Error handling
    {
        uint8_t buffer[packetSize];
        uint8_t index = 0;
        while (LoRa.available() && index < packetSize)
        {
            buffer[index] = (uint8_t)LoRa.read();
            index++;
        }
        Protocol::deSerializePacket(packet, buffer);
        return packetSize;
    }
};

#endif /* LORAHANDLER_H */