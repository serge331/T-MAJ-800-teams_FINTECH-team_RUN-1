#include "Communication.interface.h"

#if COMMUNICATOR_ADAPTER == COMMUNICATION_ADAPTER_MOCK

#include <iostream>

#include "LoRaHandler.h"

extern LoRaHandler loRaHandlerClass;

void ICommunicate::init()
{
}

void ICommunicate::onReceive(int packetSize)
{
    if (packetSize < sizeof(Protocol::HeaderPacket))
    { // TODO Handle error
        std::cout << "Not enough data received for the header!" << std::endl;
        return;
    }
    Protocol::HeaderPacket header;

    loRaHandlerClass.receiveHeader(&header);

    if (packetSize < sizeof(Protocol::HeaderPacket) + header.bodySize)
    { // TODO Handle error
        std::cout << "Not enough data received for the full packet!" << std::endl;
        return;
    }
    switch (header.packetType)
    {
    case Protocol::STATUS_PACKET_ID:
        Protocol::StatusPacket statusPacket;
        loRaHandlerClass.receivePacket(&statusPacket, header.bodySize);
        Protocol::printPacket(statusPacket);
        if (receivedCount < RECEIVED_PACKET_BUFFER_CAPACITY)
        {
            receivedCount++;
        }
        receivedHeaderBuffer[receivedEnd] = header;
        receivedPacketBuffer[receivedEnd] = statusPacket
        receivedEnd++;
        receivedEnd = receivedEnd % RECEIVED_PACKET_BUFFER_CAPACITY;
        // TODO add packet to buffers
        break;
    case Protocol::HEARTBEAT_PACKET_ID:
        Protocol::HeartbeatPacket heartbeatPacket;
        loRaHandlerClass.receivePacket(&heartbeatPacket, header.bodySize);
        Protocol::printPacket(heartbeatPacket);
        if (receivedCount < RECEIVED_PACKET_BUFFER_CAPACITY)
        {
            receivedCount++;
        }
        receivedHeaderBuffer[receivedEnd] = header;
        receivedPacketBuffer[receivedEnd] = heartbeatPacket
        receivedEnd++;
        receivedEnd = receivedEnd % RECEIVED_PACKET_BUFFER_CAPACITY;
        // TODO add packet to buffers
        break;
    case Protocol::TRACEROUTE_STATUS_PACKET_ID:
        Protocol::TracerouteStatusPacket trStatusPacket;
        loRaHandlerClass.receivePacket(&trStatusPacket, header.bodySize);
        Protocol::printPacket(trStatusPacket);
        if (receivedCount < RECEIVED_PACKET_BUFFER_CAPACITY)
        {
            receivedCount++;
        }
        receivedHeaderBuffer[receivedEnd] = header;
        receivedPacketBuffer[receivedEnd] = statusPacket
        receivedEnd++;
        receivedEnd = receivedEnd % RECEIVED_PACKET_BUFFER_CAPACITY;
        // TODO add packet to buffers
        break;
    case Protocol::TRACEROUTE_HEARTBEAT_PACKET_ID:
        Protocol::TracerouteHeartbeatPacket trHeartbeatPacket;
        loRaHandlerClass.receivePacket(&trHeartbeatPacket, header.bodySize);
        Protocol::printPacket(trHeartbeatPacket);
        if (receivedCount < RECEIVED_PACKET_BUFFER_CAPACITY)
        {
            receivedCount++;
        }
        receivedHeaderBuffer[receivedEnd] = header;
        receivedPacketBuffer[receivedEnd] = statusPacket
        receivedEnd++;
        receivedEnd = receivedEnd % RECEIVED_PACKET_BUFFER_CAPACITY;
        // TODO add packet to buffers
        break;
    default:
        Serial.print("Unknown packet type: ");
        Serial.println(header.packetType);
        return;
    }
}

bool ICommunicate::getPacket(Protocol::HeartbeatPacket &headerIn, Packet &packetIn)
{
    headerIn = receivedHeaderBuffer[receivedStart];
    packetIn = receivedPacketBuffer[receivedStart];
    receivedStart++;
    receivedStart = receivedStart % RECEIVED_PACKET_BUFFER_CAPACITY;
    receivedCount--;

    return false;
}
bool ICommunicate::sendPacket(Protocol::HeartbeatPacket const &header, Packet const &packet)
{
    return false;
}

#endif