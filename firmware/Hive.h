#ifndef HIVE_H
#define HIVE_H
#include "FastLED.h"
#include <WebSocketsServer.h>
#include <ArduinoJson.h>

// Includes for BLE
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLEDevice.h>
#include <BLEAdvertising.h>

#define FIRMWARE_VERSION "0.0.18"

#define SERVICE_UUID  "0000aaaa-ead2-11e7-80c1-9a214cf093ae"
#define WIFI_UUID     "00005555-ead2-11e7-80c1-9a214cf093ae"

#define TOTAL_LEDS  300
#define SLICE_LEDS  10
#define DATA_PIN    33

//#define DEFAULT_SSID      "HIVE_AP"
#define DEFAULT_PSWD        "hive1234"
#define WEBSOCKET_PORT      5656
#define RESET_TO_DEFAULT    5 * 1000

class Hive 
{

public:
    Hive(bool debug = false);

    void setup();
    void run();

protected:
    uint32_t getChipId();

    void initLeds();
    void initWifi();
    void initMDNS();
    void initBLE();

    void saveConfiguration();
    bool loadConfiguration();
    void resetSettingsToDefault();

    void updateFirmware(String filename);
    void updateNetworking(String msg);

    void setColor();
    void setColor(CRGB color);

    void colorBreathing();
    void colorCylon();
    void colorSwirl();
    void rainbow();
    CRGB wheel(byte wheelPos);

    CRGB stringToColor(String color);
    

    void debugPrint(String msg, bool withNewline = true);
    void debugPrint(uint8_t* msg, bool withNewline = true);
    void debugPrint(int msg, bool withNewline = true);

    void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length);

    String      _deviceId;
    String      _localIp;

    bool        _apMode;
    bool        _allowProgramRun;
    bool        _updatingFirmware;
    
    String      _currentSSID;
    String      _currentPassword;
    char        _deviceName[100];

    bool        _configIsDirty;
    bool        _allowDebug;


    DynamicJsonDocument _jsonDocument;
    DynamicJsonDocument _jsonCurrentProgram;

    uint8_t     _colorBreathingCounter;
    int         _colorBreathingDirection;
    long        _colorBreathingDuration;

    int         _colorCylonIndex;
    int         _colorCylonDuration;
    int         _colorCylonDirection;

    WebSocketsServer* _webSocket;

    // BLE
    BLECharacteristic*  _pCharacteristicWiFi;
    BLEAdvertising*     _pAdvertising;
    BLEService*         _pService;
    BLEServer*          _pServer;    

    int _i;


    CRGB        _leds[TOTAL_LEDS];    
};



#endif