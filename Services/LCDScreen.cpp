#include "LCDScreen.hpp"
#include <string>
#include <iostream>
#include <lgpio.h>
#include <unistd.h>
using namespace std;

int i2c_handle;
const int NUM_COLUMNS = 16;

LCDScreen::LCDScreen()
{
    i2c_handle = lgI2cOpen(1, 0x27, 0);
    if (i2c_handle < 0) 
    {
        throw std::runtime_error("Failed to open I2C connection");
    }
    init();
}

LCDScreen::~LCDScreen()
{
    lgI2cClose(i2c_handle);
}

void LCDScreen::displayStatic(string msg)
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

void LCDScreen::clear()
{
    cout << "Clearing LCD screen..." << endl;
    lgI2cWriteByte(i2c_handle, 0x0C);
    lgI2cWriteByte(i2c_handle, 0x08);
    lgI2cWriteByte(i2c_handle, 0x1C);
    lgI2cWriteByte(i2c_handle, 0x18); //refactor

    usleep(5000);  // Wait 5ms for clear to complete (longer delay)

    cout << "Clear command sent!" << endl;        
}

void LCDScreen::moveToSecondLine()
{
    // Move cursor to second line, row 1, column 0 (command 0xC0)
    lgI2cWriteByte(i2c_handle, 0xCC);  
    lgI2cWriteByte(i2c_handle, 0xC8);  
    lgI2cWriteByte(i2c_handle, 0x0C);  
    lgI2cWriteByte(i2c_handle, 0x08);
}
void LCDScreen::displayScroll(string msg)
{
    cout << "Printing and Scrolling Message: " << msg << endl;
    displayStatic(msg);
    usleep(500000);
    for (int i = 0; i < NUM_COLUMNS; i++)
    {
        // shift to the right by 1 
        lgI2cWriteByte(i2c_handle, 0x1C);
        lgI2cWriteByte(i2c_handle, 0x18);
        lgI2cWriteByte(i2c_handle, 0xCC);
        lgI2cWriteByte(i2c_handle, 0xC8);
        usleep(100000);
    }
}

void LCDScreen::init()
{
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

    // Function set: 4-bit, 2 lines, 5x8 font
    lgI2cWriteByte(i2c_handle, 0x2C);
    lgI2cWriteByte(i2c_handle, 0x28);
    lgI2cWriteByte(i2c_handle, 0x8C);
    lgI2cWriteByte(i2c_handle, 0x88);
    usleep(2000);
    
    // Display on, cursor off, blink off
    lgI2cWriteByte(i2c_handle, 0x0C);
    lgI2cWriteByte(i2c_handle, 0x08);
    lgI2cWriteByte(i2c_handle, 0xCC);
    lgI2cWriteByte(i2c_handle, 0xC8);
    usleep(2000);
    
    // Entry mode: increment cursor
    lgI2cWriteByte(i2c_handle, 0x0C);
    lgI2cWriteByte(i2c_handle, 0x08);
    lgI2cWriteByte(i2c_handle, 0x6C);
    lgI2cWriteByte(i2c_handle, 0x68);
    usleep(2000);
    
    // Clear display
    lgI2cWriteByte(i2c_handle, 0x0C);
    lgI2cWriteByte(i2c_handle, 0x08);
    lgI2cWriteByte(i2c_handle, 0x1C);
    lgI2cWriteByte(i2c_handle, 0x18);
    usleep(5000);
    
    cout << "LCD initialized!" << endl;
}