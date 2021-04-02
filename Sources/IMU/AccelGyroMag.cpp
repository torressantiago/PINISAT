@ -0,0 +1,43 @@
/** @file AccelGyroMag.cpp
 * 
 * @brief
 * Read accelerometer, gyroscope and magnetometer values from
 * inertial measurement unit: MPU9250 or LSM9DS1 over SPI on Raspberry Pi 
 * and shares them with socket.
 *
 * @author Maria Estella Yammine      
 * 
 * @version 1.0
 * 
 */

#include "Common/MPU9250.h"
#include "Navio2/LSM9DS1.h"
#include "Common/Util.h"
#include <unistd.h>
#include <string>
#include <memory>

/**
 * \brief This function allows you to choose which of the two sensors : 
 * MPU or LSM you wish to use
 * \param[out] ptr the pointer to the chosen measurement unit
 * \param[in] name the name of the sensor you want  
 */
std::unique_ptr <InertialSensor> getSensor( std::string name)
{
    if (name == "mpu") {
        printf("Selected: MPU9250\n");
        auto ptr = std::unique_ptr <InertialSensor>{ new MPU9250() };
        return ptr;
    }
    else if (name == "lsm") {
        printf("Selected: LSM9DS1\n");
        auto ptr = std::unique_ptr <InertialSensor>{ new LSM9DS1() };
        return ptr;
    }
    else {
        return NULL;
    }
}
