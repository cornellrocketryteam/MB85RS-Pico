#ifndef MB85RS_HPP
#define MB85RS_HPP

#include "hardware/spi.h"
#include "pico/stdlib.h"

#define MB85RS_WRITE (0x02)
#define MB85RS_READ (0x03)
#define MB85RS_WRDI (0x04)
#define MB85RS_WREN (0x06)
#define MB85RS_RDID (0x9F)

class MB85RS {
public:
    MB85RS(spi_inst_t *spi_type);

    bool begin();

    bool read_bytes();

    bool write_bytes();
private:
    uint8_t get_id();

    spi_inst_t *spi;
};

#endif // MB85RS_HPP