#include "ssd1306.h"

int main () {
    ssd1309Init();

    uint8_t buff [128] = {0x00, 0x00, 0xFF, 0xF0, 0x0F, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xFF, 0xF0, 0x0F, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xFF, 0xF0, 0x0F, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xFF, 0xF0, 0x0F, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xFF, 0xF0, 0x0F, 0x00, 0x00, 0x00};
    
    sendData(buff, 128);
}