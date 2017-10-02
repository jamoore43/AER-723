//Authors: Joel Moore and Jeffrey Jevnikar
// Date: 09/30/2017
// The following code will accept Morse code input from the user, stores it onto an EEPROM and replays the message.
// The message is also converted into English characters.

#include <Wire.h> //I2C library
#include <Morse.h> //Morse Library

// Declare variables
const int buttonPin = 2;
const int ledPinOutput = 9;
const int ledPinInput = 5;
const int eepromPin = 3;

// Initialize constructor
MorseCode morse(buttonPin, ledPinInput, ledPinOutput, eepromPin);

///////////////////////////////////////////////////////////////////////////////////////
// Setup
///////////////////////////////////////////////////////////////////////////////////////

void setup()
{
  Wire.begin(); // initialise the connection as the device master
  Serial.begin(9600); // Enable Serial port (so we can print results to understand whats going on)
}

///////////////////////////////////////////////////////////////////////////////////////
// Main Loop
///////////////////////////////////////////////////////////////////////////////////////

void loop(){
  int MEMLOCATIONaddr = 0; // Initial memory address
  char DatByte_in;
  char DatByte_out;

  // Loop to record user input
  while (1) {

    DatByte_in = morse.buttonPress(); // Check state of button and determine the desired character

    // Condition to break loop
    if(DatByte_in == '!')
      break;
   
    morse.writeEEPROM(MEMLOCATIONaddr, DatByte_in);  // Write character to EEPROM

    MEMLOCATIONaddr++; // Move to next address
    delay(400);
  }

  morse.ledEndTransmission(); // Indicate end of transmission by flashing LED
  delay(2000);
  
  morse.printMessage(MEMLOCATIONaddr, DatByte_out); // Translate and print morse code
}
