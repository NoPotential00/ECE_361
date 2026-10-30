#include <stdio.h>
#include "iom361_r4.h"
#include "sensor.h"


int main(void) {
    int rc;
    uint32_t *base = iom361_initialize(3, 2, &rc);
    if (base == NULL || rc != 0) {
        fprintf(stderr, "iom361_initialize failed: %d\n", rc);
        return 1;
    }
    /* A typical soak reading: 95.0 represents 950 degrees C in the kiln. */
    _iom361_set_sensor1(95.0f, 10.0f);

    float temperature, humidity;
    rc = sensor_read(base, &temperature, &humidity);
    if (rc != 0) {
        fprintf(stderr, "sensor_read failed: %d\n", rc);
        return 1;
    }

    printf("Kiln controller: temperature=%.1f C, humidity=%.1f%% RH\n",
           temperature, humidity);
    return 0;
}
