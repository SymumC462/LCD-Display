#include <iostream>
#include <lgpio.h>
#include <unistd.h>

int main() {
    int i2c_handle = lgI2cOpen(1, 0x27, 0);
    
    if (i2c_handle < 0) {
        std::cout << "Failed to open I2C connection" << std::endl;
        return 1;
    }
    
    std::cout << "Clearing LCD screen..." << std::endl;
    
    // Send clear command (0x01) as COMMAND (RS=0)
    uint8_t command = 0x01;  // Clear display command
    
    // Send high nibble with RS=0 (command mode) and enable pulse
    uint8_t high_nibble = (command & 0xF0) | 0x08 | 0x04;  // RS=0 for command
    lgI2cWriteByte(i2c_handle, high_nibble);
    usleep(1);
    high_nibble = (command & 0xF0) | 0x08;  // Enable low, RS still 0
    lgI2cWriteByte(i2c_handle, high_nibble);
    usleep(1);
    
    // Send low nibble with RS=0 and enable pulse  
    uint8_t low_nibble = ((command & 0x0F) << 4) | 0x08 | 0x04;
    lgI2cWriteByte(i2c_handle, low_nibble);
    usleep(1);
    low_nibble = ((command & 0x0F) << 4) | 0x08;
    lgI2cWriteByte(i2c_handle, low_nibble);
    
    usleep(5000);  // Wait 5ms for clear to complete (longer delay)
    
    std::cout << "Clear command sent!" << std::endl;
    
    lgI2cClose(i2c_handle);
    return 0;
}