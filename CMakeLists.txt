add_library(MB85RS-Pico INTERFACE)

target_sources(MB85RS-Pico INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/mb85rs.cpp
)

target_link_libraries(MB85RS-Pico INTERFACE
    hardware_spi
    pico_stdlib
)