/** @file gps.cpp
 * 
 * @brief GPS decoding using Emlid Navio 2 HAT for Raspberry Pi 
 * and sharing through on-board sockets.
 *
 * @author Santiago Torres Borda       
 * 
 * @version 1.0
 * @brief
 * Listens to GPS using SPI via Ublox class and shows data as a standard output
 */ 

#include <Common/Ublox.h>
#include <Common/Util.h>

using namespace std;


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
bool setNewGPSRate(gps, int rate){
    // ConfigureSolutionRate() allows the user to set a fixed data capture rate
    if (!gps.configureSolutionRate(rate)){
        return 0;
    }else{
        printf("Error setting new rate\n");
        return 1;
    }
}

int main(int argc, char *argv[]){


    // We create a dynamic vector to save our position data.
    std::vector<double> pos_data;

    // The navio's  GPS uses ublox protocol for SPI communication. This is
    // a propietary protocol by Ublox that allows perfect clock synchronisation.
    
    // Ublox doc: https://www.u-blox.com/en/docs/UBX-13003221
    Ublox gps;

    // We test the connection to the sensor    
    if(!testGPSConnection(gps)){
        // We set the new rate for data capture
        if(!setNewGPSRate(gps, 1000)){
            while(true){
                // Here we use decodeSingleMessage(message_t msg, std::vector<double>& position_data). This is the 
                // function that will trigger the SPI communication incomming from the GPS module. The first argument
                // is the byte we want to read from the module and the second the place in which said byte stream is 
                // going to be stored. Here we'll read the NAV_POSLLH bytes which gives us the position of the GPS module
                // by returning the lagitude and longitude values.
                if(gps.decodeSingleMessage(Ublox::NAV_POSLLH, pos_data) == 1){
                    printf("message captured/n");
                }else{
                    printf("message was not sent\n");
                }
                // We can also decode a status message called NAV_STATUS which can tell us if there's some problem on board our satellite.
            }
        }
        // We can use the onboard RTC with the system command usleep(int utime) wich allows us to capture data in between a specific
        // amount of time. 
        usleep(500);
    }
        

    return 0;
}