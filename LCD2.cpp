#include <iostream>
#include <lgpio.h>
#include <unistd.h>
#include <string>
using namespace std;


string displayA(int i2c) 
{
    cout << "Displaying letter 'A'..." << endl;
    
    // ASCII code for 'A' is 0x41 (0100 0001 in binary)
    // Upper nibble = 0x4, Lower nibble = 0x1
    
    // Send upper nibble (0x4) with RS=1 (data mode)
    lgI2cWriteByte(i2c, 0x4D);  // 0100 1101: data=0x4, RS=1, EN=1, BL=1
    lgI2cWriteByte(i2c, 0x49);  // 0100 1001: data=0x4, RS=1, EN=0, BL=1
    
    // Send lower nibble (0x1) with RS=1 (data mode)
    lgI2cWriteByte(i2c, 0x1D);  // 0001 1101: data=0x1, RS=1, EN=1, BL=1
    lgI2cWriteByte(i2c, 0x19);  // 0001 1001: data=0x1, RS=1, EN=0, BL=1
    
    usleep(100);  // Small delay
    
    return "Letter 'A' sent!";
}

void printName(int i2c)
{
    cout << "Printing name..." << endl;

    lgI2cWriteByte(i2c, 0x5D); // S
    lgI2cWriteByte(i2c, 0x59);
    lgI2cWriteByte(i2c, 0x3D);
    lgI2cWriteByte(i2c, 0x39);
    
    lgI2cWriteByte(i2c, 0x7D); // y
    lgI2cWriteByte(i2c, 0x79);
    lgI2cWriteByte(i2c, 0x9D);
    lgI2cWriteByte(i2c, 0x99);

    lgI2cWriteByte(i2c, 0x6D); // m
    lgI2cWriteByte(i2c, 0x69);
    lgI2cWriteByte(i2c, 0xDD);
    lgI2cWriteByte(i2c, 0xD9);

    lgI2cWriteByte(i2c, 0x7D); // u 
    lgI2cWriteByte(i2c, 0x79);
    lgI2cWriteByte(i2c, 0x5D);
    lgI2cWriteByte(i2c, 0x59);

    lgI2cWriteByte(i2c, 0x6D); // m
    lgI2cWriteByte(i2c, 0x69);
    lgI2cWriteByte(i2c, 0xDD);
    lgI2cWriteByte(i2c, 0xD9);

    lgI2cWriteByte(i2c, 0x2D); // space
    lgI2cWriteByte(i2c, 0x29);
    lgI2cWriteByte(i2c, 0x0D);
    lgI2cWriteByte(i2c, 0x09);

    lgI2cWriteByte(i2c, 0x4D); // C
    lgI2cWriteByte(i2c, 0x49);
    lgI2cWriteByte(i2c, 0x3D);
    lgI2cWriteByte(i2c, 0x39);

    lgI2cWriteByte(i2c, 0x6D); // h
    lgI2cWriteByte(i2c, 0x69);
    lgI2cWriteByte(i2c, 0x8D);
    lgI2cWriteByte(i2c, 0x89);

    lgI2cWriteByte(i2c, 0x6D); // o
    lgI2cWriteByte(i2c, 0x69);
    lgI2cWriteByte(i2c, 0xFD);
    lgI2cWriteByte(i2c, 0x29);

    usleep(100);

    cout << "Name printed!" << endl;

}

void clearScreen(int i2c_handle) 
{
    cout << "Clearing LCD screen..." << endl;
    lgI2cWriteByte(i2c_handle, 0x0C);
    lgI2cWriteByte(i2c_handle, 0x08);
    lgI2cWriteByte(i2c_handle, 0x1C);
    lgI2cWriteByte(i2c_handle, 0x18); //refactor

    usleep(5000);  // Wait 5ms for clear to complete (longer delay)

    cout << "Clear command sent!" << endl;
}

void initLCD(int i2c_handle) {
    cout << "Initializing LCD..." << endl;
    
    usleep(50000);  // Wait 50ms after power on
    
    // Put LCD into 4-bit mode (send 0x03 three times, then 0x02)
    lgI2cWriteByte(i2c_handle, 0x3C);
    lgI2cWriteByte(i2c_handle, 0x38);
    usleep(5000);
    
    lgI2cWriteByte(i2c_handle, 0x3C);
    lgI2cWriteByte(i2c_handle, 0x38);
    usleep(5000);
    
    lgI2cWriteByte(i2c_handle, 0x3C);
    lgI2cWriteByte(i2c_handle, 0x38);
    usleep(5000);
    
    lgI2cWriteByte(i2c_handle, 0x2C);
    lgI2cWriteByte(i2c_handle, 0x28);
    usleep(5000);
    
    cout << "LCD initialized!" << endl;
}

void printMsg(string msg, int i2c_handle)
{
    int upper;
    int lower;
    for (int i = 0; i < msg.size(); i++)
    {
        cout << "character " << i << ": " << msg.at(i) << endl;
        upper = (msg.at(i) & 0xF0);        
        lower = (msg.at(i) & 0x0F) << 4;
        lgI2cWriteByte(i2c_handle, upper | 0x0D);
        lgI2cWriteByte(i2c_handle, upper | 0x09);
        lgI2cWriteByte(i2c_handle, lower | 0x0D);
        lgI2cWriteByte(i2c_handle, lower | 0x09);
    }

}
int main() {
    int i2c_handle = lgI2cOpen(1, 0x27, 0);
    
    if (i2c_handle < 0) {
        cout << "Failed to open I2C connection" << endl;
        return 1;
    }
    initLCD(i2c_handle);

    cout << "Writing a..." << endl;

    printMsg("Symum Chowdhury", i2c_handle);
    usleep(1000000);
    clearScreen(i2c_handle);
    
    // Send clear command (0x01) as COMMAND (RS=0)
    // uint8_t command = 0x01;  // Clear display command
    
    // Send high nibble with RS=0 (command mode) and enable pulse
    // uint8_t high_nibble = (command & 0xF0) | 0x08 | 0x04;  // RS=0 for command
    // lgI2cWriteByte(i2c_handle, high_nibble);
    // usleep(1);
    // high_nibble = (command & 0xF0) | 0x08;  // Enable low, RS still 0
    // lgI2cWriteByte(i2c_handle, high_nibble);
    // usleep(1);
    
    // // Send low nibble with RS=0 and enable pulse  
    // uint8_t low_nibble = ((command & 0x0F) << 4) | 0x08 | 0x04;
    // lgI2cWriteByte(i2c_handle, low_nibble);
    // usleep(1);
    // low_nibble = ((command & 0x0F) << 4) | 0x08;
    // lgI2cWriteByte(i2c_handle, low_nibble);
    
    
    lgI2cClose(i2c_handle);
    return 0;
}



    
   

