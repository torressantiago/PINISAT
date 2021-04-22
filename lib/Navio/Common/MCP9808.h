#ifndef MCP9808_H
#define MCP9808_H
/**
 * \brief Create I2C bus and configure slave with given address
 * \param[out] file returns file descriptor return from reading /dev/i2c-1
 * \param[in] addr inputs the slave's address
 */
int create_i2c(int addr);

/**
 * \brief // Write to slave and output temperature in celsius
 * \param[out] cTemp returns the temperature in celsius degrees
 * \param[in] file the file descriptor is given as an input.
 */
float returntemp(int file)

#endif