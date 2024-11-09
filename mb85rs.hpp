/**
 * @file mb85rs.hpp
 * @author csg83
 *
 * @brief MB85RS driver definitions
 */

#ifndef MB85RS_HPP
#define MB85RS_HPP

#include "hardware/gpio.h"
#include "hardware/spi.h"
#include "pico/stdlib.h"

// Opcodes
#define MB85RS_WRITE (0x02)
#define MB85RS_READ (0x03)
#define MB85RS_WRDI (0x04)
#define MB85RS_WREN (0x06)
#define MB85RS_RDID (0x9F)

// RDID expected values
#define MANUFACTURER_ID (0x04)
#define CONT_CODE (0x7F)
#define PRODUCT_ID_1 (0x48)
#define PRODUCT_ID_2 (0x03)

/**
 * Representation of the MB85RS chip
 */
class MB85RS {
public:
    /**
     * Initializes an MB85RS object on an SPI bus.
     * @param spi_type The SPI bus that this chip is on
     * @param chip_select The SPI chip select pin to use
     */
    MB85RS(spi_inst_t *spi_type, uint chip_select);

    /**
     * Attempts to establish a connection with the chip.
     * @return True on successful connection, false otherwise
     */
    bool begin();

    /**
     * Reads a specified number of bytes from an address on the chip
     * @param addr The address to read from
     * @param data The resulting data that is read
     * @param len The number of bytes to read
     */
    bool read_bytes(uint32_t addr, uint8_t *data, uint8_t len);

    /**
     * Writes a specified number of bytes to an address on the chip
     * @param addr The address to write to
     * @param data The data to write
     * @param len The number of bytes to write
     */
    bool write_bytes(uint32_t addr, uint8_t *data, uint8_t len);

private:
    /**
     * Reads the MB85RS's device ID
     * @return True on verified ID, false otherwise
     */
    bool get_id();
    uint8_t chip_id[4] = {MANUFACTURER_ID, CONT_CODE, PRODUCT_ID_1, PRODUCT_ID_2};

    /**
     * The SPI bus
     */
    spi_inst_t *spi;

    /**
     * The chip select pin
     */
    uint cs;
};

#endif // MB85RS_HPP