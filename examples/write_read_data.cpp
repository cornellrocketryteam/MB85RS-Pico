#include "../mb85rs.hpp"
#include "tusb.h"
#include <cstdio>

#define SPI_PORT spi0
#define SPI_MISO 16
#define SPI_MOSI 19
#define SPI_SCK 18

#define FRAM_CS 17

MB85RS fram(SPI_PORT);

int main() {
    stdio_init_all();

    spi_init(SPI_PORT, 20000000);
    gpio_set_function(SPI_MISO, GPIO_FUNC_SPI);
    gpio_set_function(SPI_MOSI, GPIO_FUNC_SPI);
    gpio_set_function(SPI_SCK, GPIO_FUNC_SPI);

    while (!tud_cdc_connected()) {
        sleep_ms(500);
    }
    printf("Connected\n");

    

    return 0;
}