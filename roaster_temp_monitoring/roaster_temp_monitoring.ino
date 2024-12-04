#include <Adafruit_MAX31865.h> // This is the PT100 RTD interface board.
#include <TM1637Display.h> .   // One of many libraries for the TM1637.

// MAX31865 configuration
#define MAX_CS   9   // Chip Select
#define MAX_MOSI 11  // MOSI (SDI)
#define MAX_MISO 12  // MISO (SDO)
#define MAX_CLK  13  // Clock

// Adafruit_MAX31865 thermo = Adafruit_MAX31865(MAX_CS, MAX_MOSI, MAX_MISO, MAX_CLK);
Adafruit_MAX31865 thermo = Adafruit_MAX31865(MAX_CS);  // Hardware SPI

// Use 430.0 for a PT100 and 4300.0 for a PT1000
#define RREF 430.0

// TODO: Based on your unique snowflake of an RTD you should adjust this so your RTD reads accurately! 
#define RNOMINAL 98.0   // Tweaked down from 100.0 to correct offset. 


// TM1637 configuration, like I2C, but not standard compliant
#define CLK 7  // Clock 
#define DIO 8  // Data (DIO)

TM1637Display display(CLK, DIO);

// Segment data for 'C' and 'F' and 'E'
const uint8_t CHAR_C = SEG_A | SEG_D | SEG_E | SEG_F;
const uint8_t CHAR_F = SEG_A | SEG_E | SEG_F | SEG_G;
const uint8_t CHAR_E = SEG_A | SEG_D | SEG_E | SEG_F | SEG_G;
const uint8_t CHAR_R = SEG_E | SEG_G;

void setup() {
  Serial.begin(9600);
  while (!Serial) ; 
  Serial.println("Serial port ready.");

  display.setBrightness(5);

  if (!thermo.begin(MAX31865_3WIRE)) {  // Initialize the MAX31865
    Serial.println("Failed to initialize MAX31865. Check your wiring?");
  } else {
    Serial.println("MAX31865 Initialized!");
  }

}

void loop() {
  // Read temperature from the MAX31865
  float temperature = thermo.temperature(RNOMINAL, RREF);

  // Debugging: Print raw resistance and fault details
  uint16_t rtdValue = thermo.readRTD();
  Serial.print("Raw RTD value: "); Serial.println(rtdValue);
  Serial.print("Ratio: "); Serial.println(rtdValue/32768.0, 8);
  Serial.print("Resistance: "); Serial.println(RREF * rtdValue/32768.0, 5);
  Serial.print("Temperature (C): "); Serial.println(temperature, 1);
  Serial.print("Temperature (F): "); Serial.println(temperature * 9/5 + 32, 1);

  uint8_t fault = thermo.readFault();  // Check fault register
  if (fault) {
    Serial.print("Fault detected! Code: "); Serial.println(fault, HEX);

    if (fault & MAX31865_FAULT_HIGHTHRESH) Serial.println("RTD High Threshold Fault");
    if (fault & MAX31865_FAULT_LOWTHRESH) Serial.println("RTD Low Threshold Fault");
    if (fault & MAX31865_FAULT_REFINLOW) Serial.println("REFIN- < 0.85*V_BIAS");
    if (fault & MAX31865_FAULT_REFINHIGH) Serial.println("REFIN- > 0.85*V_BIAS");
    if (fault & MAX31865_FAULT_RTDINLOW) Serial.println("RTDIN- < 0.85*V_BIAS");
    if (fault & MAX31865_FAULT_OVUV) Serial.println("Over/Under Voltage Fault");

    thermo.clearFault();  // Clear the fault after report
  }

  // Display temperature (both C & F), if we have a good reading
  if (!fault) {
    int tempInt = round(temperature);  // Round the C temperature for display
    display.showNumberDecEx(tempInt, 0, false, 3, 0);  // Display on the left three digits
    display.setSegments(&CHAR_C, 1, 3);  // Add "C" in the last display position
    delay(2000);
    display.clear();
    delay(250);
    tempInt = round(temperature * 9/5 + 32);  // Round the F temperature for display
    display.showNumberDecEx(tempInt, 0, false, 3, 0);  // Display on the left three digits
    display.setSegments(&CHAR_F, 1, 3);  // Add "F" on the last display position
    delay(2000);
    display.clear();
    delay(250);
  } else {
    display.clear();  // Clear the display if there's a fault...
    display.setSegments(&CHAR_E, 1, 1);  // ...add "E" on the second digit...
    display.setSegments(&CHAR_R, 1, 2);  // ...add "R" on the third digit...
    display.setSegments(&CHAR_R, 1, 3);  // ...and add "R" on the last digit!
    delay(500);       // ...but return to the well swiftly for a new value.
  }
  
}
