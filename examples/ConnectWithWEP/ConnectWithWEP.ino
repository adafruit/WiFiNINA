/*

 This example connects to a WEP-encrypted Wifi network.
 Then it prints the  MAC address of the Wifi module,
 the IP address obtained, and other network details.

 If you use 40-bit WEP, you need a key that is 10 characters long,
 and the characters must be hexadecimal (0-9 or A-F).
 e.g.  for 40-bit, ABBADEAF01 will work, but ABBADEAF won't work
 (too short) and ABBAISDEAF won't work (I and S are not
 hexadecimal characters).

 For 128-bit, you need a string that is 26 characters long.
 D0D0DEADF00DABBADEAFBEADED will work because it's 26 characters,
 all in the 0-9, A-F range.

 created 13 July 2010
 by dlf (Metodo2 srl)
 modified 31 May 2012
 by Tom Igoe
 */
#include <SPI.h>
#include <WiFiNINA.h>

#if defined(ADAFRUIT_FEATHER_M4_EXPRESS) || \
  defined(ADAFRUIT_FEATHER_M0_EXPRESS) || \
  defined(ADAFRUIT_FEATHER_M0) || \
  defined(ARDUINO_AVR_FEATHER32U4) || \
  defined(ARDUINO_NRF52840_FEATHER) || \
  defined(ADAFRUIT_ITSYBITSY_M0) || \
  defined(ADAFRUIT_ITSYBITSY_M4_EXPRESS) || \
  defined(ARDUINO_AVR_ITSYBITSY32U4_3V) || \
  defined(ARDUINO_NRF52_ITSYBITSY)
  // Configure the pins used for the ESP32 connection
  #define SPIWIFI       SPI  // The SPI port
  #define SPIWIFI_SS    13   // Chip select pin
  #define ESP32_RESETN  12   // Reset pin
  #define SPIWIFI_ACK   11   // a.k.a BUSY or READY pin
  #define ESP32_GPIO0   -1
#elif defined(ARDUINO_ADAFRUIT_ITSYBITSY_RP2040)
  #define SPIWIFI SPI  // The SPI port
  #define SPIWIFI_SS    11   // Chip select pin
  #define ESP32_RESETN  10   // Reset pin
  #define SPIWIFI_ACK   9   // a.k.a BUSY or READY pin
  #define ESP32_GPIO0   -1
#elif defined(ARDUINO_AVR_FEATHER328P)
  #define SPIWIFI       SPI  // The SPI port
  #define SPIWIFI_SS     4   // Chip select pin
  #define ESP32_RESETN   3   // Reset pin
  #define SPIWIFI_ACK    2   // a.k.a BUSY or READY pin
  #define ESP32_GPIO0   -1
#elif defined(TEENSYDUINO)
  #define SPIWIFI       SPI  // The SPI port
  #define SPIWIFI_SS     5   // Chip select pin
  #define ESP32_RESETN   6   // Reset pin
  #define SPIWIFI_ACK    9   // a.k.a BUSY or READY pin
  #define ESP32_GPIO0   -1
#elif defined(ARDUINO_NRF52832_FEATHER )
  #define SPIWIFI       SPI  // The SPI port
  #define SPIWIFI_SS    16  // Chip select pin
  #define ESP32_RESETN  15  // Reset pin
  #define SPIWIFI_ACK    7  // a.k.a BUSY or READY pin
  #define ESP32_GPIO0   -1
#elif !defined(SPIWIFI_SS)  // if the wifi definition isnt in the board variant
  // Don't change the names of these #define's! they match the variant ones
  #define SPIWIFI       SPI
  #define SPIWIFI_SS    10   // Chip select pin
  #define SPIWIFI_ACK    7   // a.k.a BUSY or READY pin
  #define ESP32_RESETN   5   // Reset pin
  #define ESP32_GPIO0   -1   // Not connected
#endif

#include "arduino_secrets.h" 
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;                                // your network key Index number
int status = WL_IDLE_STATUS;                     // the Wifi radio's status

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  WiFi.setPins(SPIWIFI_SS, SPIWIFI_ACK, ESP32_RESETN, ESP32_GPIO0, &SPIWIFI);
  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < "1.0.0") {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WEP network, SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, keyIndex, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }

  // once you are connected :
  Serial.print("You're connected to the network");
  printCurrentNet();
  printWifiData();
}

void loop() {
  // check the network connection once every 10 seconds:
  delay(10000);
  printCurrentNet();
}

void printWifiData() {
  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  Serial.println(ip);

  // print your MAC address:
  byte mac[6];
  WiFi.macAddress(mac);
  Serial.print("MAC address: ");
  printMacAddress(mac);
}

void printCurrentNet() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print the MAC address of the router you're attached to:
  byte bssid[6];
  WiFi.BSSID(bssid);
  Serial.print("BSSID: ");
  printMacAddress(bssid);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.println(rssi);

  // print the encryption type:
  byte encryption = WiFi.encryptionType();
  Serial.print("Encryption Type:");
  Serial.println(encryption, HEX);
  Serial.println();
}

void printMacAddress(byte mac[]) {
  for (int i = 5; i >= 0; i--) {
    if (mac[i] < 16) {
      Serial.print("0");
    }
    Serial.print(mac[i], HEX);
    if (i > 0) {
      Serial.print(":");
    }
  }
  Serial.println();
}
