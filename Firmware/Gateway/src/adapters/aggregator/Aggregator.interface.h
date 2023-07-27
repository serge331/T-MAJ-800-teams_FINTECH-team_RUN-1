#ifndef AGGREGATOR_INTERFACE_H
#define AGGREGATOR_INTERFACE_H

/* ---------- Module protection ---------- */
#include "Aggregator.module.h"
#ifndef AGGREGATOR_ADAPTER
static_assert(false, "Error: AGGREGATOR_ADAPTER is not defined !");
#endif
/* ---------- Module protection ---------- */

#include <stdint.h>

/**
 * Struct used as in & out parameter to aggregate data
 * @see Documentation for more information on data types.
 */
struct DataAggregate
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
};

class IAggregateData
{
private:
public:
    IAggregateData() = default;
    ~IAggregateData() = default;

    virtual void init();
    virtual void aggregate(DataAggregate &in);
};

#endif /* AGGREGATOR_INTERFACE_H */