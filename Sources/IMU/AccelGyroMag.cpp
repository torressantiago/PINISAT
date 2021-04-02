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
 * \brief This function creates the Sensor object chosen (LSM)
 * \param[out] ptr the pointer to the created object
 */
std::unique_ptr <InertialSensor> get_inertial_sensor() {
    auto ptr = std::unique_ptr <InertialSensor>{ new LSM9DS1() };
    return ptr;  
}

/**
 * \brief This function allows you to read the values of 
 * the accelerometer, the gyroscope and the magnetometer 
 * \param[out] obj the pointer to the tabs 
 * \param[in] tabaccel tab of floats with the values of the acceleromter in the 3 directions
 * \param[in] tabgyr tab of floats with the values of the gyrometer in the 3 directions
 * \param[in] tabmag tab of floats with the values of the magnetometer in the 3 directions
 */

void read_fromsens(float *tabaccel, float *tabgyr, float *tabmag){
    auto sensor = get_inertial_sensor();
    sensor->initialize();
//-------------------------------------------------------------------------

    while(1) {
        sensor->update();
        sensor->read_accelerometer(tabaccel,tabaccel+1,tabaccel+2);
        sensor->read_gyroscope(tabgyr,tabgyr+1,tabgyr+2);
        sensor->read_magnetometer(tabmag,tabmag+1,tabmag+2);

       usleep(50);
       printf("%f", *tabaccel);
    }
}

//======================================================================================================

int main(int argc, char *argv[]) {

    if (check_apm()) {
        return 1;
    }

    auto sensor = get_inertial_sensor();
    auto *sensor_ptr = &sensor;

    if (!sensor->probe()) {
        printf("Sensor not enabled\n");
        return EXIT_FAILURE;
    }

    sensor->initialize();

    float tableauaccel[3];
    float tableaumag[3];
    float tableaugyr[3];
    read_fromsens(tableauaccel, tableaumag, tableaugyr);
}