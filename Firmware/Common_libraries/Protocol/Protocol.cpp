#include "Protocol.h"

#include <stdint.h>

#include <cstring>
#include <iostream>

namespace Protocol
{

    template <typename T>
    size_t readBufferTo(const uint8_t *buffer, T *out)
    {
        for (size_t i = 0; i < sizeof(T); i++)
        {
            *out |= buffer[i] << (8 * i);
        }
        std::cout << "read(" << sizeof(T) << "): " << unsigned(*out) << std::endl;

        return sizeof(T);
    }

    template <>
    void deSerializePacket<TracerouteStatusPacket_t>(TracerouteStatusPacket_t *packet, const uint8_t *in)
    {
        constexpr size_t packetFixSize = sizeof(TracerouteStatusPacket_t) - (sizeof(TracerouteStatusPacket_t::jumpList[0]) * MAX_JUMP_LIMIT);
        size_t index = packetFixSize;
        memcpy(packet, in, sizeof(TracerouteStatusPacket_t));

        for (size_t i = 0; i < packet->jumpCounter; i++)
        {
            index += readBufferTo(in + index, &packet->jumpList[i]);
        }
    }

    template <>
    void deSerializePacket<TracerouteHeartbeatPacket_t>(TracerouteHeartbeatPacket_t *packet, const uint8_t *in)
    {
        constexpr size_t packetFixSize = sizeof(TracerouteHeartbeatPacket_t) - (sizeof(TracerouteHeartbeatPacket_t::jumpList[0]) * MAX_JUMP_LIMIT);
        size_t index = packetFixSize;
        memcpy(packet, in, sizeof(TracerouteHeartbeatPacket_t));

        for (size_t i = 0; i < packet->jumpCounter; i++)
        {
            index += readBufferTo(in + index, &packet->jumpList[i]);
        }
    }

    void printPacket(const HeaderPacket_t &packet)
    {
        Serial.print("{\n    packetType: ");
        Serial.print(unsigned(packet.packetType));
        Serial.print("\n    TTL: ");
        Serial.print(unsigned(packet.TTL));
        Serial.print("\n    deviceSerailNumber: ");
        Serial.print(unsigned(packet.deviceSerailNumber));
        Serial.print("\n    checksum: ");
        Serial.print(unsigned(packet.checksum));
        Serial.print("\n    bodySize: ");
        Serial.print(unsigned(packet.bodySize));
        Serial.println("\n}");
        Serial.flush();
    }

    void printPacket(const StatusPacket_t &packet)
    {
        Serial.println("StatusPacket_t");

        Serial.print("{\n    deviceStatus: ");
        Serial.print(unsigned(packet.deviceStatus));
        Serial.println("\n}");
        Serial.flush();
    }

    void printPacket(const HeartbeatPacket_t &packet)
    {
        Serial.println("HeartbeatPacket_t");

        Serial.println("{\n    nothing lol\n}");
        Serial.flush();
    }

    void printPacket(const TracerouteStatusPacket_t &packet)
    {
        Serial.println("TracerouteStatusPacket_t");
        Serial.flush();

        Serial.print("{\n    deviceStatus: ");
        Serial.print(unsigned(packet.deviceStatus));
        Serial.print(",\n    jumpCounter: ");
        Serial.print(unsigned(packet.jumpCounter));
        Serial.print(",\n    [ ");
        for (size_t i = 0; i < packet.jumpCounter; i++)
        {
            Serial.print(unsigned(packet.jumpList[i]));
            Serial.print(", ");
        }
        Serial.println("]\n}");
        Serial.flush();
    }

    void printPacket(const TracerouteHeartbeatPacket_t &packet)
    {
        Serial.println("TracerouteHeartbeatPacket_t");

        Serial.print("{\n    jumpCounter: ");
        Serial.print(unsigned(packet.jumpCounter));
        Serial.print(",\n    [ ");
        for (size_t i = 0; i < packet.jumpCounter; i++)
        {
            Serial.print(unsigned(packet.jumpList[i]));
            Serial.print(", ");
        }
        Serial.println("]\n}");
        Serial.flush();
    }

} // namespace Protocol