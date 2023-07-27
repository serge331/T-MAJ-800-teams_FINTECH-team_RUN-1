#ifndef COMMUNICATION_INTERFACE_H
#define COMMUNICATION_INTERFACE_H

#include "Communication.module.h"

#ifndef COMMUNICATOR_ADAPTER
static_assert(false, "Error: COMMUNICATOR_ADAPTER is not defined !");
#endif

#include <variant>

#include "Protocol/Protocol.h"

typedef std::variant<
    Protocol::StatusPacket,
    Protocol::HeartbeatPacket,
    Protocol::TracerouteStatusPacket,
    Protocol::TracerouteHeartbeatPacket,
    Protocol::DataTransferPacket>
    Packet;

class ICommunicate
{
private:
    static const uint16_t RECEIVED_PACKET_BUFFER_CAPACITY = 5;
    std::array<Packet, RECEIVED_PACKET_BUFFER_CAPACITY> receivedPacketBuffer;
    std::array<Protocol::HeartbeatPacket, RECEIVED_PACKET_BUFFER_CAPACITY> receivedHeaderBuffer;
    uint16_t receivedStart = 0;
    uint16_t receivedEnd = 0;
    uint16_t receivedCount = 0;

    static const uint16_t SEND_PACKET_BUFFER_CAPACITY = 2;
    std::array<Packet, SEND_PACKET_BUFFER_CAPACITY> sendPacketBuffer;
    std::array<Protocol::HeartbeatPacket, SEND_PACKET_BUFFER_CAPACITY> sendHeaderBuffer;
    uint16_t sendStart = 0;
    uint16_t sendEnd = 0;
    uint16_t sendCount = 0;



public:
    ICommunicate() = default;
    ~ICommunicate() = default;

    void init();
    void onReceive(int packetSize);
    bool getPacket(Protocol::HeartbeatPacket &headerIn, Packet &packetIn);
    bool sendPacket(Protocol::HeartbeatPacket const &header, Packet const &packet);
};

#endif /* COMMUNICATION_INTERFACE_H */