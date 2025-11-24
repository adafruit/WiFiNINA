/*

 This example shows how to use the built in RGB LED

 Circuit:
 * Board with NINA firmware on it (In this case its an Adafruit AirLift)

 Written by Bryan Siepert for Adafruit Industries on the 30th of October in the year of our Rona, 2020
 */


#include <SPI.h>
#include <WiFiNINA.h>

 // Configure the pins used for the ESP32 connection
#if defined(ADAFRUIT_FEATHER_M4_EXPRESS) || \
  defined(ADAFRUIT_ITSYBITSY_M4_EXPRESS) || \
	defined(ADAFRUIT_FEATHER_M0_EXPRESS) || \
 defined(ARDUINO_AVR_FEATHER32U4) || \
	defined(ARDUINO_NRF52840_FEATHER)
  #define SPIWIFI       SPI  // The SPI port
  #define SPIWIFI_SS    13   // Chip select pin
  #define ESP32_RESETN  12   // Reset pin
  #define SPIWIFI_ACK   11   // a.k.a BUSY or READY pin
  #define ESP32_GPIO0   10

#elif defined(ARDUINO_AVR_FEATHER328P) 
  #define SPIWIFI       SPI  // The SPI port
  #define SPIWIFI_SS     4   // Chip select pin
  #define ESP32_RESETN   3   // Reset pin
  #define SPIWIFI_ACK    2   // a.k.a BUSY or READY pin
  #define ESP32_GPIO0   -1

#elif defined(ARDUINO_NRF52832_FEATHER )
  #define SPIWIFI       SPI  // The SPI port
  #define SPIWIFI_SS    16  // Chip select pin
  #define ESP32_RESETN  15  // Reset pin
  #define SPIWIFI_ACK    7  // a.k.a BUSY or READY pin
  #define ESP32_GPIO0   -1

#elif defined(TEENSYDUINO) 
  #define SPIWIFI       SPI  // The SPI port
  #define SPIWIFI_SS     5   // Chip select pin
  #define ESP32_RESETN   6   // Reset pin
  #define SPIWIFI_ACK    9   // a.k.a BUSY or READY pin
  #define ESP32_GPIO0   -1
#endif

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("WiFi Scanning test");

  // Set up the pins!
  WiFi.setPins(SPIWIFI_SS, SPIWIFI_ACK, ESP32_RESETN, ESP32_GPIO0, &SPIWIFI);

  // check for the WiFi module:
  while (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    delay(1000);
  }
  String fv = WiFi.firmwareVersion();
  Serial.println(fv);
  if (fv < "1.0.0") {
    Serial.println("Please upgrade the firmware");
    while (1) delay(10);
  }
  Serial.println("Firmware OK");

}

void loop() {
   WiFi.setLEDs(255, 0, 0); // RED
   delay(100);
   WiFi.setLEDs(0, 255, 0); // GREEN
   delay(100);
   WiFi.setLEDs(0, 0, 255); // BLUE
   delay(100);
   WiFi.setLEDs(0, 0, 0); // OFF
   delay(50);

}
