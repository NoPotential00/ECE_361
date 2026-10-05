#include "status.h"
#include "bits.h"

enum {
    HEAT_POS = 0,
    HEAT_WIDTH = 1,
    COOL_POS = 1,
    COOL_WIDTH = 1,
    FAN_POS = 2,
    FAN_WIDTH = 1,
    FAULT_POS = 3,
    FAULT_WIDTH = 1,
    MODE_POS = 4,
    MODE_WIDTH = 3,
    SETPOINT_POS = 8,
    SETPOINT_WIDTH = 8
};

status_t status_unpack(uint16_t word)
{
    status_t status = {0};

    status.heat = get_field(word, HEAT_POS, HEAT_WIDTH);
    status.cool = get_field(word, COOL_POS, COOL_WIDTH);
    status.fan = get_field(word, FAN_POS, FAN_WIDTH);
    status.fault = get_field(word, FAULT_POS, FAULT_WIDTH);

    status.mode = get_field(word, MODE_POS, MODE_WIDTH);
    if (status.mode > 4u)
    {
        status.mode = 0u;
    }

    uint32_t setpoint_raw = get_field(word, SETPOINT_POS, SETPOINT_WIDTH);
    status.setpoint = (int8_t)sign_extend(setpoint_raw, SETPOINT_WIDTH);

    return status;
}
