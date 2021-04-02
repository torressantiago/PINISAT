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
 * \param[in] sensor_name the name of the sensor you choose  
 */
std::unique_ptr <InertialSensor> get_inertial_sensor( std::string sensor_name)
{
    if (sensor_name == "mpu") {
        printf("Selected: MPU9250\n");
        auto ptr = std::unique_ptr <InertialSensor>{ new MPU9250() };
        return ptr;
    }
    else if (sensor_name == "lsm") {
        printf("Selected: LSM9DS1\n");
        auto ptr = std::unique_ptr <InertialSensor>{ new LSM9DS1() };
        return ptr;
    }
    else {
        return NULL;
    }
}

/**
 * \brief This function creates the object Sensor 
 */
std::string get_sensor_name(int argc, char *argv[])
{
    if (get_navio_version() == NAVIO2) {

        if (argc < 2) {
            printf("Enter parameter\n");
            return std::string();
        }

        // prevent the error message
        opterr = 0;
        int parameter;

        while ((parameter = getopt(argc, argv, "i:h")) != -1) {
            switch (parameter) {
            case 'i': return optarg;
            case 'h': print_help(); return "-1";
            case '?': printf("Wrong parameter.\n");
                      print_help();
                      return std::string();
            }
        }

    } else { //sensor on NAVIO+

        return "mpu";
    }

/**
 * \brief This function allows you to read the values of the accelerometer,
 * the gyroscope and the magnetometer 
 * \param[out] obj the pointer to the tabs 
 * \param[in] tabaccel tab of floats with the values of the acceleromter in the 3 directions
 * \param[in] tabgyr tab of floats with the values of the gyrometer in the 3 directions
 * \param[in] tabmag tab of floats with the values of the magnetometer in the 3 directions
 */
void read(float &tabaccel, float &tabgyr, float &tabmag, auto &obj){
  obj->read_accelerometer(tabaccel,tabaccel+1,tabaccel+2);
  obj->read_gyroscope(tabgyr,tabgyr+1,tabgyr+2);
  obj->read_magnetometer(tabmag,tabmag+1,tabmag+2);
}

//======================================================================================================

int main(int argc, char *argv[]) {

    if (check_apm()) {
        return 1;
    }

    auto sensor_name = get_sensor_name(argc, argv);
    if (sensor_name.empty())
        return EXIT_FAILURE;

    auto sensor = get_inertial_sensor(sensor_name);

    if (!sensor) {
        printf("Wrong sensor name. Select: mpu or lsm\n");
        return EXIT_FAILURE;
    }

    if (!sensor->probe()) {
        printf("Sensor not enabled\n");
        return EXIT_FAILURE;
    }
    sensor->initialize();

    float tableauaccel[3];
    float tabbleaumag[3];
    float tableaugyr[3];
    auto sensor = getSensor(sensor_name);

    while(1){
        sensor->update();
        sensor->read(&tableauaccel, &tabelaumag, &tableaugyr, &sensor);

        usleep(500000);
    }
}

    
