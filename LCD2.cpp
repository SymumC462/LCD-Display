#include <iostream>
#include <lgpio.h>
#include <unistd.h>
#include <string>
using namespace std;


class LCDScreen 
{
    private: 
        int i2c_handle;

    public:
        void seti2c(int i2c)
        {
            i2c_handle = i2c;
        }
        void displayStatic(string msg)
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
        void clear()
        {
            cout << "Clearing LCD screen..." << endl;
            lgI2cWriteByte(i2c_handle, 0x0C);
            lgI2cWriteByte(i2c_handle, 0x08);
            lgI2cWriteByte(i2c_handle, 0x1C);
            lgI2cWriteByte(i2c_handle, 0x18); //refactor

            usleep(5000);  // Wait 5ms for clear to complete (longer delay)

            cout << "Clear command sent!" << endl;
        
        }
        void displayScroll(string msg, int times)
        {
            cout << "Printing and Scrolling Message: " << msg << endl;
            displayStatic(msg);
            usleep(500000);
            clear();
            for (int i = 1; i <= times; i++)
            {
                for (int j = 1; j <= i; j++)
                {
                    displayStatic(" ");
                }
                displayStatic(msg);
                usleep(50000);
                clear();
            }
        }

        
        
        
        
    
};

            
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



void printAndScroll(string msg, int i2c_handle, int times)
{
    cout << "Printing and Scrolling Message: " << msg << endl;
    printMsg(msg, i2c_handle);
    usleep(500000);
    clearScreen(i2c_handle);
    for (int i = 1; i <= times; i++)
    {
       for (int j = 1; j <= i; j++)
       {
        printMsg(" ", i2c_handle);
       }
       printMsg(msg, i2c_handle);
       usleep(50000);
       clearScreen(i2c_handle);
    }
    
}
int main() {
    LCDScreen lcd;
    int i2c_handle = lgI2cOpen(1, 0x27, 0);
    
    if (i2c_handle < 0) {
        cout << "Failed to open I2C connection" << endl;
        return 1;
    }
    lcd.seti2c(i2c_handle);
    initLCD(i2c_handle);
    lcd.displayScroll("Symum", 16);
    usleep(1000000);
    lcd.clear();
    
    
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



    
   

