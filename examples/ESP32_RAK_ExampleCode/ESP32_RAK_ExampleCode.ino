#include <RAK-AT.h>
#include <ArduinoJson.h>

JsonDocument docpack;
char docUplink[256];

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
  RAK.begin(115200);
  // Create task to CORE
  xTaskCreatePinnedToCore(SerialRAKcallback, "SerialRAKcallback", 100000, NULL, 1, NULL, 0);
}

void loop() {
  if (Serial.available() > 0) {
    String cmd = Serial.readString();
    if (cmd == "at") {
      RAK.CheckAT();
    } else if (cmd == "version") {
      RAK.RUIVersion();
    } else if (cmd == "join") {
      RAK.LoRaWAN_Join();
    } else if (cmd == "deveui") {
      Serial.println("Get or Set DEVEUI ([?: GET, DEVEUI 8 bytes HEX]): ");
      while (Serial.available() == 0)
        ;
      String val = Serial.readString();
      RAK.OTAA_DEVEUI(val);
    } else if (cmd == "appeui") {
      Serial.println("Get or Set APPEUI ([?: GET, APPEUI 8 bytes HEX]): ");
      while (Serial.available() == 0)
        ;
      String val = Serial.readString();
      RAK.OTAA_APPEUI(val);
    } else if (cmd == "appkey") {
      Serial.println("Get or Set APPKEY ([?: GET, APPKEY 16 bytes HEX]): ");
      while (Serial.available() == 0)
        ;
      String val = Serial.readString();
      RAK.OTAA_APPKEY(val);
    } else if (cmd == "cfm") {
      Serial.println("Input Confirm Mode ([0: OFF], [1: ON] or [?: Check]): ");
      while (Serial.available() == 0)
        ;
      char mode = Serial.read();
      RAK.LoRaWAN_ConfirmMode(mode);
    } else if (cmd == "cfs") {
      RAK.LoRaWAN_ConfirmStatus();
    } else if (cmd == "joinmode") {
      Serial.println("Input Join Mode ([0: ABP], [1: OTAA] or [?: Check]): ");
      while (Serial.available() == 0)
        ;
      char mode = Serial.read();
      RAK.LoRaWAN_JoinMode(mode);
    } else if (cmd == "joinst") {
      RAK.LoRaWAN_JoinStatus();
    } else if (cmd == "send") {
      docpack["s"] = random(9500, 10000) / 100;
      docpack["t"] = random(3700, 3900) / 100.0;
      docpack["h"] = random(6000, 12000) / 100;
      char docUplink[256];
      serializeJson(docpack, docUplink);
      RAK.LoRaWAN_SendData(convertStringToHEX(String(docUplink)));
    } else if (cmd == "class") {
      Serial.println("Input Class ([A, B, C or ? : get]): ");
      while (Serial.available() == 0)
        ;
      char mode = Serial.read();
      RAK.LoRaWAN_Class(mode);
    } else if (cmd == "txpower") {
      Serial.println("Input TX Power ([0 = highest -> 10 lowest] or ? : get): ");
      while (Serial.available() == 0)
        ;
      String mode = Serial.readString();
      RAK.LoRaWAN_TXPower(mode);
    } else if (cmd == "datarate") {
      Serial.println("Input DataRate ([0 -> 7 (TH use 2 - 5)] or ? : get): ");
      while (Serial.available() == 0)
        ;
      char mode = Serial.read();
      RAK.LoRaWAN_DataRate(mode);
    } else if (cmd == "band") {
      Serial.println("Input Band ([1 - 12 (AS923 TH is 8) or ? : get]): ");
      while (Serial.available() == 0)
        ;
      String mode = Serial.readString();
      RAK.LoRaWAN_Band(mode);
    } else if (cmd == "rssi") {
      RAK.LoRaWAN_RSSI();
    }
  }
}

// Convert string to hex
String convertStringToHEX(String raw_string) {
  // Convert string to char array
  char raw_string_buffer[raw_string.length() + 1];
  raw_string.toCharArray(raw_string_buffer, raw_string.length() + 1);
  // Convert to HEX
  String HEXSTRING = "";
  for (byte i = 0; i < sizeof(raw_string_buffer) - 1; i++) {
    HEXSTRING += String(raw_string[i], HEX);
  }
  return HEXSTRING;
}
