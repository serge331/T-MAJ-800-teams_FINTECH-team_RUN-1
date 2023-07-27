/*
                        ┌───────────────────────┐
                        │[] ┌──────────┬────┐ []│ GND   ==> Ra-02 GND
  Ra-02 3.3v <== 3.3v   │[] │Espressif │ ◯  │ []│ GPIO0 ==> Ra-02 RST
                        │[] │CE        └────┤ []│ GPIO1 ==> Ra-02 DIO0
                        │[] │           ┌──┐│ []│ GPIO2 ==> Ra-02 NSS
                        │[] │ XXN4      └──┘│ []│ GPIO3 ==> Ra-02 SCK
                        │[] └───────────────┘ []│
                        │[] ▄▄ ─┬──┐      ██  []│
  Ra-02 MOSI <== GPIO6  │[] ▄▄ ─┤  ├   ▄▄ ▄▄  []│
  Ra-02 MISO <== GPIO7  │[] ▄▄ ─┴──┘   ▄▄ ▄▄  []│
                        │[]                   []│
     I2C SCL <== GPIO8  │[] ▄▄  ┌──┐          []│
     I2C SDA <== GPIO9  │[] ▄▄  └──┘      ▄▄  []│
                        │[] ▄▄  ▄▄▄▄      ▄▄  []│
                        │[]                   []│
                        │[]   [0]       [0]   []│
                        └─────────│USB│─────────┘
*/
#include <Arduino.h>

#include "Protocol/Protocol.h"
#include "LoRaHandler/LoRaHandler.h"
#include "env.h"

LoRaHandler loRaHandlerClass;
unsigned long lastSent = 0;

Protocol::HeaderPacket_t header;
Protocol::StatusPacket_t statusPacket;
Protocol::HeartbeatPacket_t heartbeatPacket;
Protocol::TracerouteStatusPacket_t trStatusPacket;
Protocol::TracerouteHeartbeatPacket_t trHeartbeatPacket;

bool triggered = false;

void ISRonTriggered()
{
  triggered = true;
}

void setup()
{
  Serial.begin(115200);
  Wire.begin(9, 8);
  while (!Serial)
    ;

  loRaHandlerClass.setupModule();
}

template <typename T>
void sendPacket(Protocol::HeaderPacket_t &header, T &packet)
{
  LoRa.beginPacket();
  loRaHandlerClass.sendPacket(&header, sizeof(Protocol::HeaderPacket_t));
  loRaHandlerClass.sendPacket(&packet, header.bodySize);
  LoRa.endPacket();
  Serial.println("Packet sent");
}

void sendStatusPacket(Protocol::HeaderPacket_t &header)
{
  Protocol::StatusPacket_t packet;
  packet.deviceStatus = 0;
  header.bodySize = sizeof(Protocol::StatusPacket_t);

  sendPacket(header, packet);
}

void loop()
{
  Serial.println("Waiting");

  if ((millis() - lastSent) >= 20000)
  {
    Serial.println("Broadcast packet");
    lastSent = millis();
    Protocol::HeaderPacket_t header;
    header.packetType = Protocol::STATUS_PACKET_ID;
    header.checksum = 0;
    header.bodySize = 0;
    header.deviceSerailNumber = env::DEVICE_SERIAL_NUMBER;
    sendStatusPacket(header);
  }

  Serial.flush();
  delay(1000);
}