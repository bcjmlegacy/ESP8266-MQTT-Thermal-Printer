#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DallasTemperature.h>

#include "config.h"
#include "Adafruit_Thermal.h"
#include "SoftwareSerial.h"

#define TX_PIN 5 // RX
#define RX_PIN 4 // TX

#define MAX_TOPIC_LENGTH 50
#define MAX_PAYLOAD_LENGTH 10

char mqtt_id[24];
char mqtt_topic[50];

DeviceAddress device_address;
WiFiClient client;
PubSubClient mqtt(client);

SoftwareSerial mySerial(TX_PIN, RX_PIN);
Adafruit_Thermal printer(&mySerial);

void hexlify(uint8_t bytes[], uint8_t len, char *buffer)
{
  for (int i=0; i<len; i++) {
    int ms = bytes[i] >> 4;
    int ls = bytes[i] & 0x0f;
    char a, b;
    if (ms < 10)
      a = '0' + ms;
    else
      a = 'a' + ms - 10;
    if (ls < 10)
      b = '0' + ls;
    else
      b = 'a' + ls - 10;
    //printf("byte %d is %02x (%x %x %c%c)\n", i, bytes[i], ms, ls, a, b);
    buffer[i*2] = a;
    buffer[(i*2)+1] = b;
  }
  buffer[(len*2)] = 0;
}

void callback(char* topic, byte* payload, unsigned int length) {
  printer.setDefault();
  printer.setSize('S');
  printer.feed(1);
  printer.print(F("Message arrived:\n"));
  for (int i=0;i<length;i++) {
    printer.print((char)payload[i]);
  }
  printer.feed(3);
}

void setup() {

  char device_address_string[17];

  mySerial.begin(baud);
  printer.begin();
  printer.setDefault();
  
  printer.setSize('S');
  printer.feed(1);
  printer.println(F("Printer starting"));
  
  wifi_station_set_hostname(my_id);
  printer.print(F("Hostname: "));
  printer.println(my_id);
  WiFi.mode(WIFI_STA);

  mqtt.setServer(mqtt_server, mqtt_port);
  mqtt.setCallback(callback);

}

void loop() {

  if (WiFi.status() != WL_CONNECTED) {
    printer.println(F("Connecting to WiFi..."));
    WiFi.begin(ssid, password);

    unsigned long begin_started = millis();
    while (WiFi.status() != WL_CONNECTED) {
      delay(10);
      if (millis() - begin_started > 60000) {
        ESP.restart();
      }
    }
    printer.println(F("WiFi connected!"));
  }

  if (!mqtt.connected()) {
    if (mqtt.connect(mqtt_id)) {
      printer.println(F("MQTT connected"));
      printer.feed(1);
      mqtt.subscribe(mqtt_listen_topic);
    } else {
      printer.println(F("MQTT connection failed"));
      printer.feed(1);
      delay(2000);
      return;
    }
  }

  mqtt.loop();
  
}
