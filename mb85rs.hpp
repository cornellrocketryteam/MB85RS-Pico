#ifndef MB85RS_HPP
#define MB85RS_HPP

#include "hardware/spi.h"
#include "hardware/gpio.h"
#include "pico/stdlib.h"

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

class MB85RS {
public:
    MB85RS(spi_inst_t *spi_type, uint chip_select);

    bool begin();

    bool read_bytes();

    bool write_bytes();
private:
    bool get_id();
    uint8_t chip_id[4] = { MANUFACTURER_ID, CONT_CODE, PRODUCT_ID_1, PRODUCT_ID_2 };

    spi_inst_t *spi;
    uint cs;
};

#endif // MB85RS_HPP