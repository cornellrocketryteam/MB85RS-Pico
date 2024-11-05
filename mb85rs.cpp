#include "mb85rs.hpp"

MB85RS::MB85RS(spi_inst_t *spi_type) {
    spi = spi_type;
}

bool MB85RS::begin() {

    return true;
}