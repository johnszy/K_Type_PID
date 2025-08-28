#include "max31855.h"

// Fault code bit masks (per MAX31855 datasheet)
#define FAULT_OC  (1 << 0)  // Open Circuit
#define FAULT_SCG (1 << 1)  // Short to GND
#define FAULT_SCV (1 << 2)  // Short to VCC

static uint32_t readRawData(void) {
    // Placeholder: perform 32-bit SPI read from MAX31855
    // Must pull CS low, clock out 32 bits, then release CS
    // Example return value for testing
    uint32_t result = 0;
    uint8_t byte;

    //cs_low();  // Start transaction
    LATC6 = 0;

    for (int i = 0; i < 4; i++) {
        byte = spi_transfer(0x00);              // Send dummy byte to clock data out
        LATC6 = 0;
        result = (result << 8) | byte;          // Shift and accumulate
        LATC6 = 0;
    }

    //cs_high(); // End transaction
    LATC6 = 1;
    
    return result;
}

void init_TC(void) {
    // Initialize SPI peripheral here
    // Configure pins, mode 0, etc.
}

float getTemp_TC(void) {
    uint32_t raw = readRawData();

    // Bits [31:18] = signed 14-bit thermocouple temp
    int16_t temp_tc = (raw >> 18) & 0x3FFF;
    if (temp_tc & 0x2000) { // sign extend
        temp_tc |= 0xC000;
    }
    return (float)temp_tc * 0.25f; // each LSB = 0.25°C
}

float getDieTemp(void) {
    uint32_t raw = readRawData();

    // Bits [15:4] = signed 12-bit internal temp
    int16_t temp_die = (raw >> 4) & 0x0FFF;
    if (temp_die & 0x0800) { // sign extend
        temp_die |= 0xF000;
    }
    return (float)temp_die * 0.0625f; // each LSB = 0.0625°C
}

uint8_t getFaultCodes(void) {
    uint32_t raw = readRawData();

    // Bits [2:0] = fault codes, bit 16 = fault flag
    if (raw & 0x00010000) {
        return (uint8_t)(raw & 0x07); // return OC, SCG, SCV bits
    }
    return 0; // no fault
}

