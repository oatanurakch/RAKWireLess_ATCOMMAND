I'll update the README.MD to mention the ArduinoJson.h dependency:

# RAK Module AT Library

This Arduino library provides an easy way to control RAK Module LoRaWAN modules using AT commands from ESP32 development boards. The library is specifically optimized for the AS923 TH frequency band but can work with other bands as well.

## Features

- Simple interface for configuring and using RAK Module devices
- Support for both OTAA and ABP connection modes
- Helper functions for all common AT commands
- Comprehensive example code demonstrating full usage

## Dependencies

This library requires the following dependencies:
- [ArduinoJson](https://arduinojson.org/) - Used for serializing data in JSON format before sending

## Installation

1. Download the ZIP file of this library
2. In the Arduino IDE, go to Sketch > Include Library > Add .ZIP Library
3. Choose the downloaded ZIP file
4. Install the ArduinoJson library from Arduino Library Manager (Sketch > Include Library > Manage Libraries...)
5. Restart the Arduino IDE

## Usage

Below is an example of how to use this library with ESP32 to control a RAK module:

```cpp
#include <RAK-AT.h>
#include <ArduinoJson.h>

JsonDocument docpack;
char docUplink[256];

// Create an instance of the RAK class
RAK RAK;

void SerialRAKcallback(void *pvParameter) {
  while (1) {
    RAK.Response();
    vTaskDelay(20 / portTICK_RATE_MS);
  }
}

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(50);
  
  // Initialize communication with the RAK module
  RAK.begin(115200);
  
  // Create task for handling module responses on separate core
  xTaskCreatePinnedToCore(SerialRAKcallback, "SerialRAKcallback", 100000, NULL, 1, NULL, 0);
}

void loop() {
  if (Serial.available() > 0) {
    String cmd = Serial.readString();
    
    // Process different commands to control the RAK module
    if (cmd == "at") {
      RAK.CheckAT();
    } else if (cmd == "join") {
      RAK.LoRaWAN_Join();
    } else if (cmd == "send") {
      // Create sample JSON data
      docpack["s"] = random(9500, 10000) / 100;
      docpack["t"] = random(3700, 3900) / 100.0;
      docpack["h"] = random(6000, 12000) / 100;
      
      // Serialize and send as hex
      char docUplink[256];
      serializeJson(docpack, docUplink);
      RAK.LoRaWAN_SendData(convertStringToHEX(String(docUplink)));
    }
    // Additional commands available in the example
  }
}

// Utility function to convert string to hex
String convertStringToHEX(String raw_string) {
  char raw_string_buffer[raw_string.length() + 1];
  raw_string.toCharArray(raw_string_buffer, raw_string.length() + 1);
  String HEXSTRING = "";
  for (byte i = 0; i < sizeof(raw_string_buffer) - 1; i++) {
    HEXSTRING += String(raw_string[i], HEX);
  }
  return HEXSTRING;
}
```

## Available Functions

### Basic Functions

- [`begin(int baudRate)`](src/RAK-AT.cpp ) - Initialize serial communication with the module
- [`Response()`](src/RAK-AT.cpp ) - Read and print responses from the module
- [`CheckAT()`](src/RAK-AT.cpp ) - Send basic AT command to check if module is responsive
- [`RUIVersion()`](src/RAK-AT.cpp ) - Get the firmware version of the module

### OTAA Connection

- [`OTAA_DEVEUI(String devEUI)`](src/RAK-AT.cpp ) - Set device EUI for OTAA
- [`OTAA_APPEUI(String appEUI)`](src/RAK-AT.cpp ) - Set application EUI for OTAA
- [`OTAA_APPKEY(String appKey)`](src/RAK-AT.cpp ) - Set application key for OTAA

### ABP Connection

- [`ABP_DEVADDR(String devAddr)`](src/RAK-AT.cpp ) - Set device address for ABP
- [`ABP_APPSKEY(String appSKey)`](src/RAK-AT.cpp ) - Set application session key for ABP
- [`ABP_NWKSKEY(String nwkSKey)`](src/RAK-AT.cpp ) - Set network session key for ABP

### LoRaWAN Configuration and Management

- [`LoRaWAN_ConfirmMode(char confirmMode)`](src/RAK-AT.cpp ) - Set confirmation mode (0=unconfirmed, 1=confirmed)
- [`LoRaWAN_ConfirmStatus()`](src/RAK-AT.cpp ) - Get current confirmation mode
- [`LoRaWAN_Join()`](src/RAK-AT.cpp ) - Join the LoRaWAN network
- [`LoRaWAN_JoinMode(char joinMode)`](src/RAK-AT.cpp ) - Set join mode (0=ABP, 1=OTAA)
- [`LoRaWAN_JoinStatus()`](src/RAK-AT.cpp ) - Check if device is connected to network
- [`LoRaWAN_SendData(String HEXData)`](src/RAK-AT.cpp ) - Send hex data over LoRaWAN
- [`LoRaWAN_Class(char classType)`](src/RAK-AT.cpp ) - Set LoRaWAN device class (A, B, or C)
- [`LoRaWAN_TXPower(String txPower)`](src/RAK-AT.cpp ) - Set transmission power
- [`LoRaWAN_DataRate(char dataRate)`](src/RAK-AT.cpp ) - Set data rate
- [`LoRaWAN_Band(String band)`](src/RAK-AT.cpp ) - Set frequency band
- [`LoRaWAN_RSSI()`](src/RAK-AT.cpp ) - Get current RSSI value

## Complete Example

The ESP32_RAK_ExampleCode.ino example included with the library demonstrates all features and provides an interactive command-line interface via the Serial Monitor:

- `at` - Check if module is responsive
- `version` - Get firmware version
- `join` - Join LoRaWAN network
- `deveui` - Get or set device EUI
- `appeui` - Get or set application EUI
- `appkey` - Get or set application key
- `cfm` - Set confirmation mode
- `cfs` - Check confirmation status
- `joinmode` - Set join mode (ABP/OTAA)
- `joinst` - Check join status
- `send` - Send sample data (JSON with temperature, humidity)
- `class` - Set LoRaWAN class
- `txpower` - Set transmission power
- `datarate` - Set data rate
- `band` - Set frequency band
- `rssi` - Get RSSI value

## License

This library is released under the MIT License.

## Author

Anurak Choosri - [anurakch.1999@gmail.com](mailto:anurakch.1999@gmail.com)

## Links

- [GitHub Repository](https://github.com/yourusername/RAK_Module_AT)