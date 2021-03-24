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
    }
}

int main(int argc, char *argv[]){


    // We create a dynamic vector to save our position data.
    std::vector<double> pos_data;

    // The navio's  GPS uses ublox protocol for SPI communication. This is
    // a propietary protocol by Ublox that allows perfect clock synchronisation.
    Ublox gps;

    // We test the connection to the sensor    
    testGPSConnection(gps);

    // We set the new rate for data capture
    setNewGPSRate(gps, 1000);

    return 0;
}