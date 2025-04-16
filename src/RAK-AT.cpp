#include <stdio.h>
#include <string.h>
#include <iostream>
#include <Arduino.h>
#include <RAK-AT.h>

using namespace std;

// Define the Serial port to use for RAK communication
#if !defined(RAKSerial)
#define RAKSerial Serial2
#endif

// RAKInitial class constructor

RAKInitial::RAKInitial() {}

void RAKInitial::begin(int baudRate)
{
    RAKSerial.begin(baudRate);
}

void RAKInitial::Response()
{
    if (RAKSerial.available() > 0)
    {
        String response = RAKSerial.readStringUntil('\n');
        Serial.println("Response: " + response);
    }
}

// RAK class constructor

RAK::RAK() {}

void RAK::CheckAT()
{
    Serial.println("CMD: Check AT");
    RAKSerial.println("AT");
}

void RAK::RUIVersion()
{
    Serial.println("CMD: RUI Version");
    RAKSerial.println("AT+VER=?");
}

void RAK::OTAA_DEVEUI(String devEUI)
{
    Serial.println("CMD: OTAA DEVEUI");
    RAKSerial.println("AT+DEVEUI=" + devEUI);
}

void RAK::OTAA_APPEUI(String appEUI)
{
    Serial.println("CMD: OTAA APPEUI");
    RAKSerial.println("AT+APPEUI=" + appEUI);
}

void RAK::OTAA_APPKEY(String appKey)
{
    Serial.println("CMD: OTAA APPKEY");
    RAKSerial.println("AT+APPKEY=" + appKey);
}

void RAK::ABP_DEVADDR(String devAddr)
{
    Serial.println("CMD: ABP DEVADDR");
    RAKSerial.println("AT+DEVADDR=" + devAddr);
}

void RAK::ABP_APPSKEY(String appSKey)
{
    Serial.println("CMD: ABP APPSKEY");
    RAKSerial.println("AT+APPSKEY=" + appSKey);
}

void RAK::ABP_NWKSKEY(String nwkSKey){
    Serial.println("CMD: ABP NWKSKEY");
    RAKSerial.println("AT+NWKSKEY=" + nwkSKey);
}

void RAK::LoRaWAN_ConfirmMode(char confirmMode)
{
    Serial.println("CMD: LoRaWAN Confirm Mode [" + String(confirmMode) + "]");
    RAKSerial.println("AT+CFM=" + String(confirmMode));
}

void RAK::LoRaWAN_ConfirmStatus()
{
    RAKSerial.println("AT+CFS=?");
}

void RAK::LoRaWAN_Join()
{
    Serial.println("CMD: LoRaWAN Join");
    RAKSerial.println("AT+JOIN=1:0:10:8");
}

void RAK::LoRaWAN_JoinMode(char JoinMode)
{
    Serial.println("CMD: LoRaWAN Join Mode [" + String(JoinMode) + "]");
    RAKSerial.println("AT+NJM=" + String(JoinMode));
}

void RAK::LoRaWAN_JoinStatus()
{
    Serial.println("CMD: LoRaWAN Join Status");
    RAKSerial.println("AT+NJS=?");
}

void RAK::LoRaWAN_SendData(String HEXData)
{
    Serial.println("CMD: LoRaWAN Send Data -> " + HEXData);
    RAKSerial.println("AT+SEND=2:" + HEXData);
}

void RAK::LoRaWAN_Class(char classType)
{
    Serial.println("CMD: LoRaWAN Class [" + String(classType) + "]");
    RAKSerial.println("AT+CLASS=" + String(classType));
}

void RAK::LoRaWAN_TXPower(String txPower)
{
    Serial.println("CMD: LoRaWAN TX Power [" + txPower + "]");
    RAKSerial.println("AT+TXP=" + txPower);
}

void RAK::LoRaWAN_DataRate(char dataRate)
{
    Serial.println("CMD: LoRaWAN Data Rate [" + String(dataRate) + "]");
    RAKSerial.println("AT+DR=" + String(dataRate));
}

void RAK::LoRaWAN_Band(String band)
{
    Serial.println("CMD: LoRaWAN Band [" + band + "]");
    RAKSerial.println("AT+BAND=" + band);
}

void RAK::LoRaWAN_RSSI()
{
    Serial.println("CMD: LoRaWAN RSSI");
    RAKSerial.println("AT+RSSI=?");
}
