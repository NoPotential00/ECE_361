#include "sensor.h"
#include <stdint.h>
#include <math.h>
#include "iom361_r4.h"


int sensor_read(uint32_t *base, float *temp_c, float *rh_pct) {
    // Implementation for reading sensor values
    int rc;
    
    uint32_t raw_temp = iom361_readReg(base, TEMP_REG, &rc);
    if (rc != 0) {
        return rc;
    }
    
    uint32_t raw_humidity = iom361_readReg(base, HUMID_REG, &rc);
    if (rc != 0) {
        return rc;
    }

    float temperature = raw_temp / 1048576.0f * 200.0f - 50.0f;
    float humidity = raw_humidity / 1048576.0f * 100.0f;
    
    *temp_c = roundf(temperature * 10.0f) / 10.0f;
    *rh_pct = roundf(humidity * 10.0f) / 10.0f;
    return 0;
}
