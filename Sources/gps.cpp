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

int main(int argc, char *argv[]){


    // We create a dynamic vector to save our position data.
    std::vector<double> pos_data;

    // create ublox
    Ublox gps;


    return 0;
}