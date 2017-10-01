//This is the header file for the Morse library

#ifndef Morse // Check if header is already loaded
#define Morse

#include "Arduino.h" // Load Arduino library

// Create class
class MorseCode {
  public: // Functions and variables that can be used in the main loop
    
    MorseCode(int buttonPin, int ledPinInput, int ledPinOutput, int eepromPin);// Constructor

    // Methods
    char buttonPress();
    void writeEEPROM(int MEMLOCATIONaddr, char DatByte_in);
    void ledEndTransmission();
    void printMessage(int counter, char DatByte_out);


  private:// Functions and variables that cannot be used in the main loop
    void translate(String morseString, int counter);
    void letterMorse(String morse);
    int _buttonPin;
    int _ledPinInput;
    int _ledPinOutput;
    int _eepromPin;
    int _EEPROMI2Caddress;

};//Close Class

#endif
