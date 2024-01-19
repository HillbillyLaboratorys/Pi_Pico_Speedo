#include "ssd1306.h"

#define CD_PIN 20
#define RST_PIN 21

#define PWR_ON 0xAF
#define PWR_OFF 0xAE

#define BAUD 1000000

static inline void cs_select() {
    asm volatile("nop \n nop \n nop");
    gpio_put(PICO_DEFAULT_SPI_CSN_PIN, 0);  // Active low
    asm volatile("nop \n nop \n nop");
}

static inline void cs_deselect() {
    asm volatile("nop \n nop \n nop");
    gpio_put(PICO_DEFAULT_SPI_CSN_PIN, 1);
    asm volatile("nop \n nop \n nop");
}

// command low
void sendCommand(uint8_t* buffer, size_t size) {
    cs_select();
    gpio_put(CD_PIN, 0);
    spi_write_blocking(spi0, buffer, size);
    cs_deselect();
}

void sendData(uint8_t* buffer, size_t size) {
    cs_select();
    gpio_put(CD_PIN, 1);
    spi_write_blocking(spi0, buffer, size);
    cs_deselect();
}

void ssd1309Init () {
    spi_init(spi0, BAUD);

    gpio_init(CD_PIN);
    gpio_init(RST_PIN);
    gpio_set_dir(CD_PIN, GPIO_OUT);
    gpio_set_dir(RST_PIN, GPIO_OUT);

    gpio_put(RST_PIN, 1);

    gpio_set_function(PICO_DEFAULT_SPI_SCK_PIN, GPIO_FUNC_SPI);
    gpio_set_function(PICO_DEFAULT_SPI_TX_PIN, GPIO_FUNC_SPI);

    // Make the SPI pins available to picotool
    //bi_decl(bi_2pins_with_func(PICO_DEFAULT_SPI_TX_PIN, PICO_DEFAULT_SPI_SCK_PIN, GPIO_FUNC_SPI));

    // Chip select is active-low, so we'll initialise it to a driven-high state
    gpio_init(PICO_DEFAULT_SPI_CSN_PIN);
    gpio_set_dir(PICO_DEFAULT_SPI_CSN_PIN, GPIO_OUT);
    gpio_put(PICO_DEFAULT_SPI_CSN_PIN, 1);

    // Make the CS pin available to picotool
    //bi_decl(bi_1pin_with_name(PICO_DEFAULT_SPI_CSN_PIN, "SPI CS"));

    // Defaults
    // 0xA8 Multiplex ratio 64 0X3F
    // 0xD5 Clock divider 0x80

    // display off, set lower column start PAM, high column, set mem addressing mode, mode: horizontal, set contrast, max contrast, inversion off, offset, 0 offset, precharge period, 34, comHW config, config 7, vcomH level, 40, enable ram output, display on
    uint8_t initCommands [] = {0xAE, 0x00, 0x10, 0x20, 0x00, 0x81, 0xFF, 0xA6, 0xD3, 0x00, 0xD9, 0x22, 0XDA, 0x12, 0xDB, 0x40, 0xA4, 0xAF};

    sendCommand(initCommands, 18);
    
}


