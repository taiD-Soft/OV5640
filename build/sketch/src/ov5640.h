#line 1 "/home/taivv/Documents/TESTOV5640/src/ov5640.h"

#ifndef __OV5640_H__
#define __OV5640_H__

#include "sensor.h"

/**
 * @brief Detect sensor pid
 *
 * @param slv_addr SCCB address
 * @param id Detection result
 * @return
 *     0:       Can't detect this sensor
 *     Nonzero: This sensor has been detected
 */
int ov5640_detect(int slv_addr, sensor_id_t *id);

/**
 * @brief initialize sensor function pointers
 *
 * @param sensor pointer of sensor
 * @return
 *      Always 0
 */
int ov5640_init(sensor_t *sensor);

#endif // __OV5640_H__
