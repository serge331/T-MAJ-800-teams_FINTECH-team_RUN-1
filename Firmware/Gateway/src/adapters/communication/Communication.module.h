#ifndef COMMUNICATION_MODULE_H
#define COMMUNICATION_MODULE_H

/**
 * This module offer the possibility to choose
 * the implementation of the communication adapter
 */

#define COMMUNICATION_ADAPTER_LORA 1
#define COMMUNICATION_ADAPTER_BLE 2
#define COMMUNICATION_ADAPTER_MOCK 3

#define COMMUNICATOR_ADAPTER COMMUNICATION_ADAPTER_MOCK

#endif /* COMMUNICATION_MODULE_H */