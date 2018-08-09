/**************************************************************
 *
 * For this example, you need to install PubSubClient library:
 *   https://github.com/knolleary/pubsubclient
 *   or from http://librarymanager/all#PubSubClient
 *
 * TinyGSM Getting Started guide:
 *   http://tiny.cc/tiny-gsm-readme
 *
 * For more MQTT examples, see PubSubClient library
 **************************************************************/

// Select your modem:
#define TINY_GSM_MODEM_SIM800
// #define TINY_GSM_MODEM_SIM808
// #define TINY_GSM_MODEM_SIM900
// #define TINY_GSM_MODEM_A6
// #define TINY_GSM_MODEM_A7
// #define TINY_GSM_MODEM_M590
// #define TINY_GSM_MODEM_ESP8266
// #define TINY_GSM_MODEM_XBEE

#include <TinyGsmClient.h>
#include <PubSubClient.h>

// Set serial for debug console (to the Serial Monitor, default speed 115200)
#define SerialMon Serial

// Use Hardware Serial on Mega, Leonardo, Micro
#define SerialAT Serial1

// or Software Serial on Uno, Nano
//#include <SoftwareSerial.h>
//SoftwareSerial SerialAT(2, 3); // RX, TX


// Your GPRS credentials
// Leave empty, if missing user or pass
const char apn[]  = "hologram";
const char user[] = "";
const char pass[] = "";

// MQTT details
const char* broker = "io.adafruit.com";
#define CLIENT_ID "gsmArduino"

// visit io.adafruit.com if you need to create an account,
// or if you need your Adafruit IO key.
#define ADAFRUIT_USERNAME    "your_username"
#define AIO_KEY              "your_key"

// Adafruit IO Feeds
#define SUBSCRIBE_FEED_PATH ADAFRUIT_USERNAME "/feeds/hologram.from"
#define PUBLISH_FEED_PATH ADAFRUIT_USERNAME "/feeds/hologram.to"


TinyGsm modem(SerialAT);
TinyGsmClient client(modem);
PubSubClient mqtt(client);

#define LED_PIN 13
int ledStatus = LOW;

long lastReconnectAttempt = 0;

// Where the magic happens

void mqttCallback(char* topic, byte* payload, unsigned int length) {

  SerialMon.print("Message arrived [");
  SerialMon.print(topic);
  SerialMon.print("]: ");
  SerialMon.write(payload, length);
  SerialMon.println();

  if (String(topic) == SUBSCRIBE_FEED_PATH) {
    ledStatus = !ledStatus;
    digitalWrite(LED_PIN, ledStatus);
    mqtt.publish(PUBLISH_FEED_PATH, ledStatus ? "1" : "0");
  }

}

void setup() {
  // Set pin mode for the LED output
  pinMode(LED_PIN, OUTPUT);

  // Set console baud rate
  SerialMon.begin(115200);
  delay(10);

  // Set GSM module baud rate
  SerialAT.begin(115200);
  delay(3000);

  // Restart takes quite some time
  // To skip it, call init() instead of restart()
  SerialMon.println("Initializing modem...");
  modem.restart();

  String modemInfo = modem.getModemInfo();
  SerialMon.print("Modem: ");
  SerialMon.println(modemInfo);

  // Unlock your SIM card with a PIN
  //modem.simUnlock("1234");

  SerialMon.print("Waiting for network...");
  if (!modem.waitForNetwork()) {
    SerialMon.println(" fail");
    while (true);
  }
  SerialMon.println(" OK");

  SerialMon.print("Connecting to ");
  SerialMon.print(apn);
  if (!modem.gprsConnect(apn, user, pass)) {
    SerialMon.println(" fail");
    while (true);
  }
  SerialMon.println(" OK");
}

void gsmConnect() {
  String modemInfo = modem.getModemInfo();
  SerialMon.print("Modem: ");
  SerialMon.println(modemInfo);

  // Unlock your SIM card with a PIN
  //modem.simUnlock("1234");

  SerialMon.print("Waiting for network...");
  if (!modem.waitForNetwork()) {
    SerialMon.println(" fail");
    while (true);
  }
  SerialMon.println(" OK");

  SerialMon.print("Connecting to ");
  SerialMon.print(apn);
  if (!modem.gprsConnect(apn, user, pass)) {
    SerialMon.println(" fail");
    while (true);
  }
  SerialMon.println(" OK");
}

boolean mqttConnect() {
  // MQTT Broker setup
  mqtt.setServer(broker, 1883);
  mqtt.setCallback(mqttCallback);

  SerialMon.print("Connecting to ");
  SerialMon.print(broker);

  // Connect to MQTT Broker
  boolean status = mqtt.connect(CLIENT_ID, ADAFRUIT_USERNAME, AIO_KEY);

  if (status == false) {
    SerialMon.println(" fail");
    return false;
  }
  SerialMon.println(" OK");
  mqtt.subscribe(SUBSCRIBE_FEED_PATH);
  return mqtt.connected();
}

void loop() {
  if(!modem.isNetworkConnected()){
    gsmConnect();
  } else {
    if (mqtt.connected()) {
    mqtt.loop();
  } else {
    // Reconnect every 10 seconds
    unsigned long t = millis();
    if (t - lastReconnectAttempt > 10000L) {
      lastReconnectAttempt = t;
      if (mqttConnect()) {
        lastReconnectAttempt = 0;
      }
    }
  }
 }
}
