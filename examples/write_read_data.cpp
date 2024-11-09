#include "../mb85rs.hpp"
#include "tusb.h"
#include <cstdio>

#define SPI_PORT spi0
#define SPI_MISO 16
#define SPI_MOSI 19
#define SPI_SCK 18

#define FRAM_CS 17

MB85RS fram(SPI_PORT, FRAM_CS);

int main() {
    stdio_init_all();

    spi_init(SPI_PORT, 20000000);
    gpio_set_function(SPI_MISO, GPIO_FUNC_SPI);
    gpio_set_function(SPI_MOSI, GPIO_FUNC_SPI);
    gpio_set_function(SPI_SCK, GPIO_FUNC_SPI);

    gpio_init(FRAM_CS);
    gpio_set_dir(FRAM_CS, GPIO_OUT);
    gpio_put(FRAM_CS, 1);

    while (!tud_cdc_connected()) {
        sleep_ms(500);
    }
    printf("Connected\n");

    if (fram.begin()) {
        printf("Begin successful\n");
    } else {
        printf("Begin failed\n");
        return 1;
    }

    uint8_t data = 42;
    uint8_t resp;

    uint64_t start = time_us_64();
    if (!fram.write_bytes(500000, &data, 1)) {
        printf("Write failed\n");
    }
    uint64_t write_duration = time_us_64() - start;

    start = time_us_64();
    if (!fram.read_bytes(500000, &resp, 1)) {
        printf("Read failed\n");
    }
    uint64_t read_duration = time_us_64() - start;

    printf("Data read: %d\n\n", resp);

    printf("Write time: %llu\n", write_duration);
    printf("Read time: %llu\n", read_duration);

    return 0;
}