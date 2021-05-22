/** @file sat.cpp
 * 
 * @brief
 * Read accelerometer, gyroscope, magnetometer and GPS variables from connected sensors
 * to send via sockets to a distant server machine.
 *
 * @author Santiago Torres B. and Maria Estella Yammine      
 * 
 * @version 1.0
 * 
 */
#include "Common/MPU9250.h"
#include "Navio2/LSM9DS1.h"
#include <unistd.h>
#include <string>
#include <memory>
#include <Common/Ublox.h>
#include <Common/Util.h>
#include "Common/sockets.h"

#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#define ADDRESS "192.168.4.1"
#define PORT 8080

/**
 * \brief Create I2C bus and configure slave with given address
 * \param[out] file returns file descriptor return from reading /dev/i2c-1
 * \param[in] addr inputs the slave's address
 */
int create_i2c(int addr){
    // Create I2C bus
	int file;
	char *bus = "/dev/i2c-1";
	if ((file = open(bus, O_RDWR)) < 0) 
	{
		printf("Failed to open the bus. \n");
		exit(1);
	}
	// Get I2C device, MCP9808 I2C address is 0x18(24)
	ioctl(file, I2C_SLAVE, 0x18);
    return file;
}

/**
 * \brief // Write to slave and output temperature in celsius
 * \param[out] cTemp returns the temperature in celsius degrees
 * \param[in] file the file descriptor is given as an input.
 */
float returntemp(int file){
    // Select configuration register(0x01)
	// Continuous conversion mode, Power-up default(0x00, 0x00)
	char config[3] = {0};
	config[0] = 0x01;
	config[1] = 0x00;
	config[2] = 0x00;
	write(file, config, 3);
	// Select resolution rgister(0x08)
	// Resolution = +0.0625 / C(0x03)
	config[0] = 0x08;
	config[1] = 0x03;
	write(file, config, 2);
	sleep(1);

	// Read 2 bytes of data from register(0x05)
	// temp msb, temp lsb
	char reg[1] = {0x05};
	write(file, reg, 1);
	char data[2] = {0};
	if(read(file, data, 2) != 2)
	{
		printf("Error : Input/Output error \n");
	}
	else
	{
		// Convert the data to 13-bits
		int temp = ((data[0] & 0x1F) * 256 + data[1]);
		if(temp > 4095)
		{
			temp -= 8192;
		}
		float cTemp = temp * 0.0625;
        return cTemp;
	}
}

/**
 * \brief Test the sensor is connected and can communicate with the CPU
 * \param[out] connectiontest returns 1 if sensor didn't respond the request, 0 otherwise
 * \param[in] gps The gps ublox object
 */
bool testGPSConnection(Ublox gps){
    // testConnection() returns 0 if it can establish an SPI connection with the
    // sensor. If somehow it can't, a 1 will be returned. If in the first 300 symbols a
    // a message is correct, the test is passed.
    if(gps.testConnection()){
        return 0;
    }else{
        printf("No GPS module is connected\n");
        return 1;
    }
}

/**
 * \brief Set a data capture rate easily
 * \param[out] GPSRateAssert returns 0 if the rate couldn't be configured correctly
 * \param[in] gps The gps ublox object
 * \param[in] rate The data rate in ... [missing unit]
 */
bool setNewGPSRate(Ublox gps, int rate){
    // ConfigureSolutionRate() allows the user to set a fixed data capture rate
    if (gps.configureSolutionRate(rate)){
        return 0;
    }else{
        printf("Error setting new rate\n");
        return 1;
    }
}


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
 * \param[in] address this parameter is meant to hold the server's ipv4 address
 */

void read_fromsens(float *tabaccel, float *tabgyr, float *tabmag, char *address){
    /*Create socket*/
    printf("Server's address: %s\n",address);
    int socket = create();
    int fileT = create_i2c(0x18);
    // We create a dynamic vector to save our position data.
    std::vector<double> pos_data;

    // The navio's  GPS uses ublox protocol for SPI communication. This is
    // a propietary protocol by Ublox that allows perfect clock synchronisation.
    
    // Ublox doc: https://www.u-blox.com/en/docs/UBX-13003221
    Ublox gps;


    auto sensor = get_inertial_sensor();
    sensor->initialize();

    int gpstest = 1;
    if(!testGPSConnection(gps)){
        // We set the new rate for data capture
        if(!setNewGPSRate(gps, 1000)){
            gpstest = 0;
        }
//-------------------------------------------------------------------------

        while(gpstest == 0) {
            sensor->update();
            sensor->read_accelerometer(tabaccel,tabaccel+1,tabaccel+2);
            sensor->read_gyroscope(tabgyr,tabgyr+1,tabgyr+2);
            sensor->read_magnetometer(tabmag,tabmag+1,tabmag+2);

            /*Send IMU info via socket*/
            send_float(socket, *(tabaccel),'I','1', PORT, address);
            send_float(socket, *(tabaccel+1),'I','2', PORT, address);
            send_float(socket, *(tabaccel+2),'I','3', PORT, address);
            send_float(socket, *(tabgyr),'I','4', PORT, address);
            send_float(socket, *(tabgyr+1),'I','5', PORT, address);
            send_float(socket, *(tabgyr+2),'I','6', PORT, address);
            send_float(socket, *(tabmag),'I','7', PORT, address);
            send_float(socket, *(tabmag+1), 'I','8', PORT, address);
            send_float(socket, *(tabmag+2),'I','9', PORT, address);

            // Here we use decodeSingleMessage(message_t msg, std::vector<double>& position_data). This is the 
            // function that will trigger the SPI communication incomming from the GPS module. The first argument
            // is the byte we want to read from the module and the second the place in which said byte stream is 
            // going to be stored. Here we'll read the NAV_POSLLH bytes which gives us the position of the GPS module
            // by returning the lagitude and longitude values.

            // Each time a message was decoded, print "message was captured"
            if(gps.decodeSingleMessage(Ublox::NAV_POSLLH, pos_data) == 1){
                //printf("message captured\n");
                /*Send GPS info via socket*/
                send_float(socket, (float)pos_data[0], 'G','1', PORT, address);
                send_float(socket, (float)pos_data[1], 'G','2', PORT, address);
                send_float(socket, (float)pos_data[2], 'G','3', PORT, address);
                send_float(socket, (float)pos_data[3], 'G','4', PORT, address);
                send_float(socket, (float)pos_data[4], 'G','5', PORT, address);
                send_float(socket, (float)pos_data[5], 'G','6', PORT, address);
                send_float(socket, (float)pos_data[6], 'G','7', PORT, address);
                /*The data decoded*/
                // GPS Millisecond Time of Week: (pos_data[0]/1000) s
                // Longitude: pos_data[1]/10000000
                // Latitude: pos_data[2]/10000000\n
                // Height above Ellipsoid: (pos_data[3]/1000) m
                // Height above mean sea level: (pos_data[4]/1000) m
                // Horizontal Accuracy Estateimate: (pos_data[5]/1000)) m
                // Vertical Accuracy Estateimate: (pos_data[6]/1000) m
            }
            // We can also decode a status message called NAV_STATUS which can tell us if there's some problem on board our satellite.
            // We can use the onboard RTC with the system command usleep(int utime) wich allows us to capture data in between a specific
            // amount of time. 
            send_float(socket, returntemp(fileT), 'T','1', PORT, address);
            usleep(500);
            //printf("%f", *tabaccel);
        }
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
    read_fromsens(tableauaccel, tableaumag, tableaugyr, argv[1]);
}
