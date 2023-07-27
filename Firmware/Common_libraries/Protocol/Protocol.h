#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdint.h>

#include <cstring>
#include <memory>

namespace Protocol
{
    const uint8_t MAX_TTL = 10;
    const uint8_t MAX_JUMP_LIMIT = MAX_TTL;

    typedef struct
    {
        uint8_t packetType = 0;
        uint8_t TTL = MAX_TTL;
        uint16_t deviceSerailNumber = 0;
        uint16_t checksum = 0;
        uint16_t bodySize = 0;
    } HeaderPacket_t;

    const uint16_t STATUS_PACKET_ID = 1;
    typedef struct
    {
        uint16_t deviceStatus = 0;
    } StatusPacket_t;

    const uint16_t HEARTBEAT_PACKET_ID = 2;
    typedef struct
    {
        uint16_t beatCount = 0;
    } HeartbeatPacket_t;

    const uint16_t TRACEROUTE_STATUS_PACKET_ID = 3;
    typedef struct
    {
        uint16_t deviceStatus = 0;
        uint8_t jumpCounter = 0;
        uint16_t jumpList[MAX_JUMP_LIMIT] = {0};
    } TracerouteStatusPacket_t;

    const uint16_t TRACEROUTE_HEARTBEAT_PACKET_ID = 4;
    typedef struct
    {
        uint16_t beatCount = 0;
        uint8_t jumpCounter = 0;
        uint16_t jumpList[MAX_JUMP_LIMIT] = {0};
    } TracerouteHeartbeatPacket_t;

    const uint16_t DATA_TRANSFER_PACKET = 4;
    typedef struct
    {
        uint16_t xG = 0; // As signed Q11.4
        uint16_t yG = 0;
        uint16_t zG = 0;

        uint16_t roll = 0; // As signed Q11.4
        uint16_t pitch = 0;
        uint16_t yaw = 0;

        uint16_t latitude = 0; // As signed Q8.7
        uint16_t longitude = 0;

        uint64_t timestamp = 0; // As 64bit counter

        uint16_t ppm_CO2 = 0; // As unsigned Q13.3
        uint16_t ppm_dust = 0;

        uint8_t humidity = 0;    // As 8 bit integer
        uint8_t temperature = 0; // As 8 bit integer
        uint8_t lightLevels = 0; // As 8 bit integer
        uint8_t speed = 0;       // As 8 bit integer

        uint8_t bitfeild_1 = 0; // 8bit as bit feild to stor bools
                                // 0000 0001 braking
    } DataTransferPacket;

    template <typename T>
    void serializePacket(const T *packet, uint8_t *out)
    {
        memcpy(out, packet, sizeof(T));
    }

    template <typename T>
    void deSerializePacket(T *packet, const uint8_t *in)
    {
        memcpy(packet, in, sizeof(T));
    }

    void printPacket(const HeaderPacket_t &packet);
    void printPacket(const StatusPacket_t &packet);
    void printPacket(const HeartbeatPacket_t &packet);
    void printPacket(const TracerouteStatusPacket_t &packet);
    void printPacket(const TracerouteHeartbeatPacket_t &packet);

} // namespace Protocol

#endif /* PROTOCOL_H */