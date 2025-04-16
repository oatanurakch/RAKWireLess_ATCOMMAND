#include <stdio.h>
#include <Arduino.h>

class RAKInitial
{
public:
    RAKInitial();
    void begin(int baudRate);
    void Response();
};

class RAK : public RAKInitial
{
public:
    RAK();
    void CheckAT();
    void RUIVersion();
    // OTAA
    void OTAA_DEVEUI(String devEUI);
    void OTAA_APPEUI(String appEUI);
    void OTAA_APPKEY(String appKey);
    // ABP
    void ABP_DEVADDR(String devAddr);
    void ABP_APPSKEY(String appSKey);
    void ABP_NWKSKEY(String nwkSKey);
    // LoRaWAN Joining and Sending
    void LoRaWAN_ConfirmMode(char confirmMode);
    void LoRaWAN_ConfirmStatus();
    void LoRaWAN_Join();
    void LoRaWAN_JoinMode(char joinMode);
    void LoRaWAN_JoinStatus();
    void LoRaWAN_SendData(String HEXData);
    // LoRaWAN Network Management
    void LoRaWAN_Class(char classType);
    void LoRaWAN_TXPower(String txPower);
    void LoRaWAN_DataRate(char dataRate);
    // LoRaWAN Region Management    
    void LoRaWAN_Band(String band);
    // LoRaWAN Information
    void LoRaWAN_RSSI();
};
