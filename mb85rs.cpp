#include "mb85rs.hpp"
#include <cstdio>

MB85RS::MB85RS(spi_inst_t *spi_type, uint chip_select) {
    spi = spi_type;
    cs = chip_select;
}

bool MB85RS::begin() {
    if (!get_id()) {
        return false;
    }
    return true;
}

bool MB85RS::read_bytes(uint32_t addr, uint8_t *data, uint8_t len) {
    uint8_t cmd[4] = {MB85RS_READ, (uint8_t)(addr >> 16), (uint8_t)(addr >> 8), (uint8_t)addr};

    gpio_put(cs, 0);

    if (spi_write_blocking(spi, cmd, 4) < 0) {
        gpio_put(cs, 1);
        return false;
    }
    if (spi_read_blocking(spi, 0, data, len) < 0) {
        gpio_put(cs, 1);
        return false;
    }

    gpio_put(cs, 1);
    return true;
}

bool MB85RS::write_bytes(uint32_t addr, uint8_t *data, uint8_t len) {
    uint8_t write_enable = MB85RS_WREN;
    uint8_t write_disable = MB85RS_WRDI;

    uint8_t cmd[4] = {MB85RS_WRITE, (uint8_t)(addr >> 16), (uint8_t)(addr >> 8), (uint8_t)addr};

    gpio_put(cs, 0);
    if (spi_write_blocking(spi, &write_enable, 1) < 0) {
        gpio_put(cs, 1);
        return false;
    }
    gpio_put(cs, 1);

    gpio_put(cs, 0);
    // Write data at addr
    if (spi_write_blocking(spi, cmd, 4) < 0) {
        gpio_put(cs, 1);
        return false;
    }
    if (spi_write_blocking(spi, data, len) < 0) {
        gpio_put(cs, 1);
        return false;
    }
    gpio_put(cs, 1);

    gpio_put(cs, 0);
    if (spi_write_blocking(spi, &write_disable, 1) < 0) {
        gpio_put(cs, 1);
        return false;
    }
    gpio_put(cs, 1);

    return true;
}

bool MB85RS::get_id() {
    uint8_t cmd = MB85RS_RDID;
    uint8_t ret[4] = {0};

    gpio_put(cs, 0);

    if (spi_write_blocking(spi, &cmd, 1) < 0) {
        gpio_put(cs, 1);
        return false;
    }

    if (spi_read_blocking(spi, 0, ret, 4) < 0) {
        gpio_put(cs, 1);
        return false;
    }

    gpio_put(cs, 1);

    for (int i = 0; i < 4; i++) {
        if (ret[i] != chip_id[i]) {
            return false;
        }
    }
    return true;
}