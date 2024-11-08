#include "mb85rs.hpp"
#include <cstdio>

MB85RS::MB85RS(spi_inst_t *spi_type, uint chip_select) {
    spi = spi_type;
    cs = chip_select;
}

bool MB85RS::begin() {
    gpio_init(cs);	
    gpio_set_dir(cs, GPIO_OUT);
    gpio_put(cs, 1) ;
    
    if (!get_id()) {
        return false;
    }
    return true;
}

bool MB85RS::read_bytes() {

}

bool MB85RS::write_bytes() {
    
}

bool MB85RS::get_id() {
    uint8_t addr[1] = { MB85RS_RDID };
    uint8_t ret[4] = {0};

    gpio_put(cs, 0);

    spi_write_blocking(spi, addr, 1);
    spi_read_blocking(spi, 0, ret, 4);

    gpio_put(cs, 1);
    
    for (int i = 0; i < 4; i++) {
        if (ret[i] != chip_id[i]) {
            return false;
        }
    }
    return true;
}