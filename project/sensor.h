#ifndef SENSOR_H
#define SENSOR_H
#include <stdint.h>
#include <time.h>
/* Read and convert the kiln's temperature and humidity sensor values. */

typedef struct {
    time_t timestamp; /* Seconds since the Unix epoch. */
    float temp_c;    /* Temperature in degrees Celsius (iom361 scale). */
    float rh_pct;    /* Relative humidity in percent. */
} reading_t;

int sensor_read(uint32_t *base, float *temp_c, float *rh_pct);

#endif
