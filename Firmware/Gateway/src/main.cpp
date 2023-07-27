/*
  ┌───────────────────────┐
  │[] ┌──────────┬────┐ []│
  │[] │Espressif │ ◯ │ []│
  │[] │CE        └────┤ []│
  │[] │           ┌──┐│ []│
  │[] │ XXN4      └──┘│ []│
  │[] └───────────────┘ []│
  │[] ▄▄ ─┬──┐      ██  []│
  │[] ▄▄ ─┤  ├   ▄▄ ▄▄  []│
  │[] ▄▄ ─┴──┘   ▄▄ ▄▄  []│
  │[]                   []│
  │[] ▄▄  ┌──┐          []│
  │[] ▄▄  └──┘      ▄▄  []│
  │[] ▄▄  ▄▄▄▄      ▄▄  []│
  │[]                   []│
  │[]   [0]       [0]   []│
  └─────────│USB│─────────┘
*/
#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "env.h"

#include "adapters/aggregator/Aggregator.interface.h"
#include "adapters/communication/Communication.interface.h"
#include "LoRaHandler.h"

LoRaHandler loRaHandlerClass;
WiFiClient client;

ICommunicate communicationInterface;

void onReceiveWrapper(int packetSize)
{
	communicationInterface.onReceive(packetSize);
}

template <typename T>
void sendToAPI(const T &packet)
{
	if (WiFi.status() != WL_CONNECTED)
		return;

	HTTPClient http;
	char apiUrlBuffer[100] = {"\0"};
	char rawDataJSON[sizeof(T) + sizeof(Protocol::HeaderPacket_t) + 50] = {"\0"};
	uint8_t packetBuffer[sizeof(T)] = {"\0"};
	uint8_t headerBuffer[sizeof(Protocol::HeaderPacket_t)] = {"\0"};
	int rdjOffset = 0;
	snprintf(apiUrlBuffer, sizeof(apiUrlBuffer), apiUrl, (unsigned)header.deviceSerailNumber);
	rdjOffset += snprintf(rawDataJSON, sizeof(rawDataJSON), "{\"hea\":\"");

	Protocol::serializePacket(&header, headerBuffer);
	for (int i = 0; i < sizeof(Protocol::HeaderPacket_t); i++)
	{
		int ret = snprintf(rawDataJSON + rdjOffset, sizeof(rawDataJSON) - rdjOffset, "%02X", headerBuffer[i]);
		assert(ret == 2);
		rdjOffset += ret;
	}

	rdjOffset += snprintf(rawDataJSON + rdjOffset, sizeof(rawDataJSON) - rdjOffset, "\", \"rda\":\"");

	Protocol::serializePacket(&packet, packetBuffer);
	for (int i = 0; i < sizeof(T); i++)
	{
		int ret = snprintf(rawDataJSON + rdjOffset, sizeof(rawDataJSON) - rdjOffset, "%02X", packetBuffer[i]);
		assert(ret == 2);
		rdjOffset += ret;
	}
	rdjOffset += snprintf(rawDataJSON + rdjOffset, sizeof(rawDataJSON) - rdjOffset, "\"}");

	Serial.print("apiUrlBuffer: ");
	Serial.println(apiUrlBuffer);
	Serial.println();
	Serial.print("rawDataJSON: ");
	Serial.println(rawDataJSON);

	http.begin(client, apiUrlBuffer);
	http.addHeader("Content-Type", "application/json");
	int httpResponseCode = http.POST(rawDataJSON);
	Serial.println(httpResponseCode);
	http.end();
}
void handlePacket()
{ // TODO BLOCK INTERRUPTS ON DIO0
	Protocol::HeartbeatPacket headerIn;
	Packet packetIn;

	bool packet = ICommunicate::getPacket(&headerIn, &packetIn)
	if (packet){
		switch (headerIn.packetType)
		{
			case Protocol::STATUS_PACKET_ID:
				sendToAPI(packetIn);
				Serial.println("Sent packet to backend!");
				break;
			case Protocol::HEARTBEAT_PACKET_ID:
				sendToAPI(packetIn);
				Serial.println("Sent packet to backend!");
				break;
			case Protocol::TRACEROUTE_STATUS_PACKET_ID:
				sendToAPI(packetIn);
				Serial.println("Sent packet to backend!");
				break;
			case Protocol::TRACEROUTE_HEARTBEAT_PACKET_ID:
				sendToAPI(packetIn);
				Serial.println("Sent packet to backend!");
				break;
			default:
				Serial.print("Unknown packet type: ");
				Serial.println(header.packetType);
				break;
			}
		}
	LoRa.flush();
}
void setup()
{
	Serial.begin(115200);
	while (!Serial)
		;
	Serial.print("Attempting to connect to SSID: ");
	Serial.println(env::SSID);

	WiFi.begin(env::SSID, env::PASSWORD);
	while (WiFi.status() != WL_CONNECTED)
	{
		delay(500);
		Serial.print(".");
	}
	WiFi.setAutoReconnect(true);
	WiFi.persistent(true);

	Serial.println("");
	Serial.print("Connected to WiFi network with IP Address: ");
	Serial.println(WiFi.localIP());

	loRaHandlerClass.setupModule();
	LoRa.onReceive(onReceiveWrapper);
	LoRa.receive();
}

void loop()
{
	Serial.println("Waiting");

	if (packetReceived)
	{
		handlePacket();
		LoRa.receive();
	}

	Serial.flush();
	delay(1000);
}