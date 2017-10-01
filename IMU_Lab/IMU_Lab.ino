#include <Wire.h>
#include <SPI.h>
#include <SparkFunLSM9DS1.h>

// Define constants from calibration, and LED pin #
float magMax = 9.18;
float magMin = -4.59;
int ledPin = 5;

//////////////////////////
// LSM9DS1 Library Init //
//////////////////////////

LSM9DS1 imu; // Use the LSM9DS1 class to create an object named 'imu'

///////////////
// I2C Setup //
///////////////
// SDO_XM and SDO_G are both pulled high, so our addresses are:
#define LSM9DS1_M	0x1E 
#define LSM9DS1_AG 0x6B 

////////////////////////////
// Sketch Output Settings //
////////////////////////////
#define PRINT_CALCULATED
#define PRINT_SPEED 250 // 250 ms between prints
static unsigned long lastPrint = 0; // Keep track of print time

#define DECLINATION -10.48 // Declination (degrees) in Toronto, ON.

///////////////////////////////////////////////////////////////////////////////////////
// Setup Loop                                                                        //
///////////////////////////////////////////////////////////////////////////////////////
void setup()
{
  Serial.begin(115200); // Initialized serial output for monitoring of data

  // Initializes IMU communcation via I2C
  imu.settings.device.commInterface = IMU_MODE_I2C;
  imu.settings.device.mAddress = LSM9DS1_M;
  imu.settings.device.agAddress = LSM9DS1_AG;

  // Error checks to see if IMU was found
  if (!imu.begin())
  {
    Serial.println("Failed to communicate with LSM9DS1.");
    Serial.println("Double-check wiring.");
    Serial.println("Default settings in this sketch will " \
                   "work for an out of the box LSM9DS1 " \
                   "Breakout, but may need to be modified " \
                   "if the board jumpers are.");
    while (1);
  }

  pinMode(ledPin, OUTPUT); // Sets up LED for output
}

///////////////////////////////////////////////////////////////////////////////////////
// Main Loop                                                                         //
///////////////////////////////////////////////////////////////////////////////////////
void loop()
{
  // Reads the data from the magnometer if it's available
  if ( imu.magAvailable() )
  {
    imu.readMag();
  }

  // If enough time has elapsed since last read of data, print the data taken from the magnometer 
  if ((lastPrint + PRINT_SPEED) < millis())
  {
    printMag();   
    lastPrint = millis(); // Update lastPrint time
  }
}

///////////////////////////////////////////////////////////////////////////////////////
// printMag                                                                          //
///////////////////////////////////////////////////////////////////////////////////////
// This functions handles printing of data to serial, and the LED output
void printMag()
{
  Serial.print("Mag. (Z-Axis):              ");
  Serial.print(imu.calcMag(imu.mz), 2);
  Serial.println(" gauss");

  Serial.print("Calibrated output:          ");
  Serial.println(imu.calcMag(imu.mz) - magMin);

  float ledValue = ((imu.calcMag(imu.mz) - magMin) / (magMax)) * 255;
  Serial.print("LED Brightness (0-255):     ");
  Serial.println(ledValue);
  Serial.println("");
  analogWrite(ledPin, ledValue);    // Turns on LED to calcualted brightness value based on range of sensor data
}
