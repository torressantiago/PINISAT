#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>

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

int main(){
    int fileT = create_i2c(0x18);
    while(1){
        printf("Temp is %f C\n",returntemp(fileT));
    }
}