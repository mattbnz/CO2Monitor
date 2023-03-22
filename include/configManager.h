#ifndef _CONFIG_MANAGER_H
#define _CONFIG_MANAGER_H

#include <config.h>

#define CONFIG_SIZE 1280

#define MQTT_USERNAME_LEN 20
#define MQTT_PASSWORD_LEN 20
#define MQTT_HOSTNAME_LEN 30
#define MQTT_TOPIC_ID_LEN 30
#define SSID_LEN 20
#define PASSWORD_LEN 20

typedef enum {
  BUZ_OFF = 0,
  BUZ_LVL_CHANGE,
  BUZ_ALWAYS
} BuzzerMode;

typedef enum {
  SLEEP_OLED_ON_LED_ON = 0,
  SLEEP_OLED_ON_LED_OFF,
  SLEEP_OLED_OFF_LED_ON,
  SLEEP_OLED_OFF_LED_OFF
} SleepModeOledLed;

struct Config {
  uint16_t deviceId;
  char mqttTopic[MQTT_TOPIC_ID_LEN + 1];
  char mqttUsername[MQTT_USERNAME_LEN + 1];
  char mqttPassword[MQTT_PASSWORD_LEN + 1];
  char mqttHost[MQTT_HOSTNAME_LEN + 1];
  bool mqttUseTls;
  bool mqttInsecure;
  uint16_t mqttServerPort;
  uint16_t altitude;
  uint16_t co2YellowThreshold;
  uint16_t co2RedThreshold;
  uint16_t co2DarkRedThreshold;
  uint16_t iaqYellowThreshold;
  uint16_t iaqRedThreshold;
  uint16_t iaqDarkRedThreshold;
  uint8_t brightness;
  uint8_t ssd1306Rows;
  uint8_t greenLed;
  uint8_t yellowLed;
  uint8_t redLed;
  uint8_t neopixelData;
  uint8_t neopixelNumber;
  uint8_t neopixelMatrixData;
  uint8_t featherMatrixData;
  uint8_t featherMatrixClock;
  uint8_t matrixColumns;
  uint8_t matrixRows;
  uint8_t matrixLayout;
  uint8_t hub75R1;
  uint8_t hub75G1;
  uint8_t hub75B1;
  uint8_t hub75R2;
  uint8_t hub75G2;
  uint8_t hub75B2;
  uint8_t hub75ChA;
  uint8_t hub75ChB;
  uint8_t hub75ChC;
  uint8_t hub75ChD;
  uint8_t hub75Clk;
  uint8_t hub75Lat;
  uint8_t hub75Oe;

  uint8_t vBatEn = VBAT_EN;
  uint8_t vBatAdc = VBAT_ADC;
  uint8_t btn2 = BTN_2;
  uint8_t btn3 = BTN_3;
  uint8_t btn4 = BTN_4;
  uint8_t oledEn = OLED_EN;
  uint8_t buzzerPin = BUZZER_PIN;
  uint8_t sdDetect = SD_DETECT;
  uint8_t sdDat0 = SD_DAT0;
  uint8_t sdDat1 = SD_DAT1;
  uint8_t sdDat2 = SD_DAT2;
  uint8_t sdDat3 = SD_DAT3;
  uint8_t sdClk = SD_CLK;
  uint8_t sdCmd = SD_CMD;

  BuzzerMode buzzerMode = BUZ_LVL_CHANGE;
  SleepModeOledLed sleepModeOledLed = SLEEP_OLED_ON_LED_ON;
};

void setupConfigManager();
void getDefaultConfiguration(Config& config);
boolean loadConfiguration(Config& config);
boolean saveConfiguration(const Config& config);
void logConfiguration(const Config& config);
void printFile();
BuzzerMode getBuzzerModeFromUint(uint8_t buzzerMode);
SleepModeOledLed getSleepModeOledLedFromUint(uint8_t mode);

extern Config config;

#endif